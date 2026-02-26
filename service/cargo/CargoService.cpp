#include "CargoService.hpp"
#include "../../visitor/cargo/CargoLoadVisitor.hpp"
#include "../../visitor/cargo/CargoRemovalVisitor.hpp"
#include "../../visitor/cargo/CargoInfoVisitor.hpp"
#include <limits>
#include <algorithm>

CargoService::CargoService(Mission& mission, ShipRepository& convoy_repo) : mission_(mission), convoy_repo_(convoy_repo) {}

bool CargoService::load_cargo(IShip* ship, double amount) {
    if (!ship || amount <= 0) return false;

    CargoLoadVisitor visitor(amount);
    ship->accept(&visitor);
    if (visitor.is_loaded()) {
        mission_.add_cargo(amount);
        return true;
    }
    return false;
}

bool CargoService::unload_cargo(IShip* ship, double amount) {
    if (!ship || amount <= 0) return false;
    CargoRemovalVisitor visitor(amount);
    ship->accept(&visitor);
    if (visitor.is_removed()) {
        mission_.remove_cargo(amount);
        return true;
    }
    return false;
}

bool CargoService::auto_distribute_cargo(double total_cargo) {
    return distribute_for_max_speed(total_cargo);
}

bool CargoService::distribute_for_max_speed(double total_cargo) {
    CargoInfoVisitor visitor;
    if (total_cargo <= 0) return true;
    
    auto cargo_ships = convoy_repo_.get_cargo_ships();
    if (cargo_ships.empty()) return false;
    
    double total_capacity = 0.0;
    for (auto ship : cargo_ships) {
        ship->accept(&visitor);
        total_capacity += visitor.get_max_cargo();
    }
    if (total_cargo > total_capacity) return false;
    
    sort_by_speed_factor(cargo_ships, true);
    
    double remaining_cargo = total_cargo;
    for (auto ship : cargo_ships) {
        if (remaining_cargo <= 0) break;
            
        ship->accept(&visitor);
        double to_load = std::min(remaining_cargo, std::max(0.0, visitor.get_max_cargo() - visitor.get_current_cargo()));
        if (to_load > 0) {
            if (load_cargo(ship, to_load)) remaining_cargo -= to_load;
        }
    }
    return remaining_cargo <= 1e-9;
}

bool CargoService::distribute_evenly(double total_cargo) {
    CargoInfoVisitor visitor;
    if (total_cargo <= 0) return true;

    auto cargo_ships = convoy_repo_.get_cargo_ships();
    if (cargo_ships.empty()) return false;

    double total_capacity = 0.0;
    for (auto ship : cargo_ships) {
        ship->accept(&visitor);
        total_capacity += visitor.get_max_cargo();
    }
    if (total_cargo > total_capacity) return false;
    
    double cargo_per_ship = total_cargo / (cargo_ships.size());
    double remaining_cargo = total_cargo;
    
    for (auto ship : cargo_ships) {
        if (remaining_cargo <= 0) break;
        
        ship->accept(&visitor);
        double to_load = std::min(cargo_per_ship, std::max(0.0, visitor.get_max_cargo() - visitor.get_current_cargo()));
        to_load = std::min(to_load, remaining_cargo);
        
        if (to_load > 0) {
            if (load_cargo(ship, to_load)) remaining_cargo -= to_load;
        }
    }
    if (remaining_cargo > 0) {
        sort_by_available_cargo(cargo_ships, false);
        for (auto ship : cargo_ships) {
            if (remaining_cargo <= 0) break;
            
            ship->accept(&visitor);
            double to_load = std::min(remaining_cargo, std::max(0.0, visitor.get_max_cargo() - visitor.get_current_cargo()));
            if (to_load > 0) {
                if (load_cargo(ship, to_load)) remaining_cargo -= to_load;
            }
        }
    }
    return remaining_cargo <= 1e-9;
}

double CargoService::get_total_cargo_capacity() const {
    CargoInfoVisitor visitor;
    auto transport_ships = convoy_repo_.get_ships_by_type("transport");
    auto war_ships = convoy_repo_.get_ships_by_type("war");

    double total_capacity = 0.0;
    for (auto ship : transport_ships) {
        ship->accept(&visitor);
        total_capacity += visitor.get_max_cargo();
    }
    for (auto ship : war_ships) {
        ship->accept(&visitor);
        total_capacity += visitor.get_max_cargo();
    }
    return total_capacity;
}

double CargoService::get_total_cargo() const {
    return mission_.get_total_cargo();
}

double CargoService::get_current_cargo() const {
    return mission_.get_current_cargo();
}

double CargoService::get_available_cargo() const {
    return get_total_cargo_capacity() - get_current_cargo();
}

std::vector<IShip*> CargoService::get_cargo_ships() const {
    return convoy_repo_.get_cargo_ships();
}

double CargoService::calculate_optimal_speed_for_ship(IShip* ship, double additional_cargo) const {
    if (!ship) return 0.0;
    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    
    double current_cargo = visitor.get_current_cargo();
    double max_cargo = visitor.get_max_cargo();
    double reduction_factor = visitor.get_speed_reduction_factor();
    
    if (max_cargo <= 0) return ship->get_max_speed();
    
    double total_cargo = current_cargo + additional_cargo;
    double cargo_ratio = std::min(total_cargo / max_cargo, 1.0);
    
    return ship->get_max_speed() * (1.0 - cargo_ratio * reduction_factor);
}

double CargoService::calculate_convoy_speed_with_current_load() const {
    auto cargo_ships = convoy_repo_.get_cargo_ships();
    if (cargo_ships.empty()) return 0.0;
    
    double min_speed = std::numeric_limits<double>::max();
    
    for (auto ship : cargo_ships) {
        double speed = calculate_optimal_speed_for_ship(ship, 0.0);
        min_speed = std::min(min_speed, speed);
    }

    auto guard_ships = convoy_repo_.get_ships_by_type("guard");
    for (auto ship : guard_ships) {
        min_speed = std::min(min_speed, ship->get_max_speed());
    }
    
    return (min_speed == std::numeric_limits<double>::max()) ? 0.0 : min_speed;
}

bool CargoService::can_ship_carry_cargo(IShip* ship, double amount) const {
    if (!ship || amount < 0) return false;
    
    double available = get_ship_available_cargo(ship);
    return amount <= available;
}

double CargoService::get_ship_max_cargo(IShip* ship) const {
    if (!ship) return 0.0;
    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    return visitor.get_max_cargo();
}

double CargoService::get_ship_current_cargo(IShip* ship) const {
    if (!ship) return 0.0;
    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    return visitor.get_current_cargo();
}

double CargoService::get_ship_available_cargo(IShip* ship) const {
    if (!ship) return 0.0;
    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    return std::max(0.0, visitor.get_max_cargo() - visitor.get_current_cargo());
}

double CargoService::get_required_cargo() const {
    return mission_.get_required_cargo();
}

void CargoService::sort_by_available_cargo(std::vector<IShip*>& ships, bool ascending) {
    std::sort(ships.begin(), ships.end(), [ascending](IShip* a, IShip* b) {
        CargoInfoVisitor visitor;
        a->accept(&visitor);
        double a_available_cargo = std::min(0.0, visitor.get_max_cargo() - visitor.get_current_cargo());
        b->accept(&visitor);
        double b_available_cargo = std::min(0.0, visitor.get_max_cargo() - visitor.get_current_cargo()); 
        
        if (ascending) return a_available_cargo < b_available_cargo;
        else return a_available_cargo > b_available_cargo;
    });
}

void CargoService::sort_by_speed_factor(std::vector<IShip*>& ships, bool ascending) {
    std::sort(ships.begin(), ships.end(), [ascending](IShip* a, IShip* b) {
        CargoInfoVisitor visitor;
        a->accept(&visitor);
        double a_speed_factor = visitor.get_speed_reduction_factor();
        b->accept(&visitor);
        double b_speed_factor = visitor.get_speed_reduction_factor(); 
        
        if (ascending) return a_speed_factor < b_speed_factor;
        else return a_speed_factor > b_speed_factor;
    });
}
#include "PirateRepository.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

void PirateRepository::create(std::unique_ptr<IShip> ship) {
    if (!ship) throw std::invalid_argument("Cannot create null ship");
    
    std::string id = ship->get_ID();
    if (id.empty()) throw std::invalid_argument("Ship must have an ID");
    if (exists(id)) throw std::runtime_error("Pirate ship with ID " + id + " already exists");
    if (ship->is_convoy()) throw std::invalid_argument("Cannot add convoy ship to pirate repository");
    
    ships_[id] = std::move(ship);
}

std::unique_ptr<IShip> PirateRepository::read(const std::string& id) const {
    auto it = ships_.find(id);
    if (it != ships_.end() && it->second) return it->second->clone();
    return nullptr;
}

std::vector<std::unique_ptr<IShip>> PirateRepository::read_all() const {
    std::vector<std::unique_ptr<IShip>> result;
    for (const auto& [id, ship] : ships_) {
        if (ship) result.push_back(ship->clone());
    }
    return result;
}

bool PirateRepository::exists(const std::string& id) const {
    return ships_.find(id) != ships_.end();
}

size_t PirateRepository::count() const {
    return ships_.size();
}

void PirateRepository::update(std::unique_ptr<IShip> ship) {
    if (!ship) throw std::invalid_argument("Cannot update null ship");
    
    std::string id = ship->get_ID();
    if (id.empty()) throw std::invalid_argument("Ship must have an ID");
    if (!exists(id)) throw std::runtime_error("Pirate ship with ID " + id + " not found");
    if (ship->is_convoy()) throw std::invalid_argument("Cannot update with convoy ship");
    
    ships_[id] = std::move(ship);
}

void PirateRepository::remove(const std::string& id) {
    ships_.erase(id);
}

void PirateRepository::clear() {
    ships_.clear();
}

std::vector<IShip*> PirateRepository::get_ships_in_range(const Vector& position, double range) const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) {
            double distance = ship->get_distance_to(position);
            if (distance <= range) result.push_back(ship.get());
        }
    }
    return result;
}

std::vector<IShip*> PirateRepository::get_ships_by_type(const std::string& type) const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->get_type() == type) result.push_back(ship.get());
    }
    return result;
}

std::vector<IShip*> PirateRepository::get_alive_ships() const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) result.push_back(ship.get());
    }
    return result;
}

std::vector<IShip*> PirateRepository::get_damaged_ships() const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive() && ship->get_health() < ship->get_max_health()) result.push_back(ship.get());
    }
    return result;
}

std::vector<IShip*> PirateRepository::get_cargo_ships() const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && (ship->get_type() == "transport" || ship->get_type() == "war")) result.push_back(ship.get());
    }
    return result;
}

std::vector<IShip*> PirateRepository::get_attack_ships() const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship && (ship->get_type() == "guard" || ship->get_type() == "war")) result.push_back(ship.get());
    }
    return result;
}

IShip* PirateRepository::get_strongest_ship() const {
    IShip* strongest = nullptr;
    double max_health = 0.0;
    
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) {
            double health = ship->get_health();
            if (health > max_health) {
                max_health = health;
                strongest = ship.get();
            }
        }
    }
    
    return strongest;
}

IShip* PirateRepository::get_weakest_ship() const {
    IShip* weakest = nullptr;
    double min_health = std::numeric_limits<double>::max();
    
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) {
            double health = ship->get_health();
            if (health < min_health) {
                min_health = health;
                weakest = ship.get();
            }
        }
    }
    
    return weakest;
}

IShip* PirateRepository::get_closest_ship_to(const Vector& position) const {
    IShip* closest = nullptr;
    double min_distance = std::numeric_limits<double>::max();
    
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) {
            double distance = ship->get_distance_to(position);
            if (distance < min_distance) {
                min_distance = distance;
                closest = ship.get();
            }
        }
    }
    
    return closest;
}

IShip* PirateRepository::get_fastest_ship() const {
    IShip* fastest = nullptr;
    double max_speed = -0.1;
    
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) {
            double speed = ship->get_speed();
            if (speed > max_speed) {
                max_speed = speed;
                fastest = ship.get();
            }
        }
    }
    
    return fastest;
}

IShip* PirateRepository::get_ship_ptr(const std::string& id) const {
    auto it = ships_.find(id);
    return (it != ships_.end()) ? it->second.get() : nullptr;
}

std::vector<IShip*> PirateRepository::get_all_ship_ptrs() const {
    std::vector<IShip*> result;
    for (const auto& [id, ship] : ships_) {
        if (ship) result.push_back(ship.get());
    }
    return result;
}

bool PirateRepository::is_ship_alive(const std::string& id) const {
    IShip* ship = get_ship_ptr(id);
    return ship && ship->is_alive();
}

size_t PirateRepository::count_alive() const {
    size_t count = 0;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->is_alive()) count++;
    }
    return count;
}

size_t PirateRepository::count_by_type(const std::string& type) const {
    size_t count = 0;
    for (const auto& [id, ship] : ships_) {
        if (ship && ship->get_type() == type) count++;
    }
    return count;
}

double PirateRepository::get_total_health() const {
    double total = 0.0;
    for (const auto& [id, ship] : ships_) {
        if (ship) total += ship->get_health();
    }
    return total;
}

double PirateRepository::get_average_health() const {
    size_t alive_count = count_alive();
    if (alive_count == 0) return 0.0;
    
    double total = get_total_health();
    return total / alive_count;
}

bool PirateRepository::validate_pirate_ship(const IShip* ship) const {
    return ship && !ship->is_convoy();
}
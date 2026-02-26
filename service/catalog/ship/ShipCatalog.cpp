#include "ShipCatalog.hpp"
#include <algorithm>
#include <stdexcept>

void ShipCatalog::initialize_default_templates() {
    ShipTemplate small_transport;
    small_transport.id = "transport_small";
    small_transport.display_name = "Малый транспорт";
    small_transport.type = "transport";
    small_transport.description = "Легкий и быстрый, но маловместительный";
    small_transport.max_speed = 30.0;
    small_transport.max_health = 120.0;
    small_transport.cost = 10000.0;
    small_transport.max_cargo = 500.0;
    small_transport.speed_reduction_factor = 0.08;
    small_transport.default_captain = Military("Лейтенант Иванов", "Лейтенант");
    templates_.push_back(small_transport);
    
    ShipTemplate medium_transport;
    medium_transport.id = "transport_medium";
    medium_transport.display_name = "Средний транспорт";
    medium_transport.type = "transport";
    medium_transport.description = "Сбалансированный по всем параметрам";
    medium_transport.max_speed = 25.0;
    medium_transport.max_health = 180.0;
    medium_transport.cost = 20000.0;
    medium_transport.max_cargo = 1000.0;
    medium_transport.speed_reduction_factor = 0.10;
    medium_transport.default_captain = Military("Капитан Смирнов", "Капитан");
    templates_.push_back(medium_transport);
    
    ShipTemplate large_transport;
    large_transport.id = "transport_large";
    large_transport.display_name = "Большой транспорт";
    large_transport.type = "transport";
    large_transport.description = "Вместительный, но медленный";
    large_transport.max_speed = 20.0;
    large_transport.max_health = 250.0;
    large_transport.cost = 30000.0;
    large_transport.max_cargo = 1500.0;
    large_transport.speed_reduction_factor = 0.12;
    large_transport.default_captain = Military("Майор Воронов", "Майор");
    templates_.push_back(large_transport);
    
    ShipTemplate fast_guard;
    fast_guard.id = "guard_fast";
    fast_guard.display_name = "Быстрый сторожевой";
    fast_guard.type = "guard";
    fast_guard.description = "Идеален для разведки и перехвата";
    fast_guard.max_speed = 45.0;
    fast_guard.max_health = 100.0;
    fast_guard.cost = 15000.0;
    fast_guard.default_captain = Military("Лейтенант Иванов", "Лейтенант");
    templates_.push_back(fast_guard);
    
    ShipTemplate medium_guard;
    medium_guard.id = "guard_medium";
    medium_guard.display_name = "Средний сторожевой";
    medium_guard.type = "guard";
    medium_guard.description = "Универсальный корабль сопровождения";
    medium_guard.max_speed = 35.0;
    medium_guard.max_health = 150.0;
    medium_guard.cost = 25000.0;
    medium_guard.default_captain = Military("Капитан Смирнов", "Капитан");
    templates_.push_back(medium_guard);
    
    ShipTemplate heavy_guard;
    heavy_guard.id = "guard_heavy";
    heavy_guard.display_name = "Тяжелый сторожевой";
    heavy_guard.type = "guard";
    heavy_guard.description = "Мощный корабль для серьезных боев";
    heavy_guard.max_speed = 28.0;
    heavy_guard.max_health = 220.0;
    heavy_guard.cost = 40000.0;
    heavy_guard.default_captain = Military("Майор Воронов", "Майор");
    templates_.push_back(heavy_guard);

    ShipTemplate light_wartransport;
    light_wartransport.id = "war_light";
    light_wartransport.display_name = "Легкий военный транспорт";
    light_wartransport.type = "war";
    light_wartransport.description = "Военный транспорт с базовым вооружением";
    light_wartransport.max_speed = 28.0;
    light_wartransport.max_health = 200.0;
    light_wartransport.cost = 25000.0;
    light_wartransport.max_cargo = 500.0;
    light_wartransport.speed_reduction_factor = 0.09;
    light_wartransport.default_captain = Military("Капитан Смирнов", "Капитан");
    templates_.push_back(light_wartransport);
    
    ShipTemplate heavy_wartransport;
    heavy_wartransport.id = "war_heavy";
    heavy_wartransport.display_name = "Тяжелый военный транспорт";
    heavy_wartransport.type = "war";
    heavy_wartransport.description = "Мощный транспорт с серьезным вооружением";
    heavy_wartransport.max_speed = 22.0;
    heavy_wartransport.max_health = 300.0;
    heavy_wartransport.cost = 45000.0;
    heavy_wartransport.max_cargo = 1000.0;
    heavy_wartransport.speed_reduction_factor = 0.11;
    heavy_wartransport.default_captain = Military("Майор Воронов", "Майор");
    templates_.push_back(heavy_wartransport);
}

ShipCatalog::ShipCatalog(std::unique_ptr<ShipFactoryManager> factory_manager) : factory_manager_(std::move(factory_manager)) {
    if (!factory_manager_) throw std::invalid_argument("Factory manager cannot be null");
    initialize_default_templates();
}

void ShipCatalog::add_template(const ShipTemplate& temp) {
    if (find_template_by_id(temp.id)) throw std::runtime_error("Template with ID '" + temp.id + "' already exists");
    if (temp.max_speed <= 0) throw std::invalid_argument("Max speed must be positive");
    if (temp.max_health <= 0) throw std::invalid_argument("Max health must be positive");
    if (temp.cost < 0) throw std::invalid_argument("Cost must be positive");
    templates_.push_back(temp);
}

const ShipTemplate* ShipCatalog::find_template_by_id(const std::string& id) const {
    auto it = std::find_if(templates_.begin(), templates_.end(), [&id](const ShipTemplate& temp) {
        return temp.id == id;
    });
    return it != templates_.end() ? &(*it) : nullptr;
}

std::vector<const ShipTemplate*> ShipCatalog::find_templates_by_type(const std::string& type) const {
    std::vector<const ShipTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.type == type) result.push_back(&temp);
    }
    return result;
}

std::vector<const ShipTemplate*> ShipCatalog::find_affordable_templates(double max_budget) const {
    std::vector<const ShipTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.cost <= max_budget) result.push_back(&temp);
    }
    return result;
}

const std::vector<ShipTemplate>& ShipCatalog::get_all_templates() const {
    return templates_;
}

size_t ShipCatalog::get_template_count() const {
    return templates_.size();
}

std::unique_ptr<IShip> ShipCatalog::create_ship(const std::string& template_id, bool is_convoy, const Vector& position) const {
    const ShipTemplate* temp = find_template_by_id(template_id);
    if (!temp) throw std::runtime_error("Template not found: " + template_id);
    
    auto ship = temp->create_ship(factory_manager_.get(), is_convoy);
    if (ship) {
        ship->set_convoy(is_convoy);
        ship->set_position(position);
    }
    return ship;
}

std::vector<std::unique_ptr<IShip>> ShipCatalog::create_ships(const std::string& template_id, size_t count, bool is_convoy) const {
    std::vector<std::unique_ptr<IShip>> ships;
    ships.reserve(count);
    
    for (size_t i = 0; i < count; ++i) {
        try {
            auto ship = create_ship(template_id, is_convoy);
            if (ship) ships.push_back(std::move(ship)); 
        }
        catch (const std::exception& e) {
            throw;
        }
    }
    return ships;
}

bool ShipCatalog::is_template_available(const std::string& template_id) const {
    return find_template_by_id(template_id) != nullptr;
}

double ShipCatalog::calculate_total_cost(const std::vector<std::string>& template_ids) const {
    double total = 0.0;
    for (const auto& id : template_ids) {
        const ShipTemplate* temp = find_template_by_id(id);
        if (temp) total += temp->cost;
    }
    return total;
}

bool ShipCatalog::validate_purchase(const std::vector<std::string>& template_ids, double budget) const {
    return calculate_total_cost(template_ids) <= budget;
}

size_t ShipCatalog::count_by_type(const std::string& type) const {
    return std::count_if(templates_.begin(), templates_.end(), [&type](const ShipTemplate& temp) {
        return temp.type == type;
    });
}

double ShipCatalog::get_min_cost() const {
    if (templates_.empty()) return 0.0;
    return std::min_element(templates_.begin(), templates_.end(), [](const ShipTemplate& a, const ShipTemplate& b) {
        return a.cost < b.cost;
    })->cost;
}

double ShipCatalog::get_max_cost() const {
    if (templates_.empty()) return 0.0;
    return std::max_element(templates_.begin(), templates_.end(), [](const ShipTemplate& a, const ShipTemplate& b) {
        return a.cost < b.cost;
    })->cost;
}
#include "WeaponCatalog.hpp"
#include <algorithm>
#include <stdexcept>

void WeaponCatalog::initialize_default_templates() {
    WeaponTemplate light_gun;
    light_gun.id = "gun_light";
    light_gun.display_name = "Легкая пушка";
    light_gun.type = "gun";
    light_gun.description = "Быстрая, но слабая пушка";
    light_gun.damage = 15.0;
    light_gun.range = 6.0;
    light_gun.fire_rate = 3;
    light_gun.max_ammo = 100;
    light_gun.cost = 3000.0;
    light_gun.accuracy = 0.75;
    templates_.push_back(light_gun);

    WeaponTemplate medium_gun;
    medium_gun.id = "gun_medium";
    medium_gun.display_name = "Средняя пушка";
    medium_gun.type = "gun";
    medium_gun.description = "Универсальная пушка";
    medium_gun.damage = 25.0;
    medium_gun.range = 8.0;
    medium_gun.fire_rate = 2;
    medium_gun.max_ammo = 100;
    medium_gun.cost = 5000.0;
    medium_gun.accuracy = 0.8;
    templates_.push_back(medium_gun);

    WeaponTemplate heavy_gun;
    heavy_gun.id = "gun_heavy";
    heavy_gun.display_name = "Тяжелая пушка";
    heavy_gun.type = "gun";
    heavy_gun.description = "Мощная, но медленная пушка";
    heavy_gun.damage = 40.0;
    heavy_gun.range = 10.0;
    heavy_gun.fire_rate = 1;
    heavy_gun.max_ammo = 100;
    heavy_gun.cost = 8000.0;
    heavy_gun.accuracy = 0.85;
    templates_.push_back(heavy_gun);

    WeaponTemplate light_rocket;
    light_rocket.id = "rocket_light";
    light_rocket.display_name = "Легкая ракета";
    light_rocket.type = "rocket";
    light_rocket.description = "Быстрая ракета с небольшим уроном";
    light_rocket.damage = 30.0;
    light_rocket.range = 8.0;
    light_rocket.fire_rate = 1;
    light_rocket.max_ammo = 80;
    light_rocket.cost = 6000.0;
    light_rocket.accuracy = 0.9;
    light_rocket.explosion_radius = 0.5;
    templates_.push_back(light_rocket);

    WeaponTemplate heavy_rocket;
    heavy_rocket.id = "rocket_heavy";
    heavy_rocket.display_name = "Тяжелая ракета";
    heavy_rocket.type = "rocket";
    heavy_rocket.description = "Мощная ракета с большим радиусом поражения";
    heavy_rocket.damage = 50.0;
    heavy_rocket.range = 12.0;
    heavy_rocket.fire_rate = 1;
    heavy_rocket.max_ammo = 100;
    heavy_rocket.cost = 10000.0;
    heavy_rocket.accuracy = 0.85;
    heavy_rocket.explosion_radius = 1.5;
    templates_.push_back(heavy_rocket);
}

WeaponCatalog::WeaponCatalog(std::unique_ptr<WeaponFactoryManager> factory_manager) : factory_manager_(std::move(factory_manager)) {
    if (!factory_manager_) throw std::invalid_argument("Factory manager cannot be null");
    initialize_default_templates();
}

void WeaponCatalog::add_template(const WeaponTemplate& temp) {
    if (find_template_by_id(temp.id)) throw std::runtime_error("Template with ID '" + temp.id + "' already exists");
    if (temp.damage <= 0) throw std::invalid_argument("Damage must be positive");
    if (temp.range <= 0) throw std::invalid_argument("Range must be positive");
    if (temp.fire_rate <= 0) throw std::invalid_argument("Fire rate must be positive");
    if (temp.max_ammo <= 0) throw std::invalid_argument("Max ammo must be positive");
    if (temp.cost < 0) throw std::invalid_argument("Cost must be positive");
    if (temp.accuracy < 0 || temp.accuracy > 1) throw std::invalid_argument("Accuracy must be between 0 and 1");
    templates_.push_back(temp);
}

const WeaponTemplate* WeaponCatalog::find_template_by_id(const std::string& id) const {
    auto it = std::find_if(templates_.begin(), templates_.end(), [&id](const WeaponTemplate& temp) {
        return temp.id == id;
    });
    return it != templates_.end() ? &(*it) : nullptr;
}

std::vector<const WeaponTemplate*> WeaponCatalog::find_templates_by_type(const std::string& type) const {
    std::vector<const WeaponTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.type == type) result.push_back(&temp);
    }
    return result;
}

std::vector<const WeaponTemplate*> WeaponCatalog::find_affordable_templates(double max_budget) const {
    std::vector<const WeaponTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.cost <= max_budget) result.push_back(&temp);
    }
    return result;
}

std::vector<const WeaponTemplate*> WeaponCatalog::find_by_min_damage(double min_damage) const {
    std::vector<const WeaponTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.damage >= min_damage) result.push_back(&temp);
    }
    return result;
}

std::vector<const WeaponTemplate*> WeaponCatalog::find_by_min_range(double min_range) const {
    std::vector<const WeaponTemplate*> result;
    for (const auto& temp : templates_) {
        if (temp.range >= min_range) result.push_back(&temp);
    }
    return result;
}

const std::vector<WeaponTemplate>& WeaponCatalog::get_all_templates() const {
    return templates_;
}

size_t WeaponCatalog::get_template_count() const {
    return templates_.size();
}

std::unique_ptr<IWeapon> WeaponCatalog::create_weapon(const std::string& template_id) const {
    const WeaponTemplate* temp = find_template_by_id(template_id);
    if (!temp) throw std::runtime_error("Template not found: " + template_id);

    return temp->create_weapon(factory_manager_.get());
}

std::vector<std::unique_ptr<IWeapon>> WeaponCatalog::create_weapons(const std::string& template_id, size_t count) const {
    std::vector<std::unique_ptr<IWeapon>> weapons;
    weapons.reserve(count);
    
    for (size_t i = 0; i < count; ++i) {
        try {
            auto weapon = create_weapon(template_id);
            if (weapon) weapons.push_back(std::move(weapon));
        } catch (const std::exception& e) {
            throw;
        }
    }
    return weapons;
}

bool WeaponCatalog::is_template_available(const std::string& template_id) const {
    return find_template_by_id(template_id) != nullptr;
}

double WeaponCatalog::calculate_total_cost(const std::vector<std::string>& template_ids) const {
    double total = 0.0;
    for (const auto& id : template_ids) {
        const WeaponTemplate* temp = find_template_by_id(id);
        if (temp) total += temp->cost;
    }
    return total;
}

bool WeaponCatalog::validate_purchase(const std::vector<std::string>& template_ids, double budget) const {
    return calculate_total_cost(template_ids) <= budget;
}

size_t WeaponCatalog::count_by_type(const std::string& type) const {
    return std::count_if(templates_.begin(), templates_.end(), [&type](const WeaponTemplate& temp) {
        return temp.type == type;
    });
}

double WeaponCatalog::get_min_cost() const {
    if (templates_.empty()) return 0.0;
    return std::min_element(templates_.begin(), templates_.end(), [](const WeaponTemplate& a, const WeaponTemplate& b) {
        return a.cost < b.cost;
    })->cost;
}

double WeaponCatalog::get_max_cost() const {
    if (templates_.empty()) return 0.0;
    return std::max_element(templates_.begin(), templates_.end(), [](const WeaponTemplate& a, const WeaponTemplate& b) {
        return a.cost < b.cost;
    })->cost;
}

double WeaponCatalog::get_max_damage() const {
    if (templates_.empty()) return 0.0;
    return std::max_element(templates_.begin(), templates_.end(), [](const WeaponTemplate& a, const WeaponTemplate& b) {
        return a.damage < b.damage;
    })->damage;
}

double WeaponCatalog::get_max_range() const {
    if (templates_.empty()) return 0.0;
    return std::max_element(templates_.begin(), templates_.end(), [](const WeaponTemplate& a, const WeaponTemplate& b) {
        return a.range < b.range;
    })->range;
}
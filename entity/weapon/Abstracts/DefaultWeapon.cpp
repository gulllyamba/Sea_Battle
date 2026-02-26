#include "DefaultWeapon.hpp"

#include <random>
#include <sstream>
#include <iomanip>

void DefaultWeapon::validate_parameters() const {
    if (damage <= 0.0) throw std::invalid_argument("Damage must be positive");
    if (range <= 0.0) throw std::invalid_argument("Range must be positive");
    if (fire_rate == 0) throw std::invalid_argument("Fire rate must be positive");
    if (cost < 0.0) throw std::invalid_argument("Cost cannot be negative");
}

DefaultWeapon::DefaultWeapon(
    const std::string& type,
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius) : 
    type(type),
    name(name),
    damage(damage),
    range(range),
    fire_rate(fire_rate),
    max_ammo(max_ammo),
    current_ammo(max_ammo),
    cost(cost),
    accuracy((accuracy < 0.0) ? 0.0 : (accuracy > 1.0) ? 1.0 : accuracy),
    explosion_radius((explosion_radius < 0.0) ? 0.0 : explosion_radius
) {
    validate_parameters();
}

std::string DefaultWeapon::get_type() const {
    return type;
}
std::string DefaultWeapon::get_name() const {
    return name;
}
double DefaultWeapon::get_damage() const {
    return damage;
}
double DefaultWeapon::get_range() const {
    return range;
}
size_t DefaultWeapon::get_fire_rate() const {
    return fire_rate;
}
size_t DefaultWeapon::get_max_ammo() const {
    return max_ammo;
}
size_t DefaultWeapon::get_current_ammo() const {
    return current_ammo;
}
double DefaultWeapon::get_cost() const {
    return cost;
}
double DefaultWeapon::get_accuracy() const {
    return accuracy;
}
double DefaultWeapon::get_explosion_radius() const {
    return explosion_radius;
}

void DefaultWeapon::set_current_ammo(size_t ammo) {
    current_ammo = (ammo > max_ammo) ? max_ammo : ammo;
}
void DefaultWeapon::set_damage(double new_damage) {
    if (new_damage <= 0.0) damage = 0.0;
    else damage = new_damage;
}
void DefaultWeapon::set_range(double new_range) {
    if (new_range <= 0.0) range = 0.0;
    else range = new_range;
}
void DefaultWeapon::set_accuracy(double new_accuracy) {
    accuracy = (new_accuracy < 0.0) ? 0.0 : (new_accuracy > 1.0) ? 1.0 : new_accuracy;
}

std::string DefaultWeapon::get_description() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << name << " [Урон: " << damage
        << ", Дальность: " << range
        << ", Скорострельность: " << fire_rate
        << ", Боезапас: " << current_ammo << "/" << max_ammo
        << ", Точность: " << std::setprecision(0) << (accuracy * 100) << "%"
        << std::setprecision(1) << ", Стоимость: " << cost << "]";
    return oss.str();
}
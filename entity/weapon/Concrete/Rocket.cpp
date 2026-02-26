#include "Rocket.hpp"

Rocket::Rocket(
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius) :
    DefaultWeapon("rocket", name, damage, range, fire_rate, max_ammo, cost, accuracy, explosion_radius) {}

std::unique_ptr<IWeapon> Rocket::clone() const {
    return std::make_unique<Rocket>(*this);
}
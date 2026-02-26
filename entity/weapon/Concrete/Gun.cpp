#include "Gun.hpp"

Gun::Gun(
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius) :
    DefaultWeapon("gun", name, damage, range, fire_rate, max_ammo, cost, accuracy, explosion_radius) {}

std::unique_ptr<IWeapon> Gun::clone() const {
    return std::make_unique<Gun>(*this);
}
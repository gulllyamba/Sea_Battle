#include "RocketFactory.hpp"

RocketFactory::RocketFactory() : prototype_(std::make_unique<Rocket>()) {}

std::unique_ptr<IWeapon> RocketFactory::create_weapon() const {
    return prototype_->clone();
}

std::unique_ptr<IWeapon> RocketFactory::create_weapon(
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius
) const {
    return std::make_unique<Rocket>(name, damage, range, fire_rate, max_ammo, cost, accuracy, explosion_radius);
}

void RocketFactory::set_prototype(std::unique_ptr<Rocket> prototype) {
    prototype_ = std::move(prototype);
}
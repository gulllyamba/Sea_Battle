#include "GunFactory.hpp"

GunFactory::GunFactory() : prototype_(std::make_unique<Gun>()) {}

std::unique_ptr<IWeapon> GunFactory::create_weapon() const {
    return prototype_->clone();
}

std::unique_ptr<IWeapon> GunFactory::create_weapon(
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius
) const {
    return std::make_unique<Gun>(name, damage, range, fire_rate, max_ammo, cost, accuracy, explosion_radius);
}

void GunFactory::set_prototype(std::unique_ptr<Gun> prototype) {
    prototype_ = std::move(prototype);
}
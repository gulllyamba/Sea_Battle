#include "WeaponFactoryManager.hpp"

void WeaponFactoryManager::register_factory(const std::string& type, std::unique_ptr<IWeaponFactory> factory) {
    factories_[type] = std::move(factory);
}

WeaponFactoryManager::WeaponFactoryManager() {
    register_factory("gun", std::make_unique<GunFactory>());
    register_factory("rocket", std::make_unique<RocketFactory>());
}

std::unique_ptr<IWeapon> WeaponFactoryManager::create_weapon(const std::string& type) const {
    auto it = factories_.find(type);
    if (it != factories_.end()) return it->second->create_weapon();
    return nullptr;
}

std::unique_ptr<IWeapon> WeaponFactoryManager::create_weapon(
    const std::string& type,
    const std::string& name,
    double damage,
    double range,
    size_t fire_rate,
    size_t max_ammo,
    double cost,
    double accuracy,
    double explosion_radius
) const {
    auto it = factories_.find(type);
    if (it != factories_.end()) {
        return it->second->create_weapon(
            name,
            damage,
            range,
            fire_rate,
            max_ammo,
            cost,
            accuracy,
            explosion_radius
        );
    }
    return nullptr;
}

IWeaponFactory* WeaponFactoryManager::get_factory(const std::string& type) const {
    auto it = factories_.find(type);
    return (it != factories_.end()) ? it->second.get() : nullptr;
}

bool WeaponFactoryManager::has_factory(const std::string& type) const {
    return factories_.find(type) != factories_.end();
}
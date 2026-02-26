#include "WeaponMapperManager.hpp"
#include "../FromDTO/GunMapper.hpp"
#include "../FromDTO/RocketMapper.hpp"

void WeaponMapperManager::register_mapper(const std::string& type, std::unique_ptr<IWeaponMapper> mapper) {
    mappers_[type] = std::move(mapper);
}

WeaponMapperManager::WeaponMapperManager() {
    register_mapper("gun", std::make_unique<GunMapper>());
    register_mapper("rocket", std::make_unique<RocketMapper>());
}

std::unique_ptr<IWeapon> WeaponMapperManager::create_weapon(const WeaponDTO& weapon_dto) const {
    auto it = mappers_.find(weapon_dto.type);
    if (it != mappers_.end()) return it->second->transform(weapon_dto);
    return nullptr;
}
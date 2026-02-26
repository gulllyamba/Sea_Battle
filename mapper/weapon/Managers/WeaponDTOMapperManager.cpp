#include "WeaponDTOMapperManager.hpp"
#include "../ToDTO/GunDTOMapper.hpp"
#include "../ToDTO/RocketDTOMapper.hpp"

void WeaponDTOMapperManager::register_mapper(const std::string& type, std::unique_ptr<IWeaponDTOMapper> mapper) {
    mappers_[type] = std::move(mapper);
}

WeaponDTOMapperManager::WeaponDTOMapperManager() {
    register_mapper("gun", std::make_unique<GunDTOMapper>());
    register_mapper("rocket", std::make_unique<RocketDTOMapper>());
}

WeaponDTO WeaponDTOMapperManager::create_weapon_dto(const IWeapon* weapon) const {
    auto it = mappers_.find(weapon->get_type());
    if (it != mappers_.end()) return it->second->transform(weapon);
    return WeaponDTO{};
}
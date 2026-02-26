#include "GunDTOMapper.hpp"

WeaponDTO GunDTOMapper::transform(const IWeapon* weapon) {
    WeaponDTO weapon_dto;
    weapon_dto.type = weapon->get_type();
    weapon_dto.name = weapon->get_name();
    weapon_dto.damage = weapon->get_damage();
    weapon_dto.range = weapon->get_range();
    weapon_dto.fire_rate = weapon->get_fire_rate();
    weapon_dto.max_ammo = weapon->get_max_ammo();
    weapon_dto.current_ammo = weapon->get_current_ammo();
    weapon_dto.cost = weapon->get_cost();
    weapon_dto.accuracy = weapon->get_accuracy();
    weapon_dto.explosion_radius = weapon->get_explosion_radius();

    return weapon_dto;
}
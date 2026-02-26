#include "GunMapper.hpp"
#include "../../../entity/weapon/Concrete/Gun.hpp"

std::unique_ptr<IWeapon> GunMapper::transform(const WeaponDTO& weapon_dto) {
    std::unique_ptr<IWeapon> weapon = std::make_unique<Gun>(
        weapon_dto.name,
        weapon_dto.damage,
        weapon_dto.range,
        weapon_dto.fire_rate,
        weapon_dto.max_ammo,
        weapon_dto.cost,
        weapon_dto.accuracy,
        weapon_dto.explosion_radius
    );
    weapon->set_current_ammo(weapon_dto.current_ammo);
    
    return weapon;
}
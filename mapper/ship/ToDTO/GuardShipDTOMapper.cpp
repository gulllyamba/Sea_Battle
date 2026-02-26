#include "GuardShipDTOMapper.hpp"
#include "../../../entity/ship/Concrete/GuardShip.hpp"
#include "../../weapon/Managers/WeaponDTOMapperManager.hpp"
#include <vector>

ShipDTO GuardShipDTOMapper::transform(const IShip* ship) {
    ShipDTO ship_dto;
    ship_dto.type = "guard";
    ship_dto.id = ship->get_ID();
    ship_dto.name = ship->get_name();
    ship_dto.captain = ship->get_captain();
    ship_dto.max_speed = ship->get_max_speed();
    ship_dto.current_speed = ship->get_speed();
    ship_dto.cost = ship->get_cost();
    ship_dto.position = ship->get_position();
    ship_dto.max_health = ship->get_max_health();
    ship_dto.current_health = ship->get_health();
    ship_dto.is_alive = ship->is_alive();
    ship_dto.is_convoy = ship->is_convoy();

    const GuardShip* guard_ship = dynamic_cast<const GuardShip*>(ship);

    LookupTable<PlaceForWeapon, WeaponDTO> weapons;
    WeaponDTOMapperManager manager;
    std::vector<PlaceForWeapon> places = {PlaceForWeapon::bow, PlaceForWeapon::port, PlaceForWeapon::starboard, PlaceForWeapon::stern};
    for (const auto& place : places) {
        if (guard_ship->has_weapon_in_place(place)) {
            weapons[place] = manager.create_weapon_dto(guard_ship->get_weapon_in_place(place));
        }
    }
    ship_dto.weapons = weapons;

    return ship_dto;
}
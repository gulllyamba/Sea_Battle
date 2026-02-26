#include "WarShipDTOMapper.hpp"
#include "../../../entity/ship/Concrete/WarShip.hpp"
#include "../../weapon/Managers/WeaponDTOMapperManager.hpp"
#include <vector>

ShipDTO WarShipDTOMapper::transform(const IShip* ship) {
    ShipDTO ship_dto;
    ship_dto.type = "war";
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

    const WarShip* war_ship = dynamic_cast<const WarShip*>(ship);
    ship_dto.max_cargo = war_ship->get_max_cargo();
    ship_dto.current_cargo = war_ship->get_cargo();
    ship_dto.speed_reduction_factor = war_ship->get_speed_reduction_factor();

    LookupTable<PlaceForWeapon, WeaponDTO> weapons;
    WeaponDTOMapperManager manager;
    std::vector<PlaceForWeapon> places = {PlaceForWeapon::bow, PlaceForWeapon::port, PlaceForWeapon::starboard, PlaceForWeapon::stern};
    for (const auto& place : places) {
        if (war_ship->has_weapon_in_place(place)) {
            weapons[place] = manager.create_weapon_dto(war_ship->get_weapon_in_place(place));
        }
    }
    ship_dto.weapons = weapons;

    return ship_dto;
}
#include "TransportShipDTOMapper.hpp"
#include "../../../entity/ship/Concrete/TransportShip.hpp"

ShipDTO TransportShipDTOMapper::transform(const IShip* ship) {
    ShipDTO ship_dto;
    ship_dto.type = "transport";
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

    const TransportShip* transport_ship = dynamic_cast<const TransportShip*>(ship);
    ship_dto.max_cargo = transport_ship->get_max_cargo();
    ship_dto.current_cargo = transport_ship->get_cargo();
    ship_dto.speed_reduction_factor = transport_ship->get_speed_reduction_factor();

    return ship_dto;
}
#include "TransportShipMapper.hpp"
#include "../../../entity/ship/Concrete/TransportShip.hpp"

std::unique_ptr<IShip> TransportShipMapper::transform(const ShipDTO& ship_dto) {
    std::unique_ptr<TransportShip> ship = std::make_unique<TransportShip>(
        ship_dto.name,
        ship_dto.captain,
        ship_dto.max_speed,
        ship_dto.max_health,
        ship_dto.cost,
        ship_dto.id,
        ship_dto.max_cargo,
        ship_dto.position
    );
    ship->set_speed(ship_dto.current_speed);
    ship->set_health(ship_dto.current_health);
    ship->set_cargo(ship_dto.current_cargo);
    ship->set_speed_reduction_factor(ship_dto.speed_reduction_factor);

    return ship;
}
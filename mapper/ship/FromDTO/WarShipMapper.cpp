#include "WarShipMapper.hpp"
#include "../../../entity/ship/Concrete/WarShip.hpp"
#include "../../weapon/Managers/WeaponMapperManager.hpp"

std::unique_ptr<IShip> WarShipMapper::transform(const ShipDTO& ship_dto) {
    std::unique_ptr<WarShip> ship = std::make_unique<WarShip>(
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

    for (auto& node : ship_dto.weapons) {
        WeaponMapperManager manager;
        ship->set_weapon_in_place(node.first, manager.create_weapon(node.second));
    }
    
    return ship;
}
#include "GuardShipMapper.hpp"
#include "../../../entity/ship/Concrete/GuardShip.hpp"
#include "../../weapon/Managers/WeaponMapperManager.hpp"

std::unique_ptr<IShip> GuardShipMapper::transform(const ShipDTO& ship_dto) {
    std::unique_ptr<GuardShip> ship = std::make_unique<GuardShip>(
        ship_dto.name,
        ship_dto.captain,
        ship_dto.max_speed,
        ship_dto.max_health,
        ship_dto.cost,
        ship_dto.id,
        ship_dto.is_convoy,
        ship_dto.position
    );
    ship->set_speed(ship_dto.current_speed);
    ship->set_health(ship_dto.current_health);

    for (auto& node : ship_dto.weapons) {
        WeaponMapperManager manager;
        ship->set_weapon_in_place(node.first, manager.create_weapon(node.second));
    }
    
    return ship;
}
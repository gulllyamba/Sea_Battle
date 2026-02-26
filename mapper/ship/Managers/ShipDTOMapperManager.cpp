#include "ShipDTOMapperManager.hpp"
#include "../ToDTO/GuardShipDTOMapper.hpp"
#include "../ToDTO/WarShipDTOMapper.hpp"
#include "../ToDTO/TransportShipDTOMapper.hpp"

void ShipDTOMapperManager::register_mapper(const std::string& type, std::unique_ptr<IShipDTOMapper> mapper) {
    mappers_[type] = std::move(mapper);
}

ShipDTOMapperManager::ShipDTOMapperManager() {
    register_mapper("guard", std::make_unique<GuardShipDTOMapper>());
    register_mapper("war", std::make_unique<WarShipDTOMapper>());
    register_mapper("transport", std::make_unique<TransportShipDTOMapper>());
}

ShipDTO ShipDTOMapperManager::create_ship_dto(const IShip* ship) const {
    auto it = mappers_.find(ship->get_type());
    if (it != mappers_.end()) return it->second->transform(ship);
    return ShipDTO{};
}
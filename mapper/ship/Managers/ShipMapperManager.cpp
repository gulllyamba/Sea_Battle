#include "ShipMapperManager.hpp"
#include "../FromDTO/GuardShipMapper.hpp"
#include "../FromDTO/WarShipMapper.hpp"
#include "../FromDTO/TransportShipMapper.hpp"

void ShipMapperManager::register_mapper(const std::string& type, std::unique_ptr<IShipMapper> mapper) {
    mappers_[type] = std::move(mapper);
}

ShipMapperManager::ShipMapperManager() {
    register_mapper("guard", std::make_unique<GuardShipMapper>());
    register_mapper("war", std::make_unique<WarShipMapper>());
    register_mapper("transport", std::make_unique<TransportShipMapper>());
}

std::unique_ptr<IShip> ShipMapperManager::create_ship(const ShipDTO& ship_dto) const {
    auto it = mappers_.find(ship_dto.type);
    if (it != mappers_.end()) return it->second->transform(ship_dto);
    return nullptr;
}
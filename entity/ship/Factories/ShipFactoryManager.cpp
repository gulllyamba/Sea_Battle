#include "ShipFactoryManager.hpp"
#include "GuardShipFactory.hpp"
#include "WarShipFactory.hpp"
#include "TransportShipFactory.hpp"
#include "../../../service/ID/ShipIDGenerator.hpp"

void ShipFactoryManager::register_factory(const std::string& type, std::unique_ptr<IShipFactory> factory) {
    factories_[type] = std::move(factory);
}

ShipFactoryManager::ShipFactoryManager() {
    register_factory("guard", std::make_unique<GuardShipFactory>());
    register_factory("war", std::make_unique<WarShipFactory>());
    register_factory("transport", std::make_unique<TransportShipFactory>());
}

std::unique_ptr<IShip> ShipFactoryManager::create_ship(const std::string& type, bool is_convoy) const {
    auto ship = create_ship_without_id(type, "", Military(), 0, 0, 0, is_convoy);
    if (ship) {
        if (is_convoy) ship->set_ID(ShipIDGenerator::generate_convoy_id());
        else ship->set_ID(ShipIDGenerator::generate_pirate_id());
    }
    return ship;
}

std::unique_ptr<IShip> ShipFactoryManager::create_ship(
    const std::string& type,
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    bool is_convoy,
    std::optional<double> max_cargo,
    const Vector& position
) const {
    auto ship = create_ship_without_id(type, name, captain, max_speed, max_health, cost, is_convoy, max_cargo, position);
    if (ship) {
        if (is_convoy) ship->set_ID(ShipIDGenerator::generate_convoy_id());
        else ship->set_ID(ShipIDGenerator::generate_pirate_id());
    }
    return ship;
}

std::unique_ptr<IShip> ShipFactoryManager::create_ship_without_id(
    const std::string& type,
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    bool is_convoy,
    std::optional<double> max_cargo,
    const Vector& position,
    const std::string& custom_id
) const {
    auto it = factories_.find(type);
    if (it != factories_.end()) {
        auto ship = it->second->create_ship(name, captain, max_speed, max_health, cost, is_convoy, max_cargo, position);
        if (ship && !custom_id.empty()) ship->set_ID(custom_id);
        return ship;
    }
    return nullptr;
}

IShipFactory* ShipFactoryManager::get_factory(const std::string& type) const {
    auto it = factories_.find(type);
    return (it != factories_.end()) ? it->second.get() : nullptr;
}

bool ShipFactoryManager::has_factory(const std::string& type) const {
    return factories_.find(type) != factories_.end();
}

void ShipFactoryManager::set_default_max_cargo(const std::string& type, double max_cargo) {
    auto factory = get_factory(type);
    if (factory) {
        if (auto war_factory = dynamic_cast<WarShipFactory*>(factory)) war_factory->set_default_max_cargo(max_cargo);
        else if (auto transport_factory = dynamic_cast<TransportShipFactory*>(factory)) transport_factory->set_default_max_cargo(max_cargo);
    }
}
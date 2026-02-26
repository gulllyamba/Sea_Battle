#include "TransportShipFactory.hpp"

TransportShipFactory::TransportShipFactory() : prototype_(std::make_unique<TransportShip>()) {}

std::unique_ptr<IShip> TransportShipFactory::create_ship() const {
    return prototype_->clone();
}

std::unique_ptr<IShip> TransportShipFactory::create_ship(
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    bool is_convoy,
    std::optional<double> max_cargo,
    const Vector& position
) const {
    double cargo_to_use = max_cargo.value_or(default_max_cargo_);
    return std::make_unique<TransportShip>(name, captain, max_speed, max_health, cost, "", cargo_to_use, position);
}

void TransportShipFactory::set_prototype(std::unique_ptr<TransportShip> prototype) {
    prototype_ = std::move(prototype);
}

void TransportShipFactory::set_default_max_cargo(double max_cargo) {
    if (max_cargo >= 0.0) default_max_cargo_ = max_cargo;
}
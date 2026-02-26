#include "WarShipFactory.hpp"

WarShipFactory::WarShipFactory() : prototype_(std::make_unique<WarShip>()) {}

std::unique_ptr<IShip> WarShipFactory::create_ship() const {
    return prototype_->clone();
}

std::unique_ptr<IShip> WarShipFactory::create_ship(
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
    return std::make_unique<WarShip>(name, captain, max_speed, max_health, cost, "", cargo_to_use, position);
}

void WarShipFactory::set_prototype(std::unique_ptr<WarShip> prototype) {
    prototype_ = std::move(prototype);
}

void WarShipFactory::set_default_max_cargo(double max_cargo) {
    if (max_cargo >= 0.0) default_max_cargo_ = max_cargo;
}
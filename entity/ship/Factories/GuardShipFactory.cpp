#include "GuardShipFactory.hpp"

GuardShipFactory::GuardShipFactory() : prototype_(std::make_unique<GuardShip>()) {}

std::unique_ptr<IShip> GuardShipFactory::create_ship() const {
    return prototype_->clone();
}

std::unique_ptr<IShip> GuardShipFactory::create_ship(
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    bool is_convoy,
    std::optional<double> max_cargo,
    const Vector& position
) const {
    return std::make_unique<GuardShip>(name, captain, max_speed, max_health, cost, "", is_convoy, position);
}

void GuardShipFactory::set_prototype(std::unique_ptr<GuardShip> prototype) {
    prototype_ = std::move(prototype);
}
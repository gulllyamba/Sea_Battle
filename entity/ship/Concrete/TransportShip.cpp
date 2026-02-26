#include "TransportShip.hpp"
#include <sstream>

TransportShip::TransportShip(
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    const std::string& id,
    double max_cargo,
    const Vector& position)
: DefaultShip(name, captain, max_speed, max_health, cost, id, true, position), DefaultCargo(max_cargo, 0.1) {}

std::string TransportShip::get_type() const {
    return "transport";
}

double TransportShip::get_speed() const {
    double reduction = current_cargo_ / max_cargo_ * get_speed_reduction_factor();
    return current_speed_ * (1.0 - reduction);
}

std::string TransportShip::get_description() const {
    std::ostringstream oss;
    oss << "Транспортный корабль: " << get_name() << "\n"
        << "Капитан: " << get_captain().FIO << "\n"
        << "Скорость: " << get_speed() << "/" << get_max_speed() << "\n"
        << "Здоровье: " << get_health() << "/" << get_max_health() << "\n"
        << "Груз: " << get_cargo() << "/" << get_max_cargo() << "\n"
        << "Стоимость: " << get_cost();
    return oss.str();
}

std::unique_ptr<IShip> TransportShip::clone() const {
    auto clone = std::make_unique<TransportShip>(name_, captain_, max_speed_, max_health_, cost_, id_, get_max_cargo(), position_);
    clone->set_cargo(get_cargo());
    return clone;
}

void TransportShip::accept(IShipVisitor* visitor) {
    visitor->visit(this);
}
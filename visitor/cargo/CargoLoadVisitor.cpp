#include "CargoLoadVisitor.hpp"
#include <stdexcept>
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"

CargoLoadVisitor::CargoLoadVisitor(double amount) : amount_(amount) {
    if (amount_ < 0) throw std::invalid_argument("Amount cannot be negative");
}

CargoLoadVisitor::~CargoLoadVisitor() = default;

void CargoLoadVisitor::visit(TransportShip* ship) {
    can_load_ = ship->can_add_cargo(amount_);
    if (can_load_) {
        ship->add_cargo(amount_);
        loaded_ = true;
    }
}

void CargoLoadVisitor::visit(GuardShip* ship) {
    can_load_ = false;
    loaded_ = false;
}

void CargoLoadVisitor::visit(WarShip* ship) {
    can_load_ = ship->can_add_cargo(amount_);
    if (can_load_) {
        ship->add_cargo(amount_);
        loaded_ = true;
    }
}

bool CargoLoadVisitor::can_load() const {
    return can_load_;
}

bool CargoLoadVisitor::is_loaded() const {
    return loaded_;
}
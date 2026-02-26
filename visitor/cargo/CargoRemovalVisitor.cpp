#include "CargoRemovalVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"
#include <stdexcept>

CargoRemovalVisitor::CargoRemovalVisitor(double amount) : amount_(amount) {
    if (amount_ < 0) throw std::invalid_argument("Amount cannot be negative");
}

CargoRemovalVisitor::~CargoRemovalVisitor() = default;

void CargoRemovalVisitor::visit(TransportShip* ship) {
    can_remove_ = ship->can_remove_cargo(amount_);
    if (can_remove_) {
        ship->remove_cargo(amount_);
        removed_ = true;
    }
}

void CargoRemovalVisitor::visit(GuardShip* ship) {
    can_remove_ = false;
    removed_ = false;
}

void CargoRemovalVisitor::visit(WarShip* ship) {
    can_remove_ = ship->can_remove_cargo(amount_);
    if (can_remove_) {
        ship->remove_cargo(amount_);
        removed_ = true;
    }
}

bool CargoRemovalVisitor::can_remove() const {
    return can_remove_;
}

bool CargoRemovalVisitor::is_removed() const {
    return removed_;
}
#include "CargoInfoVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"

CargoInfoVisitor::~CargoInfoVisitor() = default;

void CargoInfoVisitor::visit(TransportShip* ship) {
    max_cargo_ = ship->get_max_cargo();
    current_cargo_ = ship->get_cargo();
    speed_reduction_factor_ = ship->get_speed_reduction_factor();
}

void CargoInfoVisitor::visit(GuardShip* ship) {
    max_cargo_ = 0.0;
    current_cargo_ = 0.0;
    speed_reduction_factor_ = 0.0;
}

void CargoInfoVisitor::visit(WarShip* ship) {
    max_cargo_ = ship->get_max_cargo();
    current_cargo_ = ship->get_cargo();
    speed_reduction_factor_ = ship->get_speed_reduction_factor();
}

double CargoInfoVisitor::get_max_cargo() const {
    return max_cargo_;
}

double CargoInfoVisitor::get_current_cargo() const {
    return current_cargo_;
}

double CargoInfoVisitor::get_speed_reduction_factor() const {
    return speed_reduction_factor_;
}

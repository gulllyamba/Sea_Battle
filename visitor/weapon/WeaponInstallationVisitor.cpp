#include "WeaponInstallationVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"

WeaponInstallationVisitor::~WeaponInstallationVisitor() = default;

void WeaponInstallationVisitor::visit(TransportShip* ship) {
    can_install_ = false;
    installed_ = false;
}

void WeaponInstallationVisitor::visit(GuardShip* ship) {
    can_install_ = !ship->has_weapon_in_place(place_);
    if (can_install_ && weapon_) {
        ship->set_weapon_in_place(place_, std::move(weapon_));
        installed_ = true;
    }
}

void WeaponInstallationVisitor::visit(WarShip* ship) {
    can_install_ = !ship->has_weapon_in_place(place_);
    if (can_install_ && weapon_) {
        ship->set_weapon_in_place(place_, std::move(weapon_));
        installed_ = true;
    }
}

bool WeaponInstallationVisitor::can_install() const {
    return can_install_;
}

bool WeaponInstallationVisitor::is_installed() const {
    return installed_;
}
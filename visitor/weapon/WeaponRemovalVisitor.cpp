#include "WeaponRemovalVisitor.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"

WeaponRemovalVisitor::~WeaponRemovalVisitor() = default;

void WeaponRemovalVisitor::visit(TransportShip* ship) {
    removed_weapon_cost_ = 0.0;
    can_remove_ = false;
    removed_ = false;
}

void WeaponRemovalVisitor::visit(GuardShip* ship) {
    can_remove_ = ship->has_weapon_in_place(place_);
    if (can_remove_) {
        removed_weapon_cost_ = ship->get_weapon_in_place(place_)->get_cost();
        ship->remove_weapon_from_place(place_);
        removed_ = true;
    }
}

void WeaponRemovalVisitor::visit(WarShip* ship) {
    can_remove_ = ship->has_weapon_in_place(place_);
    if (can_remove_) {
        removed_weapon_cost_ = ship->get_weapon_in_place(place_)->get_cost();
        ship->remove_weapon_from_place(place_);
        removed_ = true;
    }
}

double WeaponRemovalVisitor::get_weapon_cost() const { 
    return removed_weapon_cost_; 
}

bool WeaponRemovalVisitor::can_remove() const {
    return can_remove_;
}

bool WeaponRemovalVisitor::is_removed() const {
    return removed_;
}
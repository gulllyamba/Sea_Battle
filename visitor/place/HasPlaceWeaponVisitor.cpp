#include "HasPlaceWeaponVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"
#include <vector>

HasPlaceWeaponVisitor::HasPlaceWeaponVisitor(PlaceForWeapon place) : place_(place) {}

HasPlaceWeaponVisitor::~HasPlaceWeaponVisitor() = default;

void HasPlaceWeaponVisitor::visit(TransportShip* ship) {
    has_weapon_ = false;
}

void HasPlaceWeaponVisitor::visit(GuardShip* ship) {
    if (ship && ship->is_alive()) {
        if (ship->has_weapon_in_place(place_)) has_weapon_ = true;
        else has_weapon_ = false;
    }
    else has_weapon_ = false;
    return;
}

void HasPlaceWeaponVisitor::visit(WarShip* ship) {
    if (ship && ship->is_alive()) {
        if (ship->has_weapon_in_place(place_)) has_weapon_ = true;
        else has_weapon_ = false;
    }
    else has_weapon_ = false;
    return;
}

PlaceForWeapon HasPlaceWeaponVisitor::get_place() const {
    return place_;
}

bool HasPlaceWeaponVisitor::has_weapon() const {
    return has_weapon_;
}
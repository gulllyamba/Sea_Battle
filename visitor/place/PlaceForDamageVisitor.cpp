#include "PlaceForDamageVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"
#include <vector>

PlaceForDamageVisitor::PlaceForDamageVisitor(double distance) : place_(PlaceForWeapon::bow), distance_(distance) {}

PlaceForDamageVisitor::~PlaceForDamageVisitor() = default;

void PlaceForDamageVisitor::visit(TransportShip* ship) {
    has_place_ = false;
}

void PlaceForDamageVisitor::visit(GuardShip* ship) {
    if (!ship || !ship->is_alive()) {
        place_ = PlaceForWeapon::bow;
        return;
    }
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::bow, PlaceForWeapon::stern, PlaceForWeapon::port, PlaceForWeapon::starboard};

    double max_damage = 0.0;
    PlaceForWeapon best_place = all_places[0];
    for (auto place : all_places) {
        if (ship->has_weapon_in_place(place)) {
            IWeapon* weapon = ship->get_weapon_in_place(place);
            if (weapon && weapon->get_range() >= distance_) {
                double damage = weapon->get_damage();
                if (damage > max_damage) {
                    max_damage = damage;
                    best_place = place;
                }
            }
        }
    }
    place_ = best_place;
    has_place_ = true;
}

void PlaceForDamageVisitor::visit(WarShip* ship) {
    if (!ship || !ship->is_alive()) {
        place_ = PlaceForWeapon::bow;
        return;
    }
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::bow, PlaceForWeapon::stern, PlaceForWeapon::port, PlaceForWeapon::starboard};

    double max_damage = 0.0;
    PlaceForWeapon best_place = all_places[0];
    for (auto place : all_places) {
        if (ship->has_weapon_in_place(place)) {
            IWeapon* weapon = ship->get_weapon_in_place(place);
            double damage = weapon->get_damage();
            if (weapon && damage > max_damage && weapon->get_range() >= distance_) {
                max_damage = damage;
                best_place = place;
            }
        }
    }
    place_ = best_place;
    has_place_ = true;
}

PlaceForWeapon PlaceForDamageVisitor::get_place() const {
    return place_;
}

double PlaceForDamageVisitor::get_distance() const {
    return distance_;
}

bool PlaceForDamageVisitor::has_place() const {
    return has_place_;
}
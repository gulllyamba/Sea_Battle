#include "PlaceForDPSVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"
#include <vector>

double PlaceForDPSVisitor::calculate_dps(IWeapon* weapon) const {
    if (!weapon) return 0.0;
    return weapon->get_damage() * weapon->get_fire_rate();
}

PlaceForDPSVisitor::PlaceForDPSVisitor(double distance) : place_(PlaceForWeapon::bow), distance_(distance) {}

PlaceForDPSVisitor::~PlaceForDPSVisitor() = default;

void PlaceForDPSVisitor::visit(TransportShip* ship) {
    has_place_ = false;
}

void PlaceForDPSVisitor::visit(GuardShip* ship) {
    if (!ship || !ship->is_alive()) {
        place_ = PlaceForWeapon::bow;
        return;
    }
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::bow, PlaceForWeapon::stern, PlaceForWeapon::port, PlaceForWeapon::starboard};
    
    double max_dps = 0.0;
    PlaceForWeapon best_place = all_places[0];
    for (auto place : all_places) {
        if (ship->has_weapon_in_place(place)) {
            IWeapon* weapon = ship->get_weapon_in_place(place);
            if (weapon && weapon->get_range() >= distance_) {
                double dps = calculate_dps(weapon);
                if (dps > max_dps) {
                    max_dps = dps;
                    best_place = place;
                }
            }
        }
    }
    place_ = best_place;
    has_place_ = true;
}

void PlaceForDPSVisitor::visit(WarShip* ship) {
    if (!ship || !ship->is_alive()) {
        place_ = PlaceForWeapon::bow;
        return;
    }
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::bow, PlaceForWeapon::stern, PlaceForWeapon::port, PlaceForWeapon::starboard};
    
    double max_dps = 0.0;
    PlaceForWeapon best_place = all_places[0];
    for (auto place : all_places) {
        if (ship->has_weapon_in_place(place)) {
            IWeapon* weapon = ship->get_weapon_in_place(place);
            if (weapon && weapon->get_range() >= distance_) {
                double dps = calculate_dps(weapon);
                if (dps > max_dps) {
                    max_dps = dps;
                    best_place = place;
                }
            }
        }
    }
    place_ = best_place;
    has_place_ = true;
}

PlaceForWeapon PlaceForDPSVisitor::get_place() const {
    return place_;
}

double PlaceForDPSVisitor::get_distance() const {
    return distance_;
}

bool PlaceForDPSVisitor::has_place() const {
    return has_place_;
}
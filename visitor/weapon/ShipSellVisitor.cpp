#include "ShipSellVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"
#include <vector>

ShipSellVisitor::~ShipSellVisitor() = default;

void ShipSellVisitor::visit(TransportShip* ship) {
    ship_refund_ = ship->get_cost();
    weapons_refund_ = 0.0;
}

void ShipSellVisitor::visit(GuardShip* ship) {
    ship_refund_ = ship->get_cost();
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::stern, PlaceForWeapon::bow, PlaceForWeapon::port, PlaceForWeapon::starboard};
    
    for (auto place : all_places) {
        if (auto weapon = ship->get_weapon_in_place(place)) {
            weapons_refund_ += weapon->get_cost();
            ship->remove_weapon_from_place(place);
        }
    }
}

void ShipSellVisitor::visit(WarShip* ship) {
    ship_refund_ = ship->get_cost();
    std::vector<PlaceForWeapon> all_places = {PlaceForWeapon::stern, PlaceForWeapon::bow, PlaceForWeapon::port, PlaceForWeapon::starboard};
    
    for (auto place : all_places) {
        if (auto weapon = ship->get_weapon_in_place(place)) {
            weapons_refund_ += weapon->get_cost();
            ship->remove_weapon_from_place(place);
        }
    }
}

double ShipSellVisitor::get_ship_refund() const {
    return ship_refund_;
}

double ShipSellVisitor::get_weapons_refund() const {
    return weapons_refund_;
}

double ShipSellVisitor::get_total_refund() const {
    return ship_refund_ + weapons_refund_;
}
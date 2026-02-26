#include "ShootingVisitor.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"
#include "../../entity/ship/Concrete/GuardShip.hpp"
#include "../../entity/ship/Concrete/WarShip.hpp"

bool ShootingVisitor::can_ship_shoot(const IShip* ship) const {
    if (!ship || !ship->is_alive()) return false;
    if (!target_ship_ || !target_ship_->is_alive()) return false;
    return true;
}

double ShootingVisitor::calculate_distance(const IShip* attacker) const {
    if (!attacker) return 0.0;
    if (target_ship_) return attacker->get_distance_to(target_ship_->get_position());
    else return 0.0;
}

ShootingVisitor::ShootingVisitor(PlaceForWeapon place, IShip* target_ship, DamageService& damage_service)
: place_(place), target_ship_(target_ship), damage_service_(damage_service) {}

ShootingVisitor::~ShootingVisitor() = default;

void ShootingVisitor::visit(TransportShip* ship) {
    shot_fired_ = false;
}

void ShootingVisitor::visit(GuardShip* ship) {
    shot_fired_ = false;

    if (!can_ship_shoot(ship)) return;

    IWeapon* weapon = ship->get_weapon_in_place(place_);
    if (!weapon) return;
    if (weapon->get_current_ammo() == 0) return;

    double distance = calculate_distance(ship);
    if (distance > weapon->get_range()) return;

    double damage_result = damage_service_.calculate_damage(weapon, target_ship_, distance);

    target_ship_->take_damage(damage_result);
    shot_fired_ = true;

    size_t current_ammo = weapon->get_current_ammo();
    if (current_ammo > 0) weapon->set_current_ammo(current_ammo - 1);
}

void ShootingVisitor::visit(WarShip* ship) {
    shot_fired_ = false;

    if (!can_ship_shoot(ship)) return;

    IWeapon* weapon = ship->get_weapon_in_place(place_);
    if (!weapon) return;
    if (weapon->get_current_ammo() == 0) return;

    double distance = calculate_distance(ship);
    if (distance > weapon->get_range()) return;

    double damage_result = damage_service_.calculate_damage(weapon, target_ship_, distance);

    target_ship_->take_damage(damage_result);
    shot_fired_ = true;

    size_t current_ammo = weapon->get_current_ammo();
    if (current_ammo > 0) weapon->set_current_ammo(current_ammo - 1);
}

bool ShootingVisitor::shot_fired() const {
    return shot_fired_;
}
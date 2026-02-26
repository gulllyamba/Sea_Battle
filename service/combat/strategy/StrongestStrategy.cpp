#include "StrongestStrategy.hpp"
#include "../../../visitor/place/PlaceForDamageVisitor.hpp"
#include <cmath>

StrongestStrategy::~StrongestStrategy() = default;

std::string StrongestStrategy::get_name() const {
    return "strongest";
}

std::string StrongestStrategy::get_description() const { 
    return "Атаковать самый сильный корабль (с наибольшим здоровьем)"; 
}

IShip* StrongestStrategy::select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) {
    if (possible_targets.empty()) return nullptr;
    IShip* strongest = nullptr;
    double max_health = 0.0;
    for (auto target : possible_targets) {
        if (target && target->is_alive()) {
            double health = target->get_health();
            if (health > max_health) {
                max_health = health;
                strongest = target;
            }
        }
    }
    return strongest;
}

std::optional<PlaceForWeapon> StrongestStrategy::select_weapon_place(IShip* attacker, IShip* target) {    
    if (!attacker || !attacker->is_alive()) return PlaceForWeapon::bow;
    double distance = 0.0;
    if (target) distance = attacker->get_distance_to(target->get_position());

    PlaceForDamageVisitor visitor(distance);
    attacker->accept(&visitor);

    if (visitor.has_place()) return visitor.get_place();
    else return std::nullopt;
}
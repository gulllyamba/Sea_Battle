#include "WeakestStrategy.hpp"
#include "../../../visitor/place/PlaceForDamageVisitor.hpp"
#include <cmath>

WeakestStrategy::~WeakestStrategy() = default;

std::string WeakestStrategy::get_name() const {
    return "weakest";
}

std::string WeakestStrategy::get_description() const { 
    return "Атаковать самый слабый корабль (с наименьшим здоровьем)"; 
}

IShip* WeakestStrategy::select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) {
    if (possible_targets.empty()) return nullptr;
    IShip* weakest = nullptr;
    double min_health = std::numeric_limits<double>::max();
    for (auto target : possible_targets) {
        if (target && target->is_alive()) {
            double health = target->get_health();
            if (health < min_health) {
                min_health = health;
                weakest = target;
            }
        }
    }
    return weakest;
}

std::optional<PlaceForWeapon> WeakestStrategy::select_weapon_place(IShip* attacker, IShip* target) {    
    if (!attacker || !attacker->is_alive()) return PlaceForWeapon::bow;
    double distance = 0.0;
    if (target) distance = attacker->get_distance_to(target->get_position());

    PlaceForDamageVisitor visitor(distance);
    attacker->accept(&visitor);

    if (visitor.has_place()) return visitor.get_place();
    else return std::nullopt;
}
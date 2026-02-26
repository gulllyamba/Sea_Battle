#include "ClosestStrategy.hpp"
#include "../../../visitor/place/PlaceForDPSVisitor.hpp"
#include <limits>

ClosestStrategy::~ClosestStrategy() = default;

std::string ClosestStrategy::get_name() const {
    return "closest";
}

std::string ClosestStrategy::get_description() const { 
    return "Атаковать ближайший корабль";
}

IShip* ClosestStrategy::select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) {
    if (possible_targets.empty() || !attacker) return nullptr;
    IShip* closest = nullptr;
    double min_distance = std::numeric_limits<double>::max();
    for (auto target : possible_targets) {
        if (target && target->is_alive()) {
            double distance = attacker->get_distance_to(target->get_position());
            if (distance < min_distance) {
                min_distance = distance;
                closest = target;
            }
        }
    }
    return closest;
}

std::optional<PlaceForWeapon> ClosestStrategy::select_weapon_place(IShip* attacker, IShip* target) {
    if (!attacker || !attacker->is_alive()) return PlaceForWeapon::bow;
    double distance = 0.0;
    if (target) distance = attacker->get_distance_to(target->get_position());
    
    PlaceForDPSVisitor visitor(distance);
    attacker->accept(&visitor);

    if (visitor.has_place()) return visitor.get_place();
    else return std::nullopt;
}
#include "RandomStrategy.hpp"
#include "../../../visitor/place/PlaceForDPSVisitor.hpp"
#include <cmath>
#include <chrono>

RandomStrategy::RandomStrategy() : rng_(std::chrono::steady_clock::now().time_since_epoch().count()) {}

RandomStrategy::~RandomStrategy() = default;

std::string RandomStrategy::get_name() const {
    return "random";
}

std::string RandomStrategy::get_description() const {
    return "Атаковать случайный корабль";
}

IShip* RandomStrategy::select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) {
    if (possible_targets.empty()) return nullptr;
    std::vector<IShip*> alive_targets;
    for (auto target : possible_targets) {
        if (target && target->is_alive()) {
            alive_targets.push_back(target);
        }
    }
    if (alive_targets.empty()) return nullptr;
    std::uniform_int_distribution<size_t> dist(0, alive_targets.size() - 1);
    size_t index = dist(rng_);
    return alive_targets[index];
}

std::optional<PlaceForWeapon> RandomStrategy::select_weapon_place(IShip* attacker, IShip* target) {
    if (!attacker || !attacker->is_alive()) return PlaceForWeapon::bow;
    double distance = 0.0;
    if (target) distance = attacker->get_distance_to(target->get_position());

    PlaceForDPSVisitor visitor(distance);
    attacker->accept(&visitor);

    if (visitor.has_place()) return visitor.get_place();
    else return std::nullopt;
}
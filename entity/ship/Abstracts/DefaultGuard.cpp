#include "DefaultGuard.hpp"

IWeapon* DefaultGuard::get_weapon_in_place(PlaceForWeapon place) const {
    auto it = weapons_.find(place);
    if (it != weapons_.end()) return it->second.get();
    return nullptr;
}

void DefaultGuard::set_weapon_in_place(PlaceForWeapon place, std::unique_ptr<IWeapon> weapon) {
    if (!weapon) return;
    remove_weapon_from_place(place);
    weapons_[place] = std::move(weapon);
}

void DefaultGuard::remove_weapon_from_place(PlaceForWeapon place) {
    weapons_.erase(place);
}

size_t DefaultGuard::get_weapon_count() const {
    return weapons_.size();
}

bool DefaultGuard::has_weapon_in_place(PlaceForWeapon place) const {
    return weapons_.find(place) != weapons_.end();
}

double DefaultGuard::get_max_range() const {
    double max_range = 0.0;
    for (const auto& [place, weapon] : weapons_) {
        if (weapon) max_range = std::max(max_range, weapon->get_range());
    }
    return max_range;
}
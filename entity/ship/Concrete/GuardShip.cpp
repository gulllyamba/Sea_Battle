#include "GuardShip.hpp"
#include <sstream>

GuardShip::GuardShip(
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    const std::string& id,
    bool is_convoy,
    const Vector& position)
: DefaultShip(name, captain, max_speed, max_health, cost, id, is_convoy, position) {}
    
std::string GuardShip::get_type() const {
    return "guard";
}

std::string GuardShip::get_description() const {
    std::ostringstream oss;
    oss << "Сторожевой корабль: " << get_name() << "\n"
        << "Капитан: " << get_captain().FIO << "\n"
        << "Скорость: " << get_speed() << "/" << get_max_speed() << "\n"
        << "Здоровье: " << get_health() << "/" << get_max_health() << "\n"
        << "Оружие: " << get_weapon_count() << "\n"
        << "Стоимость: " << get_cost();
    return oss.str();
}

std::unique_ptr<IShip> GuardShip::clone() const {
    auto clone = std::make_unique<GuardShip>(name_, captain_, max_speed_, max_health_, cost_, id_, is_convoy_, position_);
    for (const auto& [place, weapon] : weapons_) {
        if (weapon) clone->set_weapon_in_place(place, weapon->clone());
    }
    return clone;
}

void GuardShip::accept(IShipVisitor* visitor) {
    visitor->visit(this);
}
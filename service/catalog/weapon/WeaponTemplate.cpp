#include "WeaponTemplate.hpp"
#include <stdexcept>
#include <sstream>

std::unique_ptr<IWeapon> WeaponTemplate::create_weapon(WeaponFactoryManager* factory_manager) const {
    if (!factory_manager) throw std::invalid_argument("Factory manager is null");
    return factory_manager->create_weapon(type, display_name, damage, range, fire_rate, max_ammo, cost, accuracy, explosion_radius);
}

std::string WeaponTemplate::get_description() const {
    std::ostringstream oss;
    oss << display_name << ": " 
        << "[Цена: " << cost 
        << ", Урон: " << damage 
        << ", Дальность: " << range
        << ", Скорострельность: " << fire_rate
        << ", Боезапас: " << max_ammo
        << ", Точность: " << accuracy << "]"; 
    return oss.str();
}
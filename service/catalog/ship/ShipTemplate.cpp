#include "ShipTemplate.hpp"
#include <stdexcept>
#include <sstream>

std::unique_ptr<IShip> ShipTemplate::create_ship(ShipFactoryManager* factory_manager, bool is_convoy) const {
    if (!factory_manager) throw std::invalid_argument("Factory manager is null");
    return factory_manager->create_ship(type, display_name, default_captain, max_speed, max_health, cost, is_convoy, max_cargo, Vector(0, 0));
}

std::string ShipTemplate::get_description() const {
    std::ostringstream oss;
    oss << display_name << ": " 
        << "[Цена: " << cost 
        << ", Здоровье: " << max_health 
        << ", Скорость: " << max_speed 
        << ", Грузоподъемность: ";
        if (max_cargo.has_value()) oss <<  max_cargo.value();
        else oss << 0.0;
        oss << ", Коэффициент уменьшения скорости: " << speed_reduction_factor << "]"; 
    return oss.str();
}
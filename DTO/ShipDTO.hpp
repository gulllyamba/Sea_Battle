/**
 * @file ShipDTO.hpp
 * @brief Заголовочный файл, содержащий определение структуры ShipDTO
 */
#pragma once

#include "WeaponDTO.hpp"
#include "../auxiliary/PlaceForWeapon.hpp"
#include "../template/LookupTable.hpp"
#include "../auxiliary/Military.hpp"
#include "../auxiliary/Vector.hpp"

/**
 * @struct ShipDTO
 * @brief Структура DTO (Data Transfer Object) для передачи данных о корабле
 */
struct ShipDTO {
    std::string type; ///< Тип корабля
    std::string id; ///< Идентификатор корабля
    std::string name; ///< Название корабля
    Military captain; ///< Капитан корабля
    double max_speed; ///< Максимальная скорость корабля
    double current_speed; ///< Текущая скорость корабля
    double cost; ///< Стоимость корабля
    
    Vector position; ///< Координаты корабля
    double max_health; ///< Максимальное здоровье корабля
    double current_health; ///< Текущее здоровье корабля
    bool is_alive = true; ///< Флаг жизни корабля
    bool is_convoy; ///< Флаг принадлежности к конвою

    double max_cargo; ///< Максимальная грузоподъемность
    double current_cargo; ///< Текущий груз
    double speed_reduction_factor; ///< Коэффициент снижения скорости от груза

    LookupTable<PlaceForWeapon, WeaponDTO> weapons; ///< Таблица оружия по местам установки
};
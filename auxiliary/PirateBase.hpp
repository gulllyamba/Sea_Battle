/**
 * @file PirateBase.hpp
 * @brief Заголовочный файл, содержащий определение структуры PirateBase
 */

#pragma once

#include "Vector.hpp"
#include <vector>
#include <string>

/**
 * @struct PirateBase
 * @brief Структура, представляющая пиратскую базу
 */
struct PirateBase {
    Vector position; ///< Позиция базы на плоскости
    double trigger_distance; ///< Расстояние активации базы

    size_t ship_count; ///< Количество кораблей на базе
    std::vector<std::string> spawned_pirate_ids; ///< id созданных пиратов

    bool is_activated; ///< Флаг активации базы
    bool is_defeated; ///< Флаг уничтожения базы

    bool operator==(const PirateBase& other) const {
        if (position != other.position) return false;
        if (trigger_distance != other.trigger_distance) return false;
        if (ship_count != other.ship_count) return false;
        if (spawned_pirate_ids != other.spawned_pirate_ids) return false;
        if (is_activated != other.is_activated) return false;
        if (is_defeated != other.is_defeated) return false;
        return true;
    }
};
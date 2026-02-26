/**
 * @file PirateBaseDTO.hpp
 * @brief Заголовочный файл, содержащий определение структуры PirateBaseDTO
 */

#pragma once

#include <string>
#include <vector>
#include "../auxiliary/Vector.hpp"

/**
 * @struct PirateBaseDTO
 * @brief Структура DTO (Data Transfer Object) для передачи данных о пиратской базе
 */
struct PirateBaseDTO {
    Vector position; ///< Позиция базы на плоскости
    double trigger_distance; ///< Расстояние активации базы

    size_t ship_count; ///< Количество кораблей на базе
    std::vector<std::string> spawned_pirate_ids; ///< Идентификаторы созданных пиратов

    bool is_activated; ///< Флаг активации базы
    bool is_defeated; ///< Флаг уничтожения базы

    /**
     * @brief Оператор сравнения на равенство
     * @param other Другая пиратская база DTO для сравнения
     * @return bool true если базы DTO равны, false в противном случае
     */
    bool operator==(const PirateBaseDTO& other) const {
        if (position != other.position) return false;
        if (std::abs(trigger_distance - other.trigger_distance) > 1e-9) return false;
        if (ship_count != other.ship_count) return false;
        if (spawned_pirate_ids != other.spawned_pirate_ids) return false;
        if (is_activated != other.is_activated) return false;
        if (is_defeated != other.is_defeated) return false;
        return true;
    }
};
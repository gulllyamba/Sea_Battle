/**
 * @file WeaponDTO.hpp
 * @brief Заголовочный файл, содержащий определение структуры WeaponDTO
 */
#pragma once

#include <string>

/**
 * @struct WeaponDTO
 * @brief Структура DTO (Data Transfer Object) для передачи данных об оружии
 */
struct WeaponDTO {
    std::string type; ///< Тип оружия
    std::string name; ///< Название оружия
    double damage; ///< Урон оружия
    double range; ///< Дальность стрельбы
    size_t fire_rate; ///< Скорострельность
    size_t max_ammo; ///< Максимальный боезапас
    size_t current_ammo; ///< Текущий боезапас
    double cost; ///< Стоимость оружия
    double accuracy; ///< Точность оружия
    double explosion_radius; ///< Радиус взрыва
};
/**
 * @file PlaceForWeapon.hpp
 * @brief Заголовочный файл, содержащий определение перечисления PlaceForWeapon
 */

#pragma once

/**
 * @enum PlaceForWeapon
 * @brief Перечисление, представляющее возможные места для установки оружия на корабле
 */
enum PlaceForWeapon {
    stern, ///< Корма
    bow, ///< Нос
    starboard, ///< Правый борт
    port ///< Левый борт
};
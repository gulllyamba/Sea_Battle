/**
 * @file Gun.hpp
 * @brief Заголовочный файл, содержащий определение класса Gun
 */

#pragma once

#include "../Abstracts/DefaultWeapon.hpp"

/**
 * @class Gun
 * @brief Класс, представляющий пушечное оружие
 */
class Gun : public DefaultWeapon {
    public:
        /**
         * @brief Конструктор с параметрами по умолчанию
         * @param name Название пушки (по умолчанию "Пушка")
         * @param damage Урон (по умолчанию 25.0)
         * @param range Дальность (по умолчанию 3.0)
         * @param fire_rate Скорострельность (по умолчанию 2)
         * @param max_ammo Максимальный боезапас (по умолчанию 50)
         * @param cost Стоимость (по умолчанию 5000.0)
         * @param accuracy Точность (по умолчанию 0.7)
         * @param explosion_radius Радиус взрыва (по умолчанию 0.0)
         */
        Gun(
            const std::string& name = "Пушка",
            double damage = 25.0,
            double range = 3.0,
            size_t fire_rate = 2,
            size_t max_ammo = 50,
            double cost = 5000.0,
            double accuracy = 0.7,
            double explosion_radius = 0.0
        );

        std::unique_ptr<IWeapon> clone() const override;
};
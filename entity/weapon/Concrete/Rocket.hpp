/**
 * @file Rocket.hpp
 * @brief Заголовочный файл, содержащий определение класса Rocket
 */

#pragma once

#include "../Abstracts/DefaultWeapon.hpp"

/**
 * @class Rocket
 * @brief Класс, представляющий ракетное оружие
 */
class Rocket : public DefaultWeapon {
    public:
        /**
         * @brief Конструктор с параметрами по умолчанию
         * @param name Название ракеты (по умолчанию "Ракета")
         * @param damage Урон (по умолчанию 40.0)
         * @param range Дальность (по умолчанию 5.0)
         * @param fire_rate Скорострельность (по умолчанию 1)
         * @param max_ammo Максимальный боезапас (по умолчанию 20)
         * @param cost Стоимость (по умолчанию 8000.0)
         * @param accuracy Точность (по умолчанию 0.9)
         * @param explosion_radius Радиус взрыва (по умолчанию 1.0)
         */
        Rocket(
            const std::string& name = "Ракета",
            double damage = 40.0,
            double range = 5.0,
            size_t fire_rate = 1,
            size_t max_ammo = 20,
            double cost = 8000.0,
            double accuracy = 0.9,
            double explosion_radius = 1.0
        );

        std::unique_ptr<IWeapon> clone() const override;
};
/**
 * @file IWeaponFactory.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IWeaponFactory
 */

#pragma once

#include "../Interfaces/IWeapon.hpp"
#include <memory>

/**
 * @class IWeaponFactory
 * @brief Интерфейс фабрики оружия
 */
class IWeaponFactory {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IWeaponFactory() = default;

        /**
         * @brief Создает оружие с параметрами по умолчанию
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        virtual std::unique_ptr<IWeapon> create_weapon() const = 0;

        /**
         * @brief Создает оружие с заданными параметрами
         * @param name Название оружия
         * @param damage Урон оружия
         * @param range Дальность стрельбы
         * @param fire_rate Скорострельность
         * @param max_ammo Максимальный боезапас
         * @param cost Стоимость оружия
         * @param accuracy Точность оружия
         * @param explosion_radius Радиус взрыва
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        virtual std::unique_ptr<IWeapon> create_weapon(
            const std::string& name,
            double damage,
            double range,
            size_t fire_rate,
            size_t max_ammo,
            double cost,
            double accuracy,
            double explosion_radius
        ) const = 0;
};
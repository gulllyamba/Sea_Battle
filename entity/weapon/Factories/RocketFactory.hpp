/**
 * @file RocketFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса RocketFactory
 */

#pragma once

#include "IWeaponFactory.hpp"
#include "../Concrete/Rocket.hpp"

/**
 * @class RocketFactory
 * @brief Фабрика для создания ракетного оружия
 */
class RocketFactory : public IWeaponFactory {
    private:
        std::unique_ptr<Rocket> prototype_; ///< Прототип ракеты для клонирования
    public:
        /**
         * @brief Конструктор
         */
        RocketFactory();
        
        /**
         * @brief Деструктор
         */
        ~RocketFactory() override = default;

        std::unique_ptr<IWeapon> create_weapon() const override;
        std::unique_ptr<IWeapon> create_weapon(
            const std::string& name,
            double damage,
            double range,
            size_t fire_rate,
            size_t max_ammo,
            double cost,
            double accuracy,
            double explosion_radius
        ) const override;

        /**
         * @brief Устанавливает прототип для фабрики
         * @param prototype Указатель на прототип ракеты
         */
        void set_prototype(std::unique_ptr<Rocket> prototype);
};
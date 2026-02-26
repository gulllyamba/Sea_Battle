/**
 * @file GunFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса GunFactory
 */

#pragma once

#include "IWeaponFactory.hpp"
#include "../Concrete/Gun.hpp"

/**
 * @class GunFactory
 * @brief Фабрика для создания пушечного оружия
 */
class GunFactory : public IWeaponFactory {
    private:
        std::unique_ptr<Gun> prototype_; ///< Прототип пушки для клонирования
    public:
        /**
         * @brief Конструктор
         */
        GunFactory();
        
        /**
         * @brief Деструктор
         */
        ~GunFactory() override = default;

        std::unique_ptr<IWeapon> create_weapon() const override;
        std::unique_ptr<IWeapon> create_weapon(
            const std::string& name,
            double damage,
            double range,
            size_t fire_rate,
            size_t max_ammo,
            double cost,
            double accuracy,
            double explosion_radius = 0.0
        ) const override;

        /**
         * @brief Устанавливает прототип для фабрики
         * @param prototype Указатель на прототип пушки
         */
        void set_prototype(std::unique_ptr<Gun> prototype);
};
/**
 * @file WeakestStrategy.hpp
 * @brief Заголовочный файл, содержащий определение класса WeakestStrategy
 */

#pragma once

#include "IAttackStrategy.hpp"

/**
 * @class WeakestStrategy
 * @brief Стратегия атаки по самой слабой цели
 */
class WeakestStrategy : public IAttackStrategy {
    public:
        /**
         * @brief Деструктор
         */
        ~WeakestStrategy() override;

        std::string get_name() const override;
        std::string get_description() const override;
        
        IShip* select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) override;
        std::optional<PlaceForWeapon> select_weapon_place(IShip* attacker, IShip* target) override;
};
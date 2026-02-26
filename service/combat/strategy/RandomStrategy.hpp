/**
 * @file RandomStrategy.hpp
 * @brief Заголовочный файл, содержащий определение класса RandomStrategy
 */

#pragma once

#include "IAttackStrategy.hpp"
#include <random>

/**
 * @class RandomStrategy
 * @brief Стратегия случайного выбора цели
 */
class RandomStrategy : public IAttackStrategy {
    private:
        std::mt19937 rng_; ///< Генератор случайных чисел
    public:
        /**
         * @brief Конструктор
         */
        RandomStrategy();
        
        /**
         * @brief Деструктор
         */
        ~RandomStrategy() override;
        
        std::string get_name() const override;
        std::string get_description() const override;
        
        IShip* select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) override;
        std::optional<PlaceForWeapon> select_weapon_place(IShip* attacker, IShip* target) override;
};
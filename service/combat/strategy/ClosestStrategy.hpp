/**
 * @file ClosestStrategy.hpp
 * @brief Заголовочный файл, содержащий определение класса ClosestStrategy
 */

#pragma once

#include "IAttackStrategy.hpp"

/**
 * @class ClosestStrategy
 * @brief Стратегия атаки по ближайшей цели
 */
class ClosestStrategy : public IAttackStrategy {
    public:
        /**
         * @brief Деструктор
         */
        ~ClosestStrategy() override;

        std::string get_name() const override;
        std::string get_description() const override;
        
        IShip* select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) override;
        std::optional<PlaceForWeapon> select_weapon_place(IShip* attacker, IShip* target) override;
};
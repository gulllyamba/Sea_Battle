/**
 * @file StrongestStrategy.hpp
 * @brief Заголовочный файл, содержащий определение класса StrongestStrategy
 */

#pragma once

#include "IAttackStrategy.hpp"

/**
 * @class StrongestStrategy
 * @brief Стратегия атаки по самой сильной цели
 */
class StrongestStrategy : public IAttackStrategy {
    public:
        /**
         * @brief Деструктор
         */
        ~StrongestStrategy() override;

        std::string get_name() const override;
        std::string get_description() const override;
        
        IShip* select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) override;
        std::optional<PlaceForWeapon> select_weapon_place(IShip* attacker, IShip* target) override;
};
/**
 * @file IAttackStrategy.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IAttackStrategy
 */

#pragma once

#include "../../../entity/ship/Interfaces/IShip.hpp"
#include "../../../auxiliary/PlaceForWeapon.hpp"
#include <optional>
#include <vector>

/**
 * @class IAttackStrategy
 * @brief Интерфейс стратегии атаки для кораблей
 */
class IAttackStrategy {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IAttackStrategy() = default;
        
        /**
         * @brief Получает название стратегии
         * @return std::string Название стратегии
         */
        virtual std::string get_name() const = 0;
        
        /**
         * @brief Получает описание стратегии
         * @return std::string Описание стратегии
         */
        virtual std::string get_description() const = 0;
        
        /**
         * @brief Выбирает цель для атаки
         * @param attacker Атакующий корабль
         * @param possible_targets Возможные цели
         * @return IShip* Выбранная цель или nullptr если целей нет
         */
        virtual IShip* select_target(IShip* attacker, const std::vector<IShip*>& possible_targets) = 0;
        
        /**
         * @brief Выбирает место для оружия для атаки
         * @param attacker Атакующий корабль
         * @param target Целевой корабль
         * @return std::optional<PlaceForWeapon> Выбранное место для оружия или std::nullopt
         */
        virtual std::optional<PlaceForWeapon> select_weapon_place(IShip* attacker, IShip* target) = 0;
};
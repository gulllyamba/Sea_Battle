/**
 * @file ShootingVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса ShootingVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../service/combat/DamageService.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class ShootingVisitor
 * @brief Посетитель для выполнения выстрела с корабля
 */
class ShootingVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Место для стрельбы
        IShip* target_ship_; ///< Целевой корабль
        DamageService& damage_service_; ///< Сервис урона
        bool shot_fired_ = false; ///< Флаг выполненного выстрела

        /**
         * @brief Проверяет, может ли корабль стрелять
         * @param ship Указатель на корабль
         * @return bool true если корабль может стрелять, false в противном случае
         */
        bool can_ship_shoot(const IShip* ship) const;
        
        /**
         * @brief Вычисляет расстояние до цели
         * @param attacker Атакующий корабль
         * @return double Расстояние до цели
         */
        double calculate_distance(const IShip* attacker) const;
    public:
        /**
         * @brief Конструктор
         * @param place Место для стрельбы
         * @param target_ship Целевой корабль
         * @param damage_service Сервис урона
         */
        ShootingVisitor(PlaceForWeapon place, IShip* target_ship, DamageService& damage_service);
        
        /**
         * @brief Деструктор
         */
        ~ShootingVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Проверяет, был ли выполнен выстрел
         * @return bool true если выстрел выполнен, false в противном случае
         */
        bool shot_fired() const;
};
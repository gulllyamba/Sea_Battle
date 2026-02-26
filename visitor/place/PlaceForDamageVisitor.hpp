/**
 * @file PlaceForDamageVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса PlaceForDamageVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class PlaceForDamageVisitor
 * @brief Посетитель для выбора места для оружия на основе максимального урона на расстоянии
 */
class PlaceForDamageVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Выбранное место для оружия
        double distance_; ///< Расстояние до цели
        bool has_place_ = false; ///< Флаг наличия подходящего места
    public:
        /**
         * @brief Конструктор
         * @param distance Расстояние до цели
         */
        PlaceForDamageVisitor(double distance);
        
        /**
         * @brief Деструктор
         */
        ~PlaceForDamageVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Получает выбранное место для оружия
         * @return PlaceForWeapon Выбранное место для оружия
         */
        PlaceForWeapon get_place() const;
        
        /**
         * @brief Получает расстояние до цели
         * @return double Расстояние до цели
         */
        double get_distance() const;
        
        /**
         * @brief Проверяет наличие подходящего места для оружия
         * @return bool true если есть подходящее место, false в противном случае
         */
        bool has_place() const;
};
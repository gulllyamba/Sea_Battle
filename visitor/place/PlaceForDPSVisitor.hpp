/**
 * @file PlaceForDPSVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса PlaceForDPSVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../entity/weapon/Interfaces/IWeapon.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class PlaceForDPSVisitor
 * @brief Посетитель для выбора места для оружия на основе максимального DPS (урона в секунду) на расстоянии
 */
class PlaceForDPSVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Выбранное место для оружия
        double distance_; ///< Расстояние до цели
        bool has_place_ = false; ///< Флаг наличия подходящего места
        
        /**
         * @brief Вычисляет DPS (урон в секунду) оружия
         * @param weapon Указатель на оружие
         * @return double DPS оружия
         */
        double calculate_dps(IWeapon* weapon) const;
    public:
        /**
         * @brief Конструктор
         * @param distance Расстояние до цели
         */
        PlaceForDPSVisitor(double distance);
        
        /**
         * @brief Деструктор
         */
        ~PlaceForDPSVisitor() override;
        
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
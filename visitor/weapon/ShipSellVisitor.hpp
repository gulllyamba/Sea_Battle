/**
 * @file ShipSellVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipSellVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../entity/weapon/Interfaces/IWeapon.hpp"

/**
 * @class ShipSellVisitor
 * @brief Посетитель для расчета стоимости продажи корабля и его оружия
 */
class ShipSellVisitor : public IShipVisitor {
    private:
        double ship_refund_ = 0.0; ///< Стоимость продажи корабля
        double weapons_refund_ = 0.0; ///< Стоимость продажи оружия
    public:
        /**
         * @brief Деструктор
         */
        ~ShipSellVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Получает общую стоимость продажи
         * @return double Общая стоимость продажи
         */
        double get_total_refund() const;
        
        /**
         * @brief Получает стоимость продажи корабля
         * @return double Стоимость продажи корабля
         */
        double get_ship_refund() const;
        
        /**
         * @brief Получает стоимость продажи оружия
         * @return double Стоимость продажи оружия
         */
        double get_weapons_refund() const;
};
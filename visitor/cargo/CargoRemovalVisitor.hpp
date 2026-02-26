/**
 * @file CargoRemovalVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса CargoRemovalVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"

/**
 * @class CargoRemovalVisitor
 * @brief Посетитель для выгрузки груза с корабля
 */
class CargoRemovalVisitor : public IShipVisitor {
    private:
        double amount_; ///< Количество груза для выгрузки
        bool can_remove_ = false; ///< Флаг возможности выгрузки
        bool removed_ = false; ///< Флаг успешной выгрузки
    public:
        /**
         * @brief Конструктор
         * @param amount Количество груза для выгрузки
         */
        CargoRemovalVisitor(double amount);
        
        /**
         * @brief Деструктор
         */
        ~CargoRemovalVisitor() override;
        
        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;
        
        /**
         * @brief Проверяет возможность выгрузки груза
         * @return bool true если груз можно выгрузить, false в противном случае
         */
        bool can_remove() const;
        
        /**
         * @brief Проверяет, был ли груз успешно выгружен
         * @return bool true если груз выгружен, false в противном случае
         */
        bool is_removed() const;
};
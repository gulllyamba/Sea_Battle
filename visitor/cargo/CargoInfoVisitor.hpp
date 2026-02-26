/**
 * @file CargoInfoVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса CargoInfoVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"

/**
 * @class CargoInfoVisitor
 * @brief Посетитель для сбора информации о грузе корабля
 */
class CargoInfoVisitor : public IShipVisitor {
    private:
        double max_cargo_ = 0.0; ///< Максимальная грузоподъемность
        double current_cargo_ = 0.0; ///< Текущий груз
        double speed_reduction_factor_ = 0.0; ///< Коэффициент снижения скорости
    public:
        /**
         * @brief Деструктор
         */
        ~CargoInfoVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Получает максимальную грузоподъемность
         * @return double Максимальная грузоподъемность
         */
        double get_max_cargo() const;
        
        /**
         * @brief Получает текущий груз
         * @return double Текущий груз
         */
        double get_current_cargo() const;
        
        /**
         * @brief Получает коэффициент снижения скорости
         * @return double Коэффициент снижения скорости
         */
        double get_speed_reduction_factor() const;
};
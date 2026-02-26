/**
 * @file CargoLoadVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса CargoLoadVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"

/**
 * @class CargoLoadVisitor
 * @brief Посетитель для загрузки груза на корабль
 */
class CargoLoadVisitor : public IShipVisitor {
    private:
        double amount_; ///< Количество груза для загрузки
        bool can_load_ = false; ///< Флаг возможности загрузки
        bool loaded_ = false; ///< Флаг успешной загрузки
    public:
        /**
         * @brief Конструктор
         * @param amount Количество груза для загрузки
         */
        CargoLoadVisitor(double amount);
        
        /**
         * @brief Деструктор
         */
        ~CargoLoadVisitor() override;
        
        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;
        
        /**
         * @brief Проверяет возможность загрузки груза
         * @return bool true если груз можно загрузить, false в противном случае
         */
        bool can_load() const;
        
        /**
         * @brief Проверяет, был ли груз успешно загружен
         * @return bool true если груз загружен, false в противном случае
         */
        bool is_loaded() const;
};
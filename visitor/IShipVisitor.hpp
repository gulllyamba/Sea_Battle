/**
 * @file IShipVisitor.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipVisitor
 */

#pragma once

class GuardShip;
class TransportShip;
class WarShip;

/**
 * @class IShipVisitor
 * @brief Интерфейс посетителя для кораблей (паттерн Visitor)
 */
class IShipVisitor {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipVisitor() = default;

        /**
         * @brief Посещает транспортный корабль
         * @param ship Указатель на транспортный корабль
         */
        virtual void visit(TransportShip* ship) = 0;
        
        /**
         * @brief Посещает сторожевой корабль
         * @param ship Указатель на сторожевой корабль
         */
        virtual void visit(GuardShip* ship) = 0;
        
        /**
         * @brief Посещает военный корабль
         * @param ship Указатель на военный корабль
         */
        virtual void visit(WarShip* ship) = 0;
};
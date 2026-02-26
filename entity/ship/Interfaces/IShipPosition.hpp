/**
 * @file IShipPosition.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipPosition
 */

#pragma once

#include "../../../auxiliary/Vector.hpp"

/**
 * @class IShipPosition
 * @brief Интерфейс, представляющий позицию и движение корабля
 */
class IShipPosition {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipPosition() = default;
        
        /**
         * @brief Получает текущую позицию корабля
         * @return Vector Текущая позиция корабля
         */
        virtual Vector get_position() const = 0;
        
        /**
         * @brief Устанавливает позицию корабля
         * @param position Новая позиция корабля
         */
        virtual void set_position(const Vector& position) = 0;
        
        /**
         * @brief Получает текущую скорость корабля
         * @return double Текущая скорость корабля
         */
        virtual double get_speed() const = 0;
        
        /**
         * @brief Устанавливает скорость корабля
         * @param speed Новая скорость корабля
         */
        virtual void set_speed(double speed) = 0;

        /**
         * @brief Вычисляет расстояние до заданной точки
         * @param point Точка, до которой вычисляется расстояние
         * @return double Расстояние до точки
         */
        virtual double get_distance_to(const Vector& point) const = 0;
        
        /**
         * @brief Проверяет, находится ли корабль в заданной позиции
         * @param position Позиция для проверки
         * @param tolerance Допустимая погрешность (по умолчанию 0.1)
         * @return bool true если корабль находится в позиции с учетом погрешности, false в противном случае
         */
        virtual bool is_at_position(const Vector& position, double tolerance = 0.1) const = 0;
};
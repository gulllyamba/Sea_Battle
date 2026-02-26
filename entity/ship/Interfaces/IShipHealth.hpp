/**
 * @file IShipHealth.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipHealth
 */

#pragma once

/**
 * @class IShipHealth
 * @brief Интерфейс, представляющий здоровье корабля
 */
class IShipHealth {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipHealth() = default;
        
        /**
         * @brief Получает текущее здоровье корабля
         * @return double Текущее здоровье корабля
         */
        virtual double get_health() const = 0;
        
        /**
         * @brief Получает максимальное здоровье корабля
         * @return double Максимальное здоровье корабля
         */
        virtual double get_max_health() const = 0;
        
        /**
         * @brief Проверяет, жив ли корабль
         * @return bool true если корабль жив, false в противном случае
         */
        virtual bool is_alive() const = 0;
        
        /**
         * @brief Устанавливает текущее здоровье корабля
         * @param health Новое значение здоровья корабля
         */
        virtual void set_health(double health) = 0;
        
        /**
         * @brief Устанавливает максимальное здоровье корабля
         * @param max_health Новое значение максимального здоровья корабля
         */
        virtual void set_max_health(double max_health) = 0;
        
        /**
         * @brief Наносит урон кораблю
         * @param damage Величина урона
         */
        virtual void take_damage(double damage) = 0;
};
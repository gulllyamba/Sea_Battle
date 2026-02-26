/**
 * @file IShipFactory.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipFactory
 */

#pragma once

#include "../Interfaces/IShip.hpp"
#include <optional>

/**
 * @class IShipFactory
 * @brief Интерфейс фабрики кораблей
 */
class IShipFactory {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipFactory() = default;

        /**
         * @brief Создает корабль с параметрами по умолчанию
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        virtual std::unique_ptr<IShip> create_ship() const = 0;
        
        /**
         * @brief Создает корабль с заданными параметрами
         * @param name Название корабля
         * @param captain Капитан корабля
         * @param max_speed Максимальная скорость корабля
         * @param max_health Максимальное здоровье корабля
         * @param cost Стоимость корабля
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @param max_cargo Максимальная грузоподъемность (опционально)
         * @param position Позиция корабля (по умолчанию (0, 0))
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        virtual std::unique_ptr<IShip> create_ship(
            const std::string& name,
            const Military& captain,
            double max_speed,
            double max_health,
            double cost,
            bool is_convoy = true,
            std::optional<double> max_cargo = std::nullopt,
            const Vector& position = Vector(0, 0)
        ) const = 0;
};
/**
 * @file TransportShipFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса TransportShipFactory
 */

#pragma once

#include "IShipFactory.hpp"
#include "../Concrete/TransportShip.hpp"

/**
 * @class TransportShipFactory
 * @brief Фабрика для создания транспортных кораблей
 */
class TransportShipFactory : public IShipFactory {
    private:
        std::unique_ptr<TransportShip> prototype_; ///< Прототип транспортного корабля для клонирования
        double default_max_cargo_ = 1000.0; ///< Значение максимальной грузоподъемности по умолчанию
    public:
        /**
         * @brief Конструктор
         */
        TransportShipFactory();
        
        /**
         * @brief Деструктор
         */
        ~TransportShipFactory() override = default;
        
        std::unique_ptr<IShip> create_ship() const override;
        std::unique_ptr<IShip> create_ship(
            const std::string& name,
            const Military& captain,
            double max_speed,
            double max_health,
            double cost,
            bool is_convoy = true,
            std::optional<double> max_cargo = std::nullopt,
            const Vector& position = Vector(0, 0)
        ) const override;
        
        /**
         * @brief Устанавливает прототип для фабрики
         * @param prototype Указатель на прототип транспортного корабля
         */
        void set_prototype(std::unique_ptr<TransportShip> prototype);
        
        /**
         * @brief Устанавливает значение максимальной грузоподъемности по умолчанию
         * @param max_cargo Новое значение максимальной грузоподъемности
         */
        void set_default_max_cargo(double max_cargo);
};
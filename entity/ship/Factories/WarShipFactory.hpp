/**
 * @file WarShipFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса WarShipFactory
 */

#pragma once

#include "IShipFactory.hpp"
#include "../Concrete/WarShip.hpp"

/**
 * @class WarShipFactory
 * @brief Фабрика для создания военных кораблей
 */
class WarShipFactory : public IShipFactory {
    private:
        std::unique_ptr<WarShip> prototype_; ///< Прототип военного корабля для клонирования
        double default_max_cargo_ = 500.0; ///< Значение максимальной грузоподъемности по умолчанию
    public:
        /**
         * @brief Конструктор
         */
        WarShipFactory();
        
        /**
         * @brief Деструктор
         */
        ~WarShipFactory() override = default;

        virtual std::unique_ptr<IShip> create_ship() const override;
        virtual std::unique_ptr<IShip> create_ship(
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
         * @param prototype Указатель на прототип военного корабля
         */
        void set_prototype(std::unique_ptr<WarShip> prototype);
        
        /**
         * @brief Устанавливает значение максимальной грузоподъемности по умолчанию
         * @param max_cargo Новое значение максимальной грузоподъемности
         */
        void set_default_max_cargo(double max_cargo);
};
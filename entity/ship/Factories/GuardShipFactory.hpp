/**
 * @file GuardShipFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса GuardShipFactory
 */

#pragma once

#include "IShipFactory.hpp"
#include "../Concrete/GuardShip.hpp"

/**
 * @class GuardShipFactory
 * @brief Фабрика для создания сторожевых кораблей
 */
class GuardShipFactory : public IShipFactory {
    private:
        std::unique_ptr<GuardShip> prototype_; ///< Прототип сторожевого корабля для клонирования
    public:
        /**
         * @brief Конструктор
         */
        GuardShipFactory();
        
        /**
         * @brief Деструктор
         */
        ~GuardShipFactory() override = default;
        
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
         * @param prototype Указатель на прототип сторожевого корабля
         */
        void set_prototype(std::unique_ptr<GuardShip> prototype);
};
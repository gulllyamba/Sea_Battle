/**
 * @file TransportShip.hpp
 * @brief Заголовочный файл, содержащий определение класса TransportShip
 */

#pragma once

#include "../Abstracts/DefaultShip.hpp"
#include "../Abstracts/DefaultCargo.hpp"

/**
 * @class TransportShip
 * @brief Класс, представляющий транспортный корабль
 */
class TransportShip : public DefaultShip, public DefaultCargo {
    public:
        /**
         * @brief Конструктор с параметрами по умолчанию
         * @param name Название корабля (по умолчанию "Транспортный корабль")
         * @param captain Капитан корабля (по умолчанию Military())
         * @param max_speed Максимальная скорость (по умолчанию 30.0)
         * @param max_health Максимальное здоровье (по умолчанию 150.0)
         * @param cost Стоимость (по умолчанию 15000.0)
         * @param id Идентификатор (по умолчанию "")
         * @param max_cargo Максимальная грузоподъемность (по умолчанию 1000.0)
         * @param position Позиция (по умолчанию (0.0, 0.0))
         */
        TransportShip(
            const std::string& name = "Транспортный корабль",
            const Military& captain = Military(),
            double max_speed = 30.0,
            double max_health = 150.0,
            double cost = 15000.0,
            const std::string& id = "",
            double max_cargo = 1000.0,
            const Vector& position = Vector(0.0, 0.0)
        );

        std::string get_type() const override;
        std::string get_description() const override;
        std::unique_ptr<IShip> clone() const override;
        
        double get_speed() const override;

        void accept(IShipVisitor* visitor) override;
};
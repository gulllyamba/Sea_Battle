/**
 * @file WarShip.hpp
 * @brief Заголовочный файл, содержащий определение класса WarShip
 */

#pragma once
#include "../Abstracts/DefaultShip.hpp"
#include "../Abstracts/DefaultGuard.hpp"
#include "../Abstracts/DefaultCargo.hpp"

/**
 * @class WarShip
 * @brief Класс, представляющий военный корабль
 */
class WarShip : public DefaultShip, public DefaultGuard, public DefaultCargo {
    public:
        /**
         * @brief Конструктор с параметрами по умолчанию
         * @param name Название корабля (по умолчанию "Военный корабль")
         * @param captain Капитан корабля (по умолчанию Military())
         * @param max_speed Максимальная скорость (по умолчанию 40.0)
         * @param max_health Максимальное здоровье (по умолчанию 200.0)
         * @param cost Стоимость (по умолчанию 25000.0)
         * @param id Идентификатор (по умолчанию "")
         * @param max_cargo Максимальная грузоподъемность (по умолчанию 500.0)
         * @param position Позиция (по умолчанию (0.0, 0.0))
         */
        WarShip(
            const std::string& name = "Военный корабль",
            const Military& captain = Military(),
            double max_speed = 40.0,
            double max_health = 200.0,
            double cost = 25000.0,
            const std::string& id = "",
            double max_cargo = 500.0,
            const Vector& position = Vector(0.0, 0.0)
        );
        
        std::string get_type() const override;
        std::string get_description() const override;
        std::unique_ptr<IShip> clone() const override;
        
        double get_speed() const override;

        void accept(IShipVisitor* visitor) override;
};
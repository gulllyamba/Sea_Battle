/**
 * @file GuardShip.hpp
 * @brief Заголовочный файл, содержащий определение класса GuardShip
 */

#pragma once

#include "../Abstracts/DefaultShip.hpp"
#include "../Abstracts/DefaultGuard.hpp"

/**
 * @class GuardShip
 * @brief Класс, представляющий сторожевой корабль
 */
class GuardShip : public DefaultShip, public DefaultGuard {
    public:
        /**
         * @brief Конструктор с параметрами по умолчанию
         * @param name Название корабля (по умолчанию "Сторожевой корабль")
         * @param captain Капитан корабля (по умолчанию Military())
         * @param max_speed Максимальная скорость (по умолчанию 50.0)
         * @param max_health Максимальное здоровье (по умолчанию 100.0)
         * @param cost Стоимость (по умолчани 10000.0)
         * @param id Идентификатор (по умолчанию "")
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @param position Позиция (по умолчанию (0.0, 0.0))
         */
        GuardShip(
            const std::string& name = "Сторожевой корабль",
            const Military& captain = Military(),
            double max_speed = 50.0,
            double max_health = 100.0,
            double cost = 10000.0,
            const std::string& id = "",
            bool is_convoy = true,
            const Vector& position = Vector()
        );
        
        std::string get_type() const override;
        std::string get_description() const override;
        std::unique_ptr<IShip> clone() const override;

        void accept(IShipVisitor* visitor) override;
};
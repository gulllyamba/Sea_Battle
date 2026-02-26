/**
 * @file DefaultShip.hpp
 * @brief Заголовочный файл, содержащий определение класса DefaultShip
 */

#pragma once

#include "../Interfaces/IShip.hpp"
#include <atomic>

/**
 * @class DefaultShip
 * @brief Абстрактный базовый класс, реализующий базовую функциональность корабля
 */
class DefaultShip : public IShip {
    protected:
        std::string name_; ///< Название корабля
        Military captain_; ///< Капитан корабля
        double max_speed_; ///< Максимальная скорость корабля
        double current_speed_; ///< Текущая скорость корабля
        double cost_; ///< Стоимость корабля

        std::string id_; ///< Идентификатор корабля
        bool is_convoy_; ///< Флаг принадлежности к конвою
        
        Vector position_; ///< Позиция корабля

        double max_health_; ///< Максимальное здоровье корабля
        std::atomic<double> current_health_; ///< Атомарное текущее здоровье
        std::atomic<bool> is_alive_; ///< Атомарный флаг жизни
        
        /**
         * @brief Проверяет корректность параметров корабля
         */
        void validate_parameters() const;
    public:
        /**
         * @brief Конструктор с параметрами
         * @param name Название корабля
         * @param captain Капитан корабля
         * @param max_speed Максимальная скорость корабля
         * @param max_health Максимальное здоровье корабля
         * @param cost Стоимость корабля
         * @param id Идентификатор корабля (по умолчанию "")
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @param position Позиция корабля (по умолчанию (0, 0))
         */
        DefaultShip(
            const std::string& name,
            const Military& captain,
            double max_speed,
            double max_health,
            double cost,
            const std::string& id = "",
            bool is_convoy = true,
            const Vector& position = Vector(0, 0)
        );
    
        /**
         * @brief Деструктор
         */
        ~DefaultShip() override = default;

        Vector get_position() const override;
        void set_position(const Vector& position) override;
        double get_speed() const override;
        void set_speed(double speed) override;
        double get_distance_to(const Vector& point) const override;
        bool is_at_position(const Vector& position, double tolerance = 0.1) const override;

        double get_health() const override;
        double get_max_health() const override;
        bool is_alive() const override;
        void set_health(double health) override;
        void set_max_health(double max_health) override;
        void take_damage(double damage) override;

        std::string get_name() const override;
        Military get_captain() const override;
        double get_max_speed() const override;
        double get_cost() const override;
        std::string get_ID() const override;
        
        void set_name(const std::string& name) override;
        void set_captain(const Military& captain) override;
        void set_max_speed(double max_speed) override;
        void set_cost(double cost) override;
        void set_ID(const std::string& id) override;

        bool is_convoy() const override;
        void set_convoy(bool is_convoy) override;

        virtual std::string get_type() const override = 0;
        virtual std::string get_description() const override = 0;
        virtual std::unique_ptr<IShip> clone() const override = 0;
        virtual void accept(IShipVisitor* visitor) override = 0;
};
/**
 * @file DefaultCargo.hpp
 * @brief Заголовочный файл, содержащий определение класса DefaultCargo
 */

#pragma once
#include "../Interfaces/ICargo.hpp"
#include <atomic>

/**
 * @class DefaultCargo
 * @brief Реализация базовой функциональности грузоподъемности корабля
 */
class DefaultCargo : public ICargo {
    protected:
        double max_cargo_; ///< Максимальная грузоподъемность
        std::atomic<double> current_cargo_; ///< Атомарный текущий груз
        double speed_reduction_factor_; ///< Коэффициент снижения скорости от груза
    public:
        /**
         * @brief Конструктор
         * @param max_cargo Максимальная грузоподъемность
         * @param speed_reduction_factor Коэффициент снижения скорости (по умолчанию 0.1)
         */
        DefaultCargo(double max_cargo, double speed_reduction_factor = 0.1);
        
        /**
         * @brief Деструктор
         */
        ~DefaultCargo() override = default;

        double get_max_cargo() const override;
        double get_cargo() const override;
        void set_max_cargo(double max_cargo) override;
        void set_cargo(double cargo) override;
        void add_cargo(double amount) override;
        void remove_cargo(double amount) override;
        double get_speed_reduction_factor() const override;
        void set_speed_reduction_factor(double factor) override;
        double get_max_speed_with_current_cargo() const override;

        /**
         * @brief Проверяет возможность добавления груза
         * @param amount Количество груза для добавления
         * @return bool true если груз можно добавить, false в противном случае
         */
        bool can_add_cargo(double amount) const;
        
        /**
         * @brief Проверяет возможность удаления груза
         * @param amount Количество груза для удаления
         * @return bool true если груз можно удалить, false в противном случае
         */
        bool can_remove_cargo(double amount) const;
};
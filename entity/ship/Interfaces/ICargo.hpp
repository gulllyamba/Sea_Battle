/**
 * @file ICargo.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса ICargo
 */

#pragma once

/**
 * @class ICargo
 * @brief Интерфейс, представляющий грузоподъемность корабля
 */
class ICargo {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~ICargo() = default;

        /**
         * @brief Получает максимальную грузоподъемность
         * @return double Максимальная грузоподъемность
         */
        virtual double get_max_cargo() const = 0;
        
        /**
         * @brief Получает текущий груз
         * @return double Текущий груз
         */
        virtual double get_cargo() const = 0;

        /**
         * @brief Устанавливает максимальную грузоподъемность
         * @param max_cargo Новая максимальная грузоподъемность
         */
        virtual void set_max_cargo(double max_cargo) = 0;
        
        /**
         * @brief Устанавливает текущий груз
         * @param cargo Новое значение текущего груза
         */
        virtual void set_cargo(double cargo) = 0;

        /**
         * @brief Добавляет груз
         * @param amount Количество добавляемого груза
         */
        virtual void add_cargo(double amount) = 0;
        
        /**
         * @brief Удаляет груз
         * @param amount Количество удаляемого груза
         */
        virtual void remove_cargo(double amount) = 0;

        /**
         * @brief Получает коэффициент снижения скорости от груза
         * @return double Коэффициент снижения скорости
         */
        virtual double get_speed_reduction_factor() const = 0;
        
        /**
         * @brief Получает максимальную скорость с текущим грузом
         * @return double Максимальная скорость с текущим грузом
         */
        virtual double get_max_speed_with_current_cargo() const = 0;

        /**
         * @brief Устанавливает коэффициент снижения скорости от груза
         * @param factor Новый коэффициент снижения скорости
         */
        virtual void set_speed_reduction_factor(double factor) = 0;
};
/**
 * @file Mission.hpp
 * @brief Заголовочный файл, содержащий определение класса Mission
 */

#pragma once

#include "../auxiliary/Military.hpp"
#include "../auxiliary/PirateBase.hpp"
#include <memory>

/**
 * @class Mission
 * @brief Класс, представляющий игровую миссию
 */
class Mission {
    private:
        std::string id_; ///< Идентификатор миссии
        Military commander_; ///< Командир миссии
        
        double total_budget_; ///< Общий бюджет миссии
        double current_budget_; ///< Текущий бюджет миссии
        
        double total_cargo_; ///< Общий груз миссии
        double current_cargo_; ///< Текущий груз миссии
        double required_cargo_percentage_; ///< Процент необходимого груза
        
        size_t max_convoy_ships_; ///< Максимальное количество кораблей конвоя
        size_t max_pirate_ships_; ///< Максимальное количество пиратских кораблей
        
        Vector base_a_; ///< Точка A базы
        Vector base_b_; ///< Точка B базы
        double base_size_; ///< Размер базы
        
        std::vector<PirateBase> pirate_bases_; ///< Вектор пиратских баз
        
        bool is_completed_; ///< Флаг завершения миссии
        bool is_successful_; ///< Флаг успешности миссии
    public:
        /**
         * @brief Конструктор с параметрами
         * @param id Идентификатор миссии
         * @param commander Командир миссии
         * @param total_budget Общий бюджет миссии
         * @param total_cargo Общий груз миссии
         * @param required_percentage Процент необходимого груза
         * @param max_convoy_ships Максимальное количество кораблей конвоя
         * @param max_pirate_ships Максимальное количество пиратских кораблей
         * @param base_a Точка A базы
         * @param base_b Точка B базы
         * @param base_size Размер базы
         * @param pirate_bases Вектор пиратских баз
         */
        Mission(
            const std::string& id,
            const Military& commander,
            double total_budget,
            double total_cargo,
            double required_percentage,
            size_t max_convoy_ships,
            size_t max_pirate_ships,
            const Vector& base_a,
            const Vector& base_b,
            double base_size,
            const std::vector<PirateBase>& pirate_bases
        );
        
        /**
         * @brief Получает идентификатор миссии
         * @return std::string Идентификатор миссии
         */
        std::string get_id() const;
        
        /**
         * @brief Получает командира миссии
         * @return Military Командир миссии
         */
        Military get_commander() const;
        
        /**
         * @brief Получает общий бюджет миссии
         * @return double Общий бюджет миссии
         */
        double get_total_budget() const;
        
        /**
         * @brief Получает текущий бюджет миссии
         * @return double Текущий бюджет миссии
         */
        double get_current_budget() const;
        
        /**
         * @brief Получает потраченный бюджет
         * @return double Потраченный бюджет
         */
        double get_spent_budget() const;
        
        /**
         * @brief Проверяет возможность потратить указанную сумму
         * @param amount Сумма для проверки
         * @return bool true если сумму можно потратить, false в противном случае
         */
        bool can_spend(double amount) const;
        
        /**
         * @brief Добавляет бюджет
         * @param amount Сумма для добавления
         * @return bool true если добавление успешно, false в противном случае
         */
        bool add_budget(double amount);
        
        /**
         * @brief Удаляет бюджет
         * @param amount Сумма для удаления
         * @return bool true если удаление успешно, false в противном случае
         */
        bool remove_budget(double amount);

        /**
         * @brief Получает общий груз миссии
         * @return double Общий груз миссии
         */
        double get_total_cargo() const;
        
        /**
         * @brief Получает текущий груз миссии
         * @return double Текущий груз миссии
         */
        double get_current_cargo() const;
        
        /**
         * @brief Получает необходимый груз
         * @return double Необходимый груз
         */
        double get_required_cargo() const;

        /**
         * @brief Добавляет груз
         * @param amount Количество груза для добавления
         * @return bool true если добавление успешно, false в противном случае
         */
        bool add_cargo(double amount);
        
        /**
         * @brief Удаляет груз
         * @param amount Количество груза для удаления
         * @return bool true если удаление успешно, false в противном случае
         */
        bool remove_cargo(double amount);
        
        /**
         * @brief Получает максимальное количество кораблей конвоя
         * @return size_t Максимальное количество кораблей конвоя
         */
        size_t get_max_convoy_ships() const;
        
        /**
         * @brief Получает максимальное количество пиратских кораблей
         * @return size_t Максимальное количество пиратских кораблей
         */
        size_t get_max_pirate_ships() const;

        /**
         * @brief Получает точку A базы
         * @return Vector Точка A базы
         */
        Vector get_base_a() const;
        
        /**
         * @brief Получает точку B базы
         * @return Vector Точка B базы
         */
        Vector get_base_b() const;
        
        /**
         * @brief Получает размер базы
         * @return double Размер базы
         */
        double get_base_size() const;
        
        /**
         * @brief Получает пиратские базы
         * @return const std::vector<PirateBase>& Вектор пиратских баз
         */
        const std::vector<PirateBase>& get_pirate_bases() const;
        
        /**
         * @brief Считает количество пиратских баз
         * @return size_t Количество пиратских баз
         */
        size_t count_pirate_bases() const;
        
        /**
         * @brief Получает пиратскую базу по индексу
         * @param index Индекс пиратской базы
         * @return PirateBase& Ссылка на пиратскую базу
         */
        PirateBase& get_pirate_base(size_t index);
        
        /**
         * @brief Получает пиратскую базу по индексу (константная версия)
         * @param index Индекс пиратской базы
         * @return const PirateBase& Константная ссылка на пиратскую базу
         */
        const PirateBase& get_pirate_base(size_t index) const;
        
        /**
         * @brief Очищает список пиратских баз
         */
        void clear_pirate_bases();
        
        /**
         * @brief Считает количество активных пиратских баз
         * @return size_t Количество активных пиратских баз
         */
        size_t count_active_pirate_bases() const;
        
        /**
         * @brief Проверяет, завершена ли миссия
         * @return bool true если миссия завершена, false в противном случае
         */
        bool is_completed() const;
        
        /**
         * @brief Проверяет, успешна ли миссия
         * @return bool true если миссия успешна, false в противном случае
         */
        bool is_successful() const;
        
        /**
         * @brief Проверяет, выполняется ли миссия
         * @return bool true если миссия в процессе выполнения, false в противном случае
         */
        bool is_in_progress() const;
        
        /**
         * @brief Получает процент выполнения миссии
         * @return double Процент выполнения миссии (0.0 - 100.0)
         */
        double get_completion_percentage() const;
        
        /**
         * @brief Проверяет, достигнута ли цель миссии
         * @return bool true если цель достигнута, false в противном случае
         */
        bool is_goal_achieved() const;

        /**
         * @brief Устанавливает текущий бюджет
         * @param budget Новое значение текущего бюджета
         */
        void set_current_budget(double budget);
        
        /**
         * @brief Устанавливает текущий груз
         * @param cargo Новое значение текущего груза
         */
        void set_current_cargo(double cargo);
        
        /**
         * @brief Устанавливает флаг завершения миссии
         * @param is_completed Новое значение флага завершения
         */
        void set_is_completed(bool is_completed);
        
        /**
         * @brief Устанавливает флаг успешности миссии
         * @param is_successful Новое значение флага успешности
         */
        void set_is_successful(bool is_successful);

        /**
         * @brief Копирующий оператор присваивания
         * @param other другой объект класса
         */
        Mission& operator=(const Mission& other);
};
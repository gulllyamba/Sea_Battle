/**
 * @file ViewConsole.hpp
 * @brief Заголовочный файл, содержащий определение класса ViewConsole
 */

#pragma once

#include "../loader/Loader.hpp"

/**
 * @class ViewConsole
 * @brief Класс консольного представления (View) для управления игровым процессом
 */
class ViewConsole {
    private:
        std::unique_ptr<Presenter> presenter_; ///< Указатель на презентер

        /**
         * @brief Загрузить игру или новая игра
         */
        void save_or_new_game();

        /**
         * @brief Сообщает информацию о миссии
         */
        void mission_info();

        /**
         * @brief Обрабатывает этап покупки кораблей
         */
        void purchase_ships();
        
        /**
         * @brief Обрабатывает этап загрузки кораблей
         */
        void load_ships();
        
        /**
         * @brief Обрабатывает этап покупки оружия
         */
        void purchase_weapons();
        
        /**
         * @brief Обрабатывает этап выполнения миссии
         */
        void mission_sequential();

        /**
         * @brief Обрабатывает этап выполнения миссии
         */
        void mission_parallel();
    public:
        /**
         * @brief Конструктор
         * @param presenter Указатель на презентер
         */
        ViewConsole(std::unique_ptr<Presenter> presenter);
        
        /**
         * @brief Запускает консольное приложение
         * @param is_parallel Флаг обработки боя(true - параллельно, false - последовательно)
         */
        void run(bool is_parallel);
};
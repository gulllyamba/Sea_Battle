/**
 * @file ShipIDGenerator.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipIDGenerator
 */

#pragma once

#include <string>

/**
 * @class ShipIDGenerator
 * @brief Генератор уникальных идентификаторов для кораблей
 */
class ShipIDGenerator {
    private:
        static size_t convoy_counter; ///< Счетчик для кораблей конвоя
        static size_t pirate_counter; ///< Счетчик для пиратских кораблей
        
    public:
        /**
         * @brief Удаленный конструктор (статический класс)
         */
        ShipIDGenerator() = delete;
        
        /**
         * @brief Генерирует идентификатор для корабля конвоя
         * @return std::string Уникальный идентификатор корабля конвоя
         */
        static std::string generate_convoy_id();
        
        /**
         * @brief Генерирует идентификатор для пиратского корабля
         * @return std::string Уникальный идентификатор пиратского корабля
         */
        static std::string generate_pirate_id();
        
        /**
         * @brief Проверяет, является ли идентификатор идентификатором конвоя
         * @param id Идентификатор для проверки
         * @return bool true если идентификатор принадлежит конвою, false в противном случае
         */
        static bool is_convoy_id(const std::string& id);
        
        /**
         * @brief Проверяет, является ли идентификатор идентификатором пирата
         * @param id Идентификатор для проверки
         * @return bool true если идентификатор принадлежит пирату, false в противном случае
         */
        static bool is_pirate_id(const std::string& id);
        
        /**
         * @brief Сбрасывает все счетчики
         */
        static void reset();
        
        /**
         * @brief Сбрасывает счетчик конвоя
         */
        static void reset_convoy();
        
        /**
         * @brief Сбрасывает счетчик пиратов
         */
        static void reset_pirate();

        /**
         * @brief Получает текущее значение счетчика конвоя
         * @return size_t Текущее значение счетчика конвоя
         */
        static size_t get_convoy_counter();
        
        /**
         * @brief Получает текущее значение счетчика пиратов
         * @return size_t Текущее значение счетчика пиратов
         */
        static size_t get_pirate_counter();

        static void set_convoy_counter(size_t cnt);
        static void set_pirate_counter(size_t cnt);
};
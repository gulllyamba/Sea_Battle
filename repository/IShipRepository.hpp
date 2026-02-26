/**
 * @file IShipRepository.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipRepository
 */

#pragma once

#include "ICRUD.hpp"
#include "../entity/ship/Interfaces/IShip.hpp"
#include <memory>
#include <vector>

/**
 * @class IShipRepository
 * @brief Интерфейс репозитория для работы с кораблями
 */
class IShipRepository : public ICRUD<IShip, std::string> {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipRepository() = default;
        
        /**
         * @brief Получает корабли в заданном радиусе от позиции
         * @param position Центральная позиция
         * @param range Радиус поиска
         * @return std::vector<IShip*> Вектор указателей на корабли в радиусе
         */
        virtual std::vector<IShip*> get_ships_in_range(const Vector& position, double range) const = 0;
        
        /**
         * @brief Получает корабли по типу
         * @param type Тип корабля для поиска
         * @return std::vector<IShip*> Вектор указателей на корабли заданного типа
         */
        virtual std::vector<IShip*> get_ships_by_type(const std::string& type) const = 0;
        
        /**
         * @brief Получает живые корабли
         * @return std::vector<IShip*> Вектор указателей на живые корабли
         */
        virtual std::vector<IShip*> get_alive_ships() const = 0;
        
        /**
         * @brief Получает поврежденные корабли
         * @return std::vector<IShip*> Вектор указателей на поврежденные корабли
         */
        virtual std::vector<IShip*> get_damaged_ships() const = 0;
        
        /**
         * @brief Получает грузовые корабли
         * @return std::vector<IShip*> Вектор указателей на грузовые корабли
         */
        virtual std::vector<IShip*> get_cargo_ships() const = 0;
        
        /**
         * @brief Получает атакующие корабли
         * @return std::vector<IShip*> Вектор указателей на атакующие корабли
         */
        virtual std::vector<IShip*> get_attack_ships() const = 0;
        
        /**
         * @brief Получает самый сильный корабль
         * @return IShip* Указатель на самый сильный корабль или nullptr
         */
        virtual IShip* get_strongest_ship() const = 0;
        
        /**
         * @brief Получает самый слабый корабль
         * @return IShip* Указатель на самый слабый корабль или nullptr
         */
        virtual IShip* get_weakest_ship() const = 0;
        
        /**
         * @brief Получает ближайший корабль к заданной позиции
         * @param position Позиция для поиска
         * @return IShip* Указатель на ближайший корабль или nullptr
         */
        virtual IShip* get_closest_ship_to(const Vector& position) const = 0;
        
        /**
         * @brief Получает самый быстрый корабль
         * @return IShip* Указатель на самый быстрый корабль или nullptr
         */
        virtual IShip* get_fastest_ship() const = 0;
        
        /**
         * @brief Получает указатель на корабль по идентификатору
         * @param id Идентификатор корабля
         * @return IShip* Указатель на корабль или nullptr
         */
        virtual IShip* get_ship_ptr(const std::string& id) const = 0;
        
        /**
         * @brief Получает указатели на все корабли
         * @return std::vector<IShip*> Вектор указателей на все корабли
         */
        virtual std::vector<IShip*> get_all_ship_ptrs() const = 0;
        
        /**
         * @brief Проверяет, жив ли корабль
         * @param id Идентификатор корабля
         * @return bool true если корабль жив, false в противном случае
         */
        virtual bool is_ship_alive(const std::string& id) const = 0;
        
        /**
         * @brief Считает количество живых кораблей
         * @return size_t Количество живых кораблей
         */
        virtual size_t count_alive() const = 0;
        
        /**
         * @brief Считает количество кораблей заданного типа
         * @param type Тип корабля
         * @return size_t Количество кораблей заданного типа
         */
        virtual size_t count_by_type(const std::string& type) const = 0;
        
        /**
         * @brief Получает общее здоровье всех кораблей
         * @return double Общее здоровье всех кораблей
         */
        virtual double get_total_health() const = 0;
        
        /**
         * @brief Получает среднее здоровье кораблей
         * @return double Среднее здоровье кораблей
         */
        virtual double get_average_health() const = 0;
};
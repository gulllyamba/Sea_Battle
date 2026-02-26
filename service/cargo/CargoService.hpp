/**
 * @file CargoService.hpp
 * @brief Заголовочный файл, содержащий определение класса CargoService
 */

#pragma once

#include "../../mission/Mission.hpp"
#include "../../repository/ShipRepository.hpp"
#include "../../visitor/cargo/CargoInfoVisitor.hpp"

/**
 * @class CargoService
 * @brief Сервис для управления грузом на кораблях
 */
class CargoService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        ShipRepository& convoy_repo_; ///< Ссылка на репозиторий конвоя

        /**
         * @brief Сортирует корабли по доступной грузоподъемности
         * @param ships Вектор кораблей для сортировки
         * @param ascending true для сортировки по возрастанию, false по убыванию (по умолчанию true)
         */
        void sort_by_available_cargo(std::vector<IShip*>& ships, bool ascending = true);
        
        /**
         * @brief Сортирует корабли по коэффициенту скорости
         * @param ships Вектор кораблей для сортировки
         * @param ascending true для сортировки по возрастанию, false по убыванию (по умолчанию true)
         */
        void sort_by_speed_factor(std::vector<IShip*>& ships, bool ascending = true);
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param convoy_repo Репозиторий конвоя
         */
        CargoService(Mission& mission, ShipRepository& convoy_repo);
        
        /**
         * @brief Загружает груз на корабль
         * @param ship Указатель на корабль
         * @param amount Количество груза
         * @return bool true если загрузка успешна, false в противном случае
         */
        bool load_cargo(IShip* ship, double amount);
        
        /**
         * @brief Выгружает груз с корабля
         * @param ship Указатель на корабль
         * @param amount Количество груза
         * @return bool true если выгрузка успешна, false в противном случае
         */
        bool unload_cargo(IShip* ship, double amount);
        
        /**
         * @brief Автоматически распределяет груз между кораблями
         * @param total_cargo Общее количество груза для распределения
         * @return bool true если распределение успешно, false в противном случае
         */
        bool auto_distribute_cargo(double total_cargo);
        
        /**
         * @brief Распределяет груз для максимальной скорости конвоя
         * @param total_cargo Общее количество груза для распределения
         * @return bool true если распределение успешно, false в противном случае
         */
        bool distribute_for_max_speed(double total_cargo);
        
        /**
         * @brief Распределяет груз равномерно между кораблями
         * @param total_cargo Общее количество груза для распределения
         * @return bool true если распределение успешно, false в противном случае
         */
        bool distribute_evenly(double total_cargo);
        
        /**
         * @brief Получает общий объем груза
         * @return double Общий объем груза
         */
        double get_total_cargo() const;
        
        /**
         * @brief Получает общую грузоподъемность
         * @return double Общая грузоподъемность
         */
        double get_total_cargo_capacity() const;
        
        /**
         * @brief Получает текущий груз
         * @return double Текущий груз
         */
        double get_current_cargo() const;
        
        /**
         * @brief Получает доступный объем груза
         * @return double Доступный объем груза
         */
        double get_available_cargo() const;
        
        /**
         * @brief Получает необходимый груз
         * @return double Необходимый груз
         */
        double get_required_cargo() const;
        
        /**
         * @brief Получает грузовые корабли
         * @return std::vector<IShip*> Вектор указателей на грузовые корабли
         */
        std::vector<IShip*> get_cargo_ships() const;

        /**
         * @brief Проверяет, может ли корабль нести указанное количество груза
         * @param ship Указатель на корабль
         * @param amount Количество груза
         * @return bool true если корабль может нести груз, false в противном случае
         */
        bool can_ship_carry_cargo(IShip* ship, double amount) const;
        
        /**
         * @brief Получает максимальную грузоподъемность корабля
         * @param ship Указатель на корабль
         * @return double Максимальная грузоподъемность корабля
         */
        double get_ship_max_cargo(IShip* ship) const;
        
        /**
         * @brief Получает текущий груз корабля
         * @param ship Указатель на корабль
         * @return double Текущий груз корабля
         */
        double get_ship_current_cargo(IShip* ship) const;
        
        /**
         * @brief Получает доступный объем груза корабля
         * @param ship Указатель на корабль
         * @return double Доступный объем груза корабля
         */
        double get_ship_available_cargo(IShip* ship) const;
        
        /**
         * @brief Вычисляет оптимальную скорость для корабля с учетом груза
         * @param ship Указатель на корабль
         * @param additional_cargo Дополнительный груз (по умолчанию 0.0)
         * @return double Оптимальная скорость корабля
         */
        double calculate_optimal_speed_for_ship(IShip* ship, double additional_cargo = 0.0) const;
        
        /**
         * @brief Вычисляет скорость конвоя с текущим грузом
         * @return double Скорость конвоя с текущим грузом
         */
        double calculate_convoy_speed_with_current_load() const;
};
/**
 * @file MovementService.hpp
 * @brief Заголовочный файл, содержащий определение класса MovementService
 */

#pragma once

#include "../../repository/ShipRepository.hpp"
#include "../../repository/PirateRepository.hpp"
#include "../../mission/Mission.hpp"
#include "../../auxiliary/Vector.hpp"

/**
 * @class MovementService
 * @brief Сервис для управления движением кораблей
 */
class MovementService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        ShipRepository& convoy_repo_; ///< Ссылка на репозиторий конвоя
        PirateRepository& pirate_repo_; ///< Ссылка на репозиторий пиратов
        
        bool is_moving_ = false; ///< Флаг движения конвоя
        double convoy_speed_ = 0.0; ///< Текущая скорость конвоя

        /**
         * @brief Двигает корабль в заданном направлении
         * @param ship Указатель на корабль
         * @param direction Направление движения
         * @param speed Скорость движения
         * @param delta_time Временной шаг
         */
        void move_ship(IShip* ship, const Vector& direction, double speed, double delta_time);
        
        /**
         * @brief Вычисляет расстояние между двумя точками
         * @param from Начальная точка
         * @param to Конечная точка
         * @return double Расстояние между точками
         */
        double get_distance_between(const Vector& from, const Vector& to) const;
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param convoy_repo Репозиторий конвоя
         * @param pirate_repo Репозиторий пиратов
         */
        MovementService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo);
        
        /**
         * @brief Обновляет движение всех кораблей
         * @param delta_time Временной шаг
         */
        void update(double delta_time);
        
        /**
         * @brief Обновляет движение конвоя
         * @param delta_time Временной шаг
         */
        void update_convoy(double delta_time);
        
        /**
         * @brief Обновляет движение пиратов
         * @param delta_time Временной шаг
         */
        void update_pirates(double delta_time);
        
        /**
         * @brief Вычисляет направление движения
         * @param start Начальная точка
         * @param end Конечная точка
         * @return Vector Направление движения
         */
        Vector calculate_direction(const Vector& start, const Vector& end) const;
        
        /**
         * @brief Вычисляет скорость конвоя
         * @return double Скорость конвоя
         */
        double calculate_convoy_speed() const;
        
        /**
         * @brief Начинает движение конвоя
         */
        void start_movement();
        
        /**
         * @brief Начинает движение пиратов
         */
        void start_pirate_movement();
        
        /**
         * @brief Останавливает движение конвоя
         */
        void stop_movement();
        
        /**
         * @brief Останавливает движение пиратов
         */
        void stop_pirate_movement();
        
        /**
         * @brief Проверяет, движется ли конвой
         * @return bool true если конвой движется, false в противном случае
         */
        bool is_moving() const;

        /**
         * @brief Считает количество кораблей в конвое
         * @return size_t Количество кораблей в конвое
         */
        size_t count_convoy_ships() const;
        
        /**
         * @brief Считает количество пиратских кораблей
         * @return size_t Количество пиратских кораблей
         */
        size_t count_pirate_ships() const;
        
        /**
         * @brief Получает текущую скорость конвоя
         * @return double Текущая скорость конвоя
         */
        double get_convoy_speed() const;
        
        /**
         * @brief Получает расстояние до базы B
         * @return double Расстояние до базы B
         */
        double get_distance_to_base_B() const;
        
        /**
         * @brief Проверяет, достиг ли конвой базы B
         * @return bool true если конвой достиг базы B, false в противном случае
         */
        bool has_reached_base_B() const;
        
        /**
         * @brief Получает центр конвоя
         * @return Vector Центр конвоя
         */
        Vector get_convoy_center() const;
        
        /**
         * @brief Получает целевую позицию конвоя
         * @return Vector Целевая позиция конвоя
         */
        Vector get_convoy_target_position() const;
        
        /**
         * @brief Сбрасывает состояние сервиса
         */
        void reset();
};
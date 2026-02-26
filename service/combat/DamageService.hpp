/**
 * @file DamageService.hpp
 * @brief Заголовочный файл, содержащий определение класса DamageService
 */

#pragma once

#include "../../entity/weapon/Interfaces/IWeapon.hpp"
#include "../../entity/ship/Interfaces/IShip.hpp"
#include <random>

/**
 * @class DamageService
 * @brief Сервис для расчета урона в бою
 */
class DamageService {
    private:
        std::uniform_real_distribution<double> dist_; ///< Распределение для случайных чисел

        /**
         * @brief Генерирует случайное число в заданном диапазоне
         * @param min Минимальное значение
         * @param max Максимальное значение
         * @return double Случайное число
         */
        double get_random_double(double min, double max);
    public:
        /**
         * @brief Конструктор
         */
        // DamageService();
        DamageService() = default;
        
        /**
         * @brief Вычисляет урон от оружия по цели
         * @param weapon Указатель на оружие
         * @param target Указатель на цель
         * @param distance Расстояние до цели
         * @return double Вычисленный урон
         */
        double calculate_damage(const IWeapon* weapon, const IShip* target, double distance);
        
        /**
         * @brief Проверяет попадание по цели
         * @param base_accuracy Базовая точность оружия
         * @param distance Расстояние до цели
         * @param max_range Максимальная дальность оружия
         * @return bool true если попадание, false в противном случае
         */
        bool check_hit(double base_accuracy, double distance, double max_range);
        
        /**
         * @brief Вычисляет эффективный урон с учетом расстояния
         * @param base_damage Базовый урон
         * @param distance Расстояние до цели
         * @param max_range Максимальная дальность оружия
         * @return double Эффективный урон
         */
        double calculate_effective_damage(double base_damage, double distance, double max_range);
        
        /**
         * @brief Проверяет критическое попадание
         * @param critical_chance Шанс критического попадания (по умолчанию 0.1)
         * @return bool true если критическое попадание, false в противном случае
         */
        bool is_critical_hit(double critical_chance = 0.1);
};
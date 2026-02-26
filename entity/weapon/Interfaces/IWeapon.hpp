/**
 * @file IWeapon.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IWeapon
 */

#pragma once

#include <string>
#include <memory>

/**
 * @class IWeapon
 * @brief Интерфейс, представляющий оружие
 */
class IWeapon {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IWeapon() = default;

        /**
         * @brief Получает тип оружия
         * @return std::string Тип оружия
         */
        virtual std::string get_type() const = 0;
        
        /**
         * @brief Получает название оружия
         * @return std::string Название оружия
         */
        virtual std::string get_name() const = 0;
        
        /**
         * @brief Получает урон оружия
         * @return double Урон оружия
         */
        virtual double get_damage() const = 0;
        
        /**
         * @brief Получает дальность стрельбы
         * @return double Дальность стрельбы
         */
        virtual double get_range() const = 0;
        
        /**
         * @brief Получает скорострельность
         * @return size_t Скорострельность
         */
        virtual size_t get_fire_rate() const = 0;
        
        /**
         * @brief Получает максимальный боезапас
         * @return size_t Максимальный боезапас
         */
        virtual size_t get_max_ammo() const = 0;
        
        /**
         * @brief Получает текущий боезапас
         * @return size_t Текущий боезапас
         */
        virtual size_t get_current_ammo() const = 0;
        
        /**
         * @brief Получает стоимость оружия
         * @return double Стоимость оружия
         */
        virtual double get_cost() const = 0;
        
        /**
         * @brief Получает точность оружия
         * @return double Точность оружия (0.0 - 1.0)
         */
        virtual double get_accuracy() const = 0;
        
        /**
         * @brief Получает радиус взрыва
         * @return double Радиус взрыва
         */
        virtual double get_explosion_radius() const = 0;

        /**
         * @brief Устанавливает текущий боезапас
         * @param ammo Новое значение боезапаса
         */
        virtual void set_current_ammo(size_t ammo) = 0;
        
        /**
         * @brief Устанавливает урон оружия
         * @param damage Новое значение урона
         */
        virtual void set_damage(double damage) = 0;
        
        /**
         * @brief Устанавливает дальность стрельбы
         * @param range Новое значение дальности
         */
        virtual void set_range(double range) = 0;
        
        /**
         * @brief Устанавливает точность оружия
         * @param accuracy Новое значение точности
         */
        virtual void set_accuracy(double accuracy) = 0;

        /**
         * @brief Клонирует оружие
         * @return std::unique_ptr<IWeapon> Указатель на клон оружия
         */
        virtual std::unique_ptr<IWeapon> clone() const = 0;

        /**
         * @brief Получает описание оружия
         * @return std::string Описание оружия
         */
        virtual std::string get_description() const = 0;
};
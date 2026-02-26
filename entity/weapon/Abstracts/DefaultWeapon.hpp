/**
 * @file DefaultWeapon.hpp
 * @brief Заголовочный файл, содержащий определение класса DefaultWeapon
 */

#pragma once

#include "../Interfaces/IWeapon.hpp"

/**
 * @class DefaultWeapon
 * @brief Абстрактный базовый класс, реализующий базовую функциональность оружия
 */
class DefaultWeapon : public IWeapon {
    protected:
        std::string type; ///< Тип оружия
        std::string name; ///< Название оружия
        double damage; ///< Урон оружия
        double range; ///< Дальность стрельбы
        size_t fire_rate; ///< Скорострельность
        size_t max_ammo; ///< Максимальный боезапас
        size_t current_ammo; ///< Текущий боезапас
        double cost; ///< Стоимость оружия
        double accuracy; ///< Точность оружия (0.0 - 1.0)
        double explosion_radius; ///< Радиус взрыва

        /**
         * @brief Проверяет корректность параметров оружия
         */
        void validate_parameters() const;
    public:
        /**
         * @brief Конструктор с параметрами
         * @param type Тип оружия
         * @param name Название оружия
         * @param damage Урон оружия
         * @param range Дальность стрельбы
         * @param fire_rate Скорострельность
         * @param max_ammo Максимальный боезапас
         * @param cost Стоимость оружия
         * @param accuracy Точность оружия (по умолчанию 0.8)
         * @param explosion_radius Радиус взрыва (по умолчанию 0.0)
         */
        DefaultWeapon(
            const std::string& type,
            const std::string& name,
            double damage, 
            double range, 
            size_t fire_rate, 
            size_t max_ammo, 
            double cost,
            double accuracy = 0.8,
            double explosion_radius = 0.0
        );
        
        /**
         * @brief Деструктор
         */
        ~DefaultWeapon() override = default;

        std::string get_type() const override;
        std::string get_name() const override;
        double get_damage() const override;
        double get_range() const override;
        size_t get_fire_rate() const override;
        size_t get_max_ammo() const override;
        size_t get_current_ammo() const override;
        double get_cost() const override;
        double get_accuracy() const override;
        double get_explosion_radius() const override;

        void set_current_ammo(size_t ammo) override;
        void set_damage(double damage) override;
        void set_range(double range) override;
        void set_accuracy(double accuracy) override;

        virtual std::unique_ptr<IWeapon> clone() const override = 0;

        virtual std::string get_description() const override;
};
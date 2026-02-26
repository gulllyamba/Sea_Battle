/**
 * @file WeaponFactoryManager.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponFactoryManager
 */

#pragma once

#include "GunFactory.hpp"
#include "RocketFactory.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class WeaponFactoryManager
 * @brief Менеджер фабрик оружия, управляющий созданием оружия разных типов
 */
class WeaponFactoryManager {
    private:
        LookupTable<std::string, std::unique_ptr<IWeaponFactory>> factories_; ///< Карта зарегистрированных фабрик
    public:
        /**
         * @brief Конструктор
         */
        WeaponFactoryManager();

        /**
         * @brief Регистрирует фабрику оружия
         * @param type Тип оружия
         * @param factory Указатель на фабрику
         */
        void register_factory(const std::string& type, std::unique_ptr<IWeaponFactory> factory);

        /**
         * @brief Создает оружие с параметрами по умолчанию
         * @param type Тип оружия
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        std::unique_ptr<IWeapon> create_weapon(const std::string& type) const;
        
        /**
         * @brief Создает оружие с заданными параметрами
         * @param type Тип оружия
         * @param name Название оружия
         * @param damage Урон оружия
         * @param range Дальность стрельбы
         * @param fire_rate Скорострельность
         * @param max_ammo Максимальный боезапас
         * @param cost Стоимость оружия
         * @param accuracy Точность оружия
         * @param explosion_radius Радиус взрыва
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        std::unique_ptr<IWeapon> create_weapon(
            const std::string& type,
            const std::string& name,
            double damage,
            double range,
            size_t fire_rate,
            size_t max_ammo,
            double cost,
            double accuracy,
            double explosion_radius = 0.0
        ) const;

        /**
         * @brief Получает фабрику по типу оружия
         * @param type Тип оружия
         * @return IWeaponFactory* Указатель на фабрику или nullptr если не найдена
         */
        IWeaponFactory* get_factory(const std::string& type) const;
        
        /**
         * @brief Проверяет наличие фабрики для заданного типа
         * @param type Тип оружия
         * @return bool true если фабрика зарегистрирована, false в противном случае
         */
        bool has_factory(const std::string& type) const;
};
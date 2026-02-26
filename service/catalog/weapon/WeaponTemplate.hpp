/**
 * @file WeaponTemplate.hpp
 * @brief Заголовочный файл, содержащий определение структуры WeaponTemplate
 */

#pragma once

#include "../../../entity/weapon/Factories/WeaponFactoryManager.hpp"

/**
 * @struct WeaponTemplate
 * @brief Структура шаблона оружия для каталога
 */
struct WeaponTemplate {
    std::string id; ///< Уникальный идентификатор шаблона
    std::string display_name; ///< Отображаемое имя
    std::string type; ///< Тип оружия
    std::string description; ///< Описание оружия
    
    double damage = 0.0; ///< Урон
    double range = 0.0; ///< Дальность
    size_t fire_rate = 0; ///< Скорострельность
    size_t max_ammo = 0; ///< Максимальный боезапас
    double cost = 0.0; ///< Стоимость
    double accuracy = 0.8; ///< Точность
    double explosion_radius = 0.0; ///< Радиус взрыва
    
    /**
     * @brief Создает оружие на основе шаблона
     * @param factory_manager Менеджер фабрик оружия
     * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
     */
    std::unique_ptr<IWeapon> create_weapon(WeaponFactoryManager* factory_manager) const;
    
    /**
     * @brief Получает описание шаблона
     * @return std::string Описание шаблона
     */
    std::string get_description() const;
};
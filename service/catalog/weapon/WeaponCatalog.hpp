/**
 * @file WeaponCatalog.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponCatalog
 */

#pragma once

#include "WeaponTemplate.hpp"
#include <vector>

/**
 * @class WeaponCatalog
 * @brief Каталог шаблонов оружия
 */
class WeaponCatalog {
    private:
        std::vector<WeaponTemplate> templates_; ///< Вектор шаблонов оружия
        std::unique_ptr<WeaponFactoryManager> factory_manager_; ///< Менеджер фабрик оружия

        /**
         * @brief Инициализирует шаблоны оружия по умолчанию
         */
        void initialize_default_templates();
    public:
        /**
         * @brief Конструктор
         * @param factory_manager Менеджер фабрик оружия
         */
        WeaponCatalog(std::unique_ptr<WeaponFactoryManager> factory_manager);
        
        /**
         * @brief Добавляет шаблон в каталог
         * @param temp Шаблон оружия для добавления
         */
        void add_template(const WeaponTemplate& temp);
        
        /**
         * @brief Находит шаблон по идентификатору
         * @param id Идентификатор шаблона
         * @return const WeaponTemplate* Указатель на найденный шаблон или nullptr
         */
        const WeaponTemplate* find_template_by_id(const std::string& id) const;
        
        /**
         * @brief Находит шаблоны по типу
         * @param type Тип оружия
         * @return std::vector<const WeaponTemplate*> Вектор указателей на найденные шаблоны
         */
        std::vector<const WeaponTemplate*> find_templates_by_type(const std::string& type) const;
        
        /**
         * @brief Находит доступные шаблоны по бюджету
         * @param max_budget Максимальный бюджет
         * @return std::vector<const WeaponTemplate*> Вектор указателей на доступные шаблоны
         */
        std::vector<const WeaponTemplate*> find_affordable_templates(double max_budget) const;
        
        /**
         * @brief Находит шаблоны с минимальным уроном
         * @param min_damage Минимальный урон
         * @return std::vector<const WeaponTemplate*> Вектор указателей на найденные шаблоны
         */
        std::vector<const WeaponTemplate*> find_by_min_damage(double min_damage) const;
        
        /**
         * @brief Находит шаблоны с минимальной дальностью
         * @param min_range Минимальная дальность
         * @return std::vector<const WeaponTemplate*> Вектор указателей на найденные шаблоны
         */
        std::vector<const WeaponTemplate*> find_by_min_range(double min_range) const;

        /**
         * @brief Получает все шаблоны
         * @return const std::vector<WeaponTemplate>& Ссылка на вектор всех шаблонов
         */
        const std::vector<WeaponTemplate>& get_all_templates() const;
        
        /**
         * @brief Получает количество шаблонов
         * @return size_t Количество шаблонов
         */
        size_t get_template_count() const;
        
        /**
         * @brief Создает оружие на основе шаблона
         * @param template_id Идентификатор шаблона
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        std::unique_ptr<IWeapon> create_weapon(const std::string& template_id) const;
        
        /**
         * @brief Создает несколько единиц оружия на основе шаблона
         * @param template_id Идентификатор шаблона
         * @param count Количество единиц оружия
         * @return std::vector<std::unique_ptr<IWeapon>> Вектор указателей на созданное оружие
         */
        std::vector<std::unique_ptr<IWeapon>> create_weapons(const std::string& template_id, size_t count) const;

        /**
         * @brief Проверяет доступность шаблона
         * @param template_id Идентификатор шаблона
         * @return bool true если шаблон доступен, false в противном случае
         */
        bool is_template_available(const std::string& template_id) const;
        
        /**
         * @brief Вычисляет общую стоимость набора шаблонов
         * @param template_ids Вектор идентификаторов шаблонов
         * @return double Общая стоимость
         */
        double calculate_total_cost(const std::vector<std::string>& template_ids) const;
        
        /**
         * @brief Проверяет возможность покупки набора шаблонов
         * @param template_ids Вектор идентификаторов шаблонов
         * @param budget Бюджет
         * @return bool true если покупка возможна, false в противном случае
         */
        bool validate_purchase(const std::vector<std::string>& template_ids, double budget) const;
        
        /**
         * @brief Считает количество шаблонов по типу
         * @param type Тип оружия
         * @return size_t Количество шаблонов заданного типа
         */
        size_t count_by_type(const std::string& type) const;
        
        /**
         * @brief Получает минимальную стоимость среди всех шаблонов
         * @return double Минимальная стоимость
         */
        double get_min_cost() const;
        
        /**
         * @brief Получает максимальную стоимость среди всех шаблонов
         * @return double Максимальная стоимость
         */
        double get_max_cost() const;
        
        /**
         * @brief Получает максимальный урон среди всех шаблонов
         * @return double Максимальный урон
         */
        double get_max_damage() const;
        
        /**
         * @brief Получает максимальную дальность среди всех шаблонов
         * @return double Максимальная дальность
         */
        double get_max_range() const;
};
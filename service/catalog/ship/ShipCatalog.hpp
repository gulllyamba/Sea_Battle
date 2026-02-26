/**
 * @file ShipCatalog.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipCatalog
 */

#pragma once

#include "ShipTemplate.hpp"
#include <vector>

/**
 * @class ShipCatalog
 * @brief Каталог шаблонов кораблей
 */
class ShipCatalog {
    private:
        std::vector<ShipTemplate> templates_; ///< Вектор шаблонов кораблей
        std::unique_ptr<ShipFactoryManager> factory_manager_; ///< Менеджер фабрик кораблей

        /**
         * @brief Инициализирует шаблоны кораблей по умолчанию
         */
        void initialize_default_templates();
    public:
        /**
         * @brief Конструктор
         * @param factory_manager Менеджер фабрик кораблей
         */
        ShipCatalog(std::unique_ptr<ShipFactoryManager> factory_manager);
        
        /**
         * @brief Добавляет шаблон в каталог
         * @param temp Шаблон корабля для добавления
         */
        void add_template(const ShipTemplate& temp);

        /**
         * @brief Находит шаблон по идентификатору
         * @param id Идентификатор шаблона
         * @return const ShipTemplate* Указатель на найденный шаблон или nullptr
         */
        const ShipTemplate* find_template_by_id(const std::string& id) const;
        
        /**
         * @brief Находит шаблоны по типу
         * @param type Тип корабля
         * @return std::vector<const ShipTemplate*> Вектор указателей на найденные шаблоны
         */
        std::vector<const ShipTemplate*> find_templates_by_type(const std::string& type) const;
        
        /**
         * @brief Находит доступные шаблоны по бюджету
         * @param max_budget Максимальный бюджет
         * @return std::vector<const ShipTemplate*> Вектор указателей на доступные шаблоны
         */
        std::vector<const ShipTemplate*> find_affordable_templates(double max_budget) const;
        
        /**
         * @brief Получает все шаблоны
         * @return const std::vector<ShipTemplate> Вектор всех шаблонов
         */
        const std::vector<ShipTemplate>& get_all_templates() const;
        
        /**
         * @brief Получает количество шаблонов
         * @return size_t Количество шаблонов
         */
        size_t get_template_count() const;
        
        /**
         * @brief Создает корабль на основе шаблона
         * @param template_id Идентификатор шаблона
         * @param is_convoy Флаг принадлежности к конвою (по умолчанию true)
         * @param position Позиция корабля (по умолчанию (0, 0))
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        std::unique_ptr<IShip> create_ship(const std::string& template_id, bool is_convoy = true, const Vector& position = Vector(0, 0)) const;
        
        /**
         * @brief Создает несколько кораблей на основе шаблона
         * @param template_id Идентификатор шаблона
         * @param count Количество кораблей
         * @param is_convoy Флаг принадлежности к конвою (по умолчанию true)
         * @return std::vector<std::unique_ptr<IShip>> Вектор указателей на созданные корабли
         */
        std::vector<std::unique_ptr<IShip>> create_ships(const std::string& template_id, size_t count, bool is_convoy = true) const;
        
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
         * @param type Тип корабля
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
};
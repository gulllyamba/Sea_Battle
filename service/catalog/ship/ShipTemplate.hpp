/**
 * @file ShipTemplate.hpp
 * @brief Заголовочный файл, содержащий определение структуры ShipTemplate
 */

#pragma once

#include "../../../entity/ship/Factories/ShipFactoryManager.hpp"

/**
 * @struct ShipTemplate
 * @brief Структура шаблона корабля для каталога
 */
struct ShipTemplate {
    std::string id; ///< Уникальный идентификатор шаблона
    std::string display_name; ///< Отображаемое имя
    std::string type; ///< Тип корабля
    std::string description; ///< Описание корабля
    Military default_captain; ///< Капитан по умолчанию

    double max_speed = 0.0; ///< Максимальная скорость
    double max_health = 0.0; ///< Максимальное здоровье
    double cost = 0.0; ///< Стоимость
    
    std::optional<double> max_cargo = std::nullopt; ///< Максимальная грузоподъемность (опционально)
    double speed_reduction_factor = 0.1; ///< Коэффициент снижения скорости от груза

    /**
     * @brief Создает корабль на основе шаблона
     * @param factory_manager Менеджер фабрик кораблей
     * @param is_convoy Флаг принадлежности к конвою
     * @return std::unique_ptr<IShip> Указатель на созданный корабль
     */
    std::unique_ptr<IShip> create_ship(ShipFactoryManager* factory_manager, bool is_convoy) const;
    
    /**
     * @brief Получает описание шаблона
     * @return std::string Описание шаблона
     */
    std::string get_description() const;
};
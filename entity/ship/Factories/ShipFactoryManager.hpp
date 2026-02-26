/**
 * @file ShipFactoryManager.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipFactoryManager
 */

#pragma once

#include "IShipFactory.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class ShipFactoryManager
 * @brief Менеджер фабрик кораблей, управляющий созданием кораблей разных типов
 */
class ShipFactoryManager {
    private:
        LookupTable<std::string, std::unique_ptr<IShipFactory>> factories_; ///< Карта зарегистрированных фабрик
    public:
        /**
         * @brief Конструктор
         */
        ShipFactoryManager();
        
        /**
         * @brief Регистрирует фабрику кораблей
         * @param type Тип корабля
         * @param factory Указатель на фабрику
         */
        void register_factory(const std::string& type, std::unique_ptr<IShipFactory> factory);
        
        /**
         * @brief Создает корабль с параметрами по умолчанию
         * @param type Тип корабля
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        std::unique_ptr<IShip> create_ship(const std::string& type, bool is_convoy = true) const;
        
        /**
         * @brief Создает корабль с заданными параметрами
         * @param type Тип корабля
         * @param name Название корабля
         * @param captain Капитан корабля
         * @param max_speed Максимальная скорость корабля
         * @param max_health Максимальное здоровье корабля
         * @param cost Стоимость корабля
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @param max_cargo Максимальная грузоподъемность (опционально)
         * @param position Позиция корабля (по умолчанию (0, 0))
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        std::unique_ptr<IShip> create_ship(
            const std::string& type,
            const std::string& name,
            const Military& captain,
            double max_speed,
            double max_health,
            double cost,
            bool is_convoy = true,
            std::optional<double> max_cargo = std::nullopt,
            const Vector& position = Vector()
        ) const;

        /**
         * @brief Создает корабль с заданными параметрами и без автоматической генерации ID
         * @param type Тип корабля
         * @param name Название корабля
         * @param captain Капитан корабля
         * @param max_speed Максимальная скорость корабля
         * @param max_health Максимальное здоровье корабля
         * @param cost Стоимость корабля
         * @param is_convoy Флаг конвоя (по умолчанию true)
         * @param max_cargo Максимальная грузоподъемность (опционально)
         * @param position Позиция корабля (по умолчанию (0, 0))
         * @param custom_id Пользовательский идентификатор (по умолчанию "")
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        std::unique_ptr<IShip> create_ship_without_id(
            const std::string& type,
            const std::string& name,
            const Military& captain,
            double max_speed,
            double max_health,
            double cost,
            bool is_convoy = true,
            std::optional<double> max_cargo = std::nullopt,
            const Vector& position = Vector(),
            const std::string& custom_id = ""
        ) const;
        
        /**
         * @brief Получает фабрику по типу корабля
         * @param type Тип корабля
         * @return IShipFactory* Указатель на фабрику или nullptr если не найдена
         */
        IShipFactory* get_factory(const std::string& type) const;
        
        /**
         * @brief Проверяет наличие фабрики для заданного типа
         * @param type Тип корабля
         * @return bool true если фабрика зарегистрирована, false в противном случае
         */
        bool has_factory(const std::string& type) const;

        /**
         * @brief Устанавливает значение максимальной грузоподъемности по умолчанию для указанного типа корабля
         * @param type Тип корабля
         * @param max_cargo Новое значение максимальной грузоподъемности
         */
        void set_default_max_cargo(const std::string& type, double max_cargo);
};
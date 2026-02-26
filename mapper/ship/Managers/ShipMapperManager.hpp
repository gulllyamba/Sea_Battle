/**
 * @file ShipMapperManager.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipMapperManager
 */

#pragma once

#include "../FromDTO/IShipMapper.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class ShipMapperManager
 * @brief Менеджер мапперов для преобразования ShipDTO в IShip
 */
class ShipMapperManager {
    private:
        LookupTable<std::string, std::unique_ptr<IShipMapper>> mappers_; ///< Карта зарегистрированных мапперов
    public:
        /**
         * @brief Конструктор
         */
        ShipMapperManager();

        /**
         * @brief Регистрирует маппер для определенного типа корабля
         * @param type Тип корабля
         * @param mapper Указатель на маппер
         */
        void register_mapper(const std::string& type, std::unique_ptr<IShipMapper> mapper);
        
        /**
         * @brief Создает IShip из ShipDTO
         * @param ship_dto Объект DTO корабля
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        std::unique_ptr<IShip> create_ship(const ShipDTO& ship_dto) const;
};
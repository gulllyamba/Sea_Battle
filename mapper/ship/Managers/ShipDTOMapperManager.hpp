/**
 * @file ShipDTOMapperManager.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipDTOMapperManager
 */

#pragma once

#include "../ToDTO/IShipDTOMapper.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class ShipDTOMapperManager
 * @brief Менеджер мапперов для преобразования IShip в ShipDTO
 */
class ShipDTOMapperManager {
    private:
        LookupTable<std::string, std::unique_ptr<IShipDTOMapper>> mappers_; ///< Карта зарегистрированных мапперов
    public:
        /**
         * @brief Конструктор
         */
        ShipDTOMapperManager();

        /**
         * @brief Регистрирует маппер для определенного типа корабля
         * @param type Тип корабля
         * @param mapper Указатель на маппер
         */
        void register_mapper(const std::string& type, std::unique_ptr<IShipDTOMapper> mapper);
        
        /**
         * @brief Создает ShipDTO из IShip
         * @param ship Указатель на объект корабля
         * @return ShipDTO Объект DTO корабля
         */
        ShipDTO create_ship_dto(const IShip* ship) const;
};
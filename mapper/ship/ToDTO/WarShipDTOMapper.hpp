/**
 * @file WarShipDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса WarShipDTOMapper
 */

#pragma once

#include "IShipDTOMapper.hpp"

/**
 * @class WarShipDTOMapper
 * @brief Маппер для преобразования WarShip в ShipDTO
 */
class WarShipDTOMapper : public IShipDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~WarShipDTOMapper() override = default;

        /**
         * @brief Преобразует IShip (WarShip) в ShipDTO
         * @param ship Указатель на объект военного корабля
         * @return ShipDTO Объект DTO корабля
         */
        ShipDTO transform(const IShip* ship) override;
};
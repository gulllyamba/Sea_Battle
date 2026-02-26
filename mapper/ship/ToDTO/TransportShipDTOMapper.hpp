/**
 * @file TransportShipDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса TransportShipDTOMapper
 */

#pragma once

#include "IShipDTOMapper.hpp"

/**
 * @class TransportShipDTOMapper
 * @brief Маппер для преобразования TransportShip в ShipDTO
 */
class TransportShipDTOMapper : public IShipDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~TransportShipDTOMapper() override = default;

        /**
         * @brief Преобразует IShip (TransportShip) в ShipDTO
         * @param ship Указатель на объект транспортного корабля
         * @return ShipDTO Объект DTO корабля
         */
        ShipDTO transform(const IShip* ship) override;
};
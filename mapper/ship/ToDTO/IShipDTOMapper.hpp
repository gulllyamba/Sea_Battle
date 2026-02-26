/**
 * @file IShipDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipDTOMapper
 */

#pragma once

#include "../../../DTO/ShipDTO.hpp"
#include "../../../entity/ship/Interfaces/IShip.hpp"

/**
 * @class IShipDTOMapper
 * @brief Интерфейс маппера для преобразования IShip в ShipDTO
 */
class IShipDTOMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipDTOMapper() = default;

        /**
         * @brief Преобразует IShip в ShipDTO
         * @param ship Указатель на объект корабля
         * @return ShipDTO Объект DTO корабля
         */
        virtual ShipDTO transform(const IShip* ship) = 0;
};
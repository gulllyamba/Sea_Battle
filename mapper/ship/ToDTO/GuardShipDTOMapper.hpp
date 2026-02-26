/**
 * @file GuardShipDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса GuardShipDTOMapper
 */

#pragma once

#include "IShipDTOMapper.hpp"

/**
 * @class GuardShipDTOMapper
 * @brief Маппер для преобразования GuardShip в ShipDTO
 */
class GuardShipDTOMapper : public IShipDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~GuardShipDTOMapper() override = default;

        /**
         * @brief Преобразует IShip (GuardShip) в ShipDTO
         * @param ship Указатель на объект сторожевого корабля
         * @return ShipDTO Объект DTO корабля
         */
        ShipDTO transform(const IShip* ship) override;
};
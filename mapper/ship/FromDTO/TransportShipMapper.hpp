/**
 * @file TransportShipMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса TransportShipMapper
 */

#pragma once

#include "IShipMapper.hpp"

/**
 * @class TransportShipMapper
 * @brief Маппер для преобразования ShipDTO в TransportShip
 */
class TransportShipMapper : public IShipMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~TransportShipMapper() override = default;

        /**
         * @brief Преобразует ShipDTO в TransportShip
         * @param ship_dto Объект DTO корабля
         * @return std::unique_ptr<IShip> Указатель на созданный транспортный корабль
         */
        std::unique_ptr<IShip> transform(const ShipDTO& ship_dto) override;
};
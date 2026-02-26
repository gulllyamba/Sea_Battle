/**
 * @file WarShipMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса WarShipMapper
 */

#pragma once

#include "IShipMapper.hpp"

/**
 * @class WarShipMapper
 * @brief Маппер для преобразования ShipDTO в WarShip
 */
class WarShipMapper : public IShipMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~WarShipMapper() override = default;

        /**
         * @brief Преобразует ShipDTO в WarShip
         * @param ship_dto Объект DTO корабля
         * @return std::unique_ptr<IShip> Указатель на созданный военный корабль
         */
        std::unique_ptr<IShip> transform(const ShipDTO& ship_dto) override;
};
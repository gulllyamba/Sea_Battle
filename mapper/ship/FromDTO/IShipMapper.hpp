/**
 * @file IShipMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShipMapper
 */

#pragma once

#include "../../../DTO/ShipDTO.hpp"
#include "../../../entity/ship/Interfaces/IShip.hpp"

/**
 * @class IShipMapper
 * @brief Интерфейс маппера для преобразования ShipDTO в IShip
 */
class IShipMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShipMapper() = default;

        /**
         * @brief Преобразует ShipDTO в IShip
         * @param ship_dto Объект DTO корабля
         * @return std::unique_ptr<IShip> Указатель на созданный корабль
         */
        virtual std::unique_ptr<IShip> transform(const ShipDTO& ship_dto) = 0;
};
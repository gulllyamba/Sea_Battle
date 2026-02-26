/**
 * @file GuardShipMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса GuardShipMapper
 */

#pragma once

#include "IShipMapper.hpp"

/**
 * @class GuardShipMapper
 * @brief Маппер для преобразования ShipDTO в GuardShip
 */
class GuardShipMapper : public IShipMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~GuardShipMapper() override = default;

        /**
         * @brief Преобразует ShipDTO в GuardShip
         * @param ship_dto Объект DTO корабля
         * @return std::unique_ptr<IShip> Указатель на созданный сторожевой корабль
         */
        std::unique_ptr<IShip> transform(const ShipDTO& ship_dto) override;
};
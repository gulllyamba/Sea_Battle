/**
 * @file RocketDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса RocketDTOMapper
 */

#pragma once

#include "IWeaponDTOMapper.hpp"

/**
 * @class RocketDTOMapper
 * @brief Маппер для преобразования Rocket в WeaponDTO
 */
class RocketDTOMapper : public IWeaponDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~RocketDTOMapper() override = default;

        /**
         * @brief Преобразует IWeapon (Rocket) в WeaponDTO
         * @param weapon Указатель на объект ракеты
         * @return WeaponDTO Объект DTO оружия
         */
        WeaponDTO transform(const IWeapon* weapon) override;
};
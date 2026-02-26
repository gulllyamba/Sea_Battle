/**
 * @file GunDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса GunDTOMapper
 */

#pragma once

#include "IWeaponDTOMapper.hpp"

/**
 * @class GunDTOMapper
 * @brief Маппер для преобразования Gun в WeaponDTO
 */
class GunDTOMapper : public IWeaponDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~GunDTOMapper() override = default;

        /**
         * @brief Преобразует IWeapon (Gun) в WeaponDTO
         * @param weapon Указатель на объект пушки
         * @return WeaponDTO Объект DTO оружия
         */
        WeaponDTO transform(const IWeapon* weapon) override;
};
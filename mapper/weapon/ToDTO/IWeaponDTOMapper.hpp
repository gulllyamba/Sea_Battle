/**
 * @file IWeaponDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IWeaponDTOMapper
 */

#pragma once

#include "../../../DTO/WeaponDTO.hpp"
#include "../../../entity/weapon/Interfaces/IWeapon.hpp"

/**
 * @class IWeaponDTOMapper
 * @brief Интерфейс маппера для преобразования IWeapon в WeaponDTO
 */
class IWeaponDTOMapper{
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IWeaponDTOMapper() = default;

        /**
         * @brief Преобразует IWeapon в WeaponDTO
         * @param weapon Указатель на объект оружия
         * @return WeaponDTO Объект DTO оружия
         */
        virtual WeaponDTO transform(const IWeapon* weapon) = 0;
};
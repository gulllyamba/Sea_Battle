/**
 * @file IWeaponMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IWeaponMapper
 */

#pragma once

#include "../../../DTO/WeaponDTO.hpp"
#include "../../../entity/weapon/Interfaces/IWeapon.hpp"

/**
 * @class IWeaponMapper
 * @brief Интерфейс маппера для преобразования WeaponDTO в IWeapon
 */
class IWeaponMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IWeaponMapper() = default;

        /**
         * @brief Преобразует WeaponDTO в IWeapon
         * @param weapon_dto Объект DTO оружия
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        virtual std::unique_ptr<IWeapon> transform(const WeaponDTO& weapon_dto) = 0;
};
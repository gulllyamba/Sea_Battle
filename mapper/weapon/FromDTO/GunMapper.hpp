/**
 * @file GunMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса GunMapper
 */

#pragma once

#include "IWeaponMapper.hpp"

/**
 * @class GunMapper
 * @brief Маппер для преобразования WeaponDTO в Gun
 */
class GunMapper : public IWeaponMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~GunMapper() override = default;

        /**
         * @brief Преобразует WeaponDTO в Gun
         * @param weapon_dto Объект DTO оружия
         * @return std::unique_ptr<IWeapon> Указатель на созданную пушку
         */
        std::unique_ptr<IWeapon> transform(const WeaponDTO& weapon_dto) override;
};
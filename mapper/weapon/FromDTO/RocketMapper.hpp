/**
 * @file RocketMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса RocketMapper
 */

#pragma once

#include "IWeaponMapper.hpp"

/**
 * @class RocketMapper
 * @brief Маппер для преобразования WeaponDTO в Rocket
 */
class RocketMapper : public IWeaponMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~RocketMapper() override = default;

        /**
         * @brief Преобразует WeaponDTO в Rocket
         * @param weapon_dto Объект DTO оружия
         * @return std::unique_ptr<IWeapon> Указатель на созданную ракету
         */
        std::unique_ptr<IWeapon> transform(const WeaponDTO& weapon_dto) override;
};
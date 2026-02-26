/**
 * @file PirateBaseDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса PirateBaseDTOMapper
 */

#pragma once

#include "IPirateBaseDTOMapper.hpp"

/**
 * @class PirateBaseDTOMapper
 * @brief Реализация маппера для преобразования PirateBase в PirateBaseDTO
 */
class PirateBaseDTOMapper : public IPirateBaseDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~PirateBaseDTOMapper() override = default;

        /**
         * @brief Преобразует PirateBase в PirateBaseDTO
         * @param base Объект пиратской базы
         * @return PirateBaseDTO Объект DTO пиратской базы
         */
        PirateBaseDTO transform(const PirateBase& base) override;
};
/**
 * @file IPirateBaseDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IPirateBaseDTOMapper
 */

#pragma once

#include "../../../DTO/PirateBaseDTO.hpp"
#include "../../../auxiliary/PirateBase.hpp"

/**
 * @class IPirateBaseDTOMapper
 * @brief Интерфейс маппера для преобразования PirateBase в PirateBaseDTO
 */
class IPirateBaseDTOMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IPirateBaseDTOMapper() = default;

        /**
         * @brief Преобразует PirateBase в PirateBaseDTO
         * @param base Объект пиратской базы
         * @return PirateBaseDTO Объект DTO пиратской базы
         */
        virtual PirateBaseDTO transform(const PirateBase& base) = 0;
};
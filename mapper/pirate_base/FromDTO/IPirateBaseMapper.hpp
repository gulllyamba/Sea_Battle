/**
 * @file IPirateBaseMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IPirateBaseMapper
 */

#pragma once

#include "../../../DTO/PirateBaseDTO.hpp"
#include "../../../auxiliary/PirateBase.hpp"

/**
 * @class IPirateBaseMapper
 * @brief Интерфейс маппера для преобразования PirateBaseDTO в PirateBase
 */
class IPirateBaseMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IPirateBaseMapper() = default;

        /**
         * @brief Преобразует PirateBaseDTO в PirateBase
         * @param base_dto Объект DTO пиратской базы
         * @return PirateBase Объект пиратской базы
         */
        virtual PirateBase transform(const PirateBaseDTO& base_dto) = 0;
};
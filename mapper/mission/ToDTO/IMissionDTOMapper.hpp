/**
 * @file IMissionDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IMissionDTOMapper
 */

#pragma once

#include "../../../DTO/MissionDTO.hpp"
#include "../../../mission/Mission.hpp"

/**
 * @class IMissionDTOMapper
 * @brief Интерфейс маппера для преобразования Mission в MissionDTO
 */
class IMissionDTOMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IMissionDTOMapper() = default;

        /**
         * @brief Преобразует Mission в MissionDTO
         * @param mission Указатель на объект миссии
         * @return MissionDTO Объект DTO миссии
         */
        virtual MissionDTO transform(const Mission* mission) = 0;
};
/**
 * @file MissionDTOMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса MissionDTOMapper
 */

#pragma once

#include "IMissionDTOMapper.hpp"

/**
 * @class MissionDTOMapper
 * @brief Реализация маппера для преобразования Mission в MissionDTO
 */
class MissionDTOMapper : public IMissionDTOMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~MissionDTOMapper() override = default;

        /**
         * @brief Преобразует Mission в MissionDTO
         * @param mission Указатель на объект миссии
         * @return MissionDTO Объект DTO миссии
         */
        MissionDTO transform(const Mission* mission) override;
};
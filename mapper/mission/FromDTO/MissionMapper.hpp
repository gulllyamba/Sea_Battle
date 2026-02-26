/**
 * @file MissionMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса MissionMapper
 */

#pragma once

#include "IMissionMapper.hpp"

/**
 * @class MissionMapper
 * @brief Реализация маппера для преобразования MissionDTO в Mission
 */
class MissionMapper : public IMissionMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~MissionMapper() override = default;

        /**
         * @brief Преобразует MissionDTO в Mission
         * @param mission_dto Объект DTO миссии
         * @return std::unique_ptr<Mission> Указатель на созданную миссию
         */
        std::unique_ptr<Mission> transform(const MissionDTO& mission_dto) override;
};
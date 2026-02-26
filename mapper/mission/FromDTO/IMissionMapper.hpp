/**
 * @file IMissionMapper.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IMissionMapper
 */

#pragma once

#include "../../../DTO/MissionDTO.hpp"
#include "../../../mission/Mission.hpp"

/**
 * @class IMissionMapper
 * @brief Интерфейс маппера для преобразования MissionDTO в Mission
 */
class IMissionMapper {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IMissionMapper() = default;

        /**
         * @brief Преобразует MissionDTO в Mission
         * @param mission_dto Объект DTO миссии
         * @return std::unique_ptr<Mission> Указатель на созданную миссию
         */
        virtual std::unique_ptr<Mission> transform(const MissionDTO& mission_dto) = 0;
};
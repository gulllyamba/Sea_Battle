/**
 * @file PirateBaseMapper.hpp
 * @brief Заголовочный файл, содержащий определение класса PirateBaseMapper
 */

#pragma once

#include "IPirateBaseMapper.hpp"

/**
 * @class PirateBaseMapper
 * @brief Реализация маппера для преобразования PirateBaseDTO в PirateBase
 */
class PirateBaseMapper : public IPirateBaseMapper {
    public:
        /**
         * @brief Деструктор
         */
        ~PirateBaseMapper() override = default;

        /**
         * @brief Преобразует PirateBaseDTO в PirateBase
         * @param base_dto Объект DTO пиратской базы
         * @return PirateBase Объект пиратской базы
         */
        PirateBase transform(const PirateBaseDTO& base_dto) override;
};
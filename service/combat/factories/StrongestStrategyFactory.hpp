/**
 * @file StrongestStrategyFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса StrongestStrategyFactory
 */

#pragma once

#include "IAttackStrategyFactory.hpp"

/**
 * @class StrongestStrategyFactory
 * @brief Фабрика для создания стратегии атаки по самой сильной цели
 */
class StrongestStrategyFactory : public IAttackStrategyFactory {
    public:
        /**
         * @brief Деструктор
         */
        ~StrongestStrategyFactory() override;

        std::unique_ptr<IAttackStrategy> create_strategy() const override;
        std::string get_name() const override;
        std::string get_description() const override;
};
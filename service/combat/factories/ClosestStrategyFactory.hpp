/**
 * @file ClosestStrategyFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса ClosestStrategyFactory
 */

#pragma once

#include "IAttackStrategyFactory.hpp"

/**
 * @class ClosestStrategyFactory
 * @brief Фабрика для создания стратегии атаки по ближайшей цели
 */
class ClosestStrategyFactory : public IAttackStrategyFactory {
    public:
        /**
         * @brief Деструктор
         */
        ~ClosestStrategyFactory() override;

        std::unique_ptr<IAttackStrategy> create_strategy() const override;
        std::string get_name() const override;
        std::string get_description() const override;
};
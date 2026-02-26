/**
 * @file WeakestStrategyFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса WeakestStrategyFactory
 */

#pragma once

#include "IAttackStrategyFactory.hpp"

/**
 * @class WeakestStrategyFactory
 * @brief Фабрика для создания стратегии атаки по самой слабой цели
 */
class WeakestStrategyFactory : public IAttackStrategyFactory {
    public:
        /**
         * @brief Деструктор
         */
        ~WeakestStrategyFactory() override;

        std::unique_ptr<IAttackStrategy> create_strategy() const override;
        std::string get_name() const override;
        std::string get_description() const override;
};
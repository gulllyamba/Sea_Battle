/**
 * @file RandomStrategyFactory.hpp
 * @brief Заголовочный файл, содержащий определение класса RandomStrategyFactory
 */

#pragma once

#include "IAttackStrategyFactory.hpp"

/**
 * @class RandomStrategyFactory
 * @brief Фабрика для создания стратегии случайного выбора цели
 */
class RandomStrategyFactory : public IAttackStrategyFactory {
    public:
        /**
         * @brief Деструктор
         */
        ~RandomStrategyFactory() override;

        std::unique_ptr<IAttackStrategy> create_strategy() const override;
        std::string get_name() const override;
        std::string get_description() const override;
};
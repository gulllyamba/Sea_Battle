/**
 * @file IAttackStrategyFactory.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IAttackStrategyFactory
 */

#pragma once

#include "../strategy/IAttackStrategy.hpp"

/**
 * @class IAttackStrategyFactory
 * @brief Интерфейс фабрики стратегий атаки
 */
class IAttackStrategyFactory {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IAttackStrategyFactory() = default;
        
        /**
         * @brief Создает стратегию атаки
         * @return std::unique_ptr<IAttackStrategy> Указатель на созданную стратегию
         */
        virtual std::unique_ptr<IAttackStrategy> create_strategy() const = 0;
        
        /**
         * @brief Получает название стратегии
         * @return std::string Название стратегии
         */
        virtual std::string get_name() const = 0;
        
        /**
         * @brief Получает описание стратегии
         * @return std::string Описание стратегии
         */
        virtual std::string get_description() const = 0;
};
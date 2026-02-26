/**
 * @file AttackStrategyFactoryManager.hpp
 * @brief Заголовочный файл, содержащий определение класса AttackStrategyFactoryManager
 */

#pragma once

#include "IAttackStrategyFactory.hpp"
#include "../../../template/LookupTable.hpp"
#include <vector>

/**
 * @class AttackStrategyFactoryManager
 * @brief Менеджер фабрик стратегий атаки
 */
class AttackStrategyFactoryManager {
    private:
        LookupTable<std::string, std::unique_ptr<IAttackStrategyFactory>> factories_; ///< Таблица зарегистрированных фабрик
    public:
        /**
         * @brief Конструктор
         */
        AttackStrategyFactoryManager();
        
        /**
         * @brief Регистрирует фабрику стратегии
         * @param name Название стратегии
         * @param factory Указатель на фабрику
         */
        void register_factory(const std::string& name, std::unique_ptr<IAttackStrategyFactory> factory);
        
        /**
         * @brief Создает стратегию по названию
         * @param name Название стратегии
         * @return std::unique_ptr<IAttackStrategy> Указатель на созданную стратегию
         */
        std::unique_ptr<IAttackStrategy> create_strategy(const std::string& name) const;
        
        /**
         * @brief Получает фабрику по названию стратегии
         * @param type Название стратегии
         * @return IAttackStrategyFactory* Указатель на фабрику или nullptr
         */
        IAttackStrategyFactory* get_factory(const std::string& type) const;
        
        /**
         * @brief Получает список доступных стратегий
         * @return std::vector<std::string> Вектор названий доступных стратегий
         */
        std::vector<std::string> get_available_strategies() const;
        
        /**
         * @brief Проверяет наличие стратегии по названию
         * @param name Название стратегии
         * @return bool true если стратегия зарегистрирована, false в противном случае
         */
        bool has_strategy(const std::string& name) const;
};
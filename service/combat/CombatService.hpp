/**
 * @file CombatService.hpp
 * @brief Заголовочный файл, содержащий определение класса CombatService
 */

#pragma once

#include "../../mission/Mission.hpp"
#include "../../repository/ShipRepository.hpp"
#include "../../repository/PirateRepository.hpp"
#include "../../service/combat/DamageService.hpp"
#include "../../service/combat/strategy/IAttackStrategy.hpp"
#include "factories/AttackStrategyFactoryManager.hpp"

#include <thread>
#include <mutex>

/**
 * @class CombatService
 * @brief Сервис для управления боем между кораблями
 */
class CombatService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        ShipRepository& convoy_repo_; ///< Ссылка на репозиторий конвоя
        PirateRepository& pirate_repo_; ///< Ссылка на репозиторий пиратов
        DamageService& damage_service_; ///< Ссылка на сервис урона
        
        std::unique_ptr<AttackStrategyFactoryManager> strategy_factory_; ///< Менеджер фабрик стратегий
        std::unique_ptr<IAttackStrategy> convoy_strategy_; ///< Стратегия конвоя
        std::unique_ptr<IAttackStrategy> pirate_strategy_; ///< Стратегия пиратов

        mutable std::mutex mission_mutex_; ///< Мьютекс для доступа к данным миссии
        std::atomic<bool> stop_threads_{false}; ///< Флаг остановки потоков

        std::vector<IShip*> get_convoy_ships_safe() const;
        std::vector<IShip*> get_pirate_ships_safe() const;
        void process_convoy_attack_range(size_t start, size_t end, const std::vector<IShip*>& convoy_ships, const std::vector<IShip*>& pirate_ships);
        void process_pirate_attack_range(size_t start, size_t end, const std::vector<IShip*>& convoy_ships, const std::vector<IShip*>& pirate_ships);

        /**
         * @brief Выполняет атаку одного корабля по другому
         * @param attacker Атакующий корабль
         * @param target Целевой корабль
         * @return bool true если атака успешна, false в противном случае
         */
        bool execute_attack(IShip* attacker, IShip* target);

        /**
         * @brief Обрабатывает атаки конвоя
         */
        void process_convoy_attack();
        
        /**
         * @brief Обрабатывает атаки пиратов
         */
        void process_pirate_attack();
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param convoy_repo Репозиторий конвоя
         * @param pirate_repo Репозиторий пиратов
         * @param damage_service Сервис урона
         */
        CombatService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo, DamageService& damage_service);
        
        ~CombatService();

        /**
         * @brief Устанавливает стратегию конвоя
         * @param strategy_name Название стратегии
         * @return bool true если стратегия успешно установлена, false в противном случае
         */
        bool set_convoy_strategy(const std::string& strategy_name);
        
        /**
         * @brief Устанавливает стратегию пиратов
         * @param strategy_name Название стратегии
         * @return bool true если стратегия успешно установлена, false в противном случае
         */
        bool set_pirate_strategy(const std::string& strategy_name);
        
        /**
         * @brief Получает список доступных стратегий
         * @return std::vector<std::string> Вектор названий доступных стратегий
         */
        std::vector<std::string> get_available_strategies() const;
        
        /**
         * @brief Получает текущую стратегию конвоя
         * @return std::string Название текущей стратегии конвоя
         */
        std::string get_current_convoy_strategy() const;
        
        /**
         * @brief Получает текущую стратегию пиратов
         * @return std::string Название текущей стратегии пиратов
         */
        std::string get_current_pirate_strategy() const;
        
        /**
         * @brief Выполняет автоматическую атаку всех кораблей(последовательно)
         */
        void auto_attack_all_sequential();

        /**
         * @brief Выполняет автоматическую атаку всех кораблей(параллельно)
         */
        void auto_attack_all_parallel();
        
        /**
         * @brief Получает количество живых кораблей конвоя
         * @return size_t Количество живых кораблей конвоя
         */
        size_t get_convoy_alive_count() const;
        
        /**
         * @brief Получает количество живых пиратских кораблей
         * @return size_t Количество живых пиратских кораблей
         */
        size_t get_pirates_alive_count() const;

        /**
         * @brief Получает количество пиратских баз
         * @return size_t Количество пиратских баз
         */
        size_t get_pirate_bases_count() const;
        
        /**
         * @brief Проверяет, активирована ли база
         * @param index Индекс базы
         * @return bool true если база активирована, false в противном случае
         */
        bool is_base_activated(size_t index) const;
        
        /**
         * @brief Проверяет, уничтожена ли база
         * @param index Индекс базы
         * @return bool true если база уничтожена, false в противном случае
         */
        bool is_base_defeated(size_t index) const;

        /**
         * @brief Получает указатели на все корабли
         * @return std::vector<IShip*> Вектор указателей на все корабли
         */
        std::vector<IShip*> get_all_ship_ptrs() const;
        
        /**
         * @brief Получает указатель на корабль по идентификатору
         * @param ship_id Идентификатор корабля
         * @return IShip* Указатель на корабль или nullptr
         */
        IShip* get_ship_ptr(const std::string& ship_id) const;
        
        /**
         * @brief Получает атакующие корабли
         * @return std::vector<IShip*> Вектор указателей на атакующие корабли
         */
        std::vector<IShip*> get_attack_ships() const;
        
        /**
         * @brief Получает указатели на все пиратские корабли
         * @return std::vector<IShip*> Вектор указателей на все пиратские корабли
         */
        std::vector<IShip*> get_all_pirate_ship_ptrs() const;
};
/**
 * @file PirateSpawnService.hpp
 * @brief Заголовочный файл, содержащий определение класса PirateSpawnService
 */

#pragma once

#include "../../mission/Mission.hpp"
#include "../../repository/PirateRepository.hpp"
#include "../catalog/ship/ShipCatalog.hpp"
#include "../catalog/weapon/WeaponCatalog.hpp"
#include "../../auxiliary/PirateBase.hpp"
#include <random>

/**
 * @enum Level
 * @brief Уровень сложности игры
 */
enum Level {
    EAZY, ///< Легкий уровень
    MEDIUM, ///< Средний уровень
    HARD ///< Сложный уровень
};

/**
 * @class PirateSpawnService
 * @brief Сервис для спавна пиратских кораблей и управления пиратскими базами
 */
class PirateSpawnService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        PirateRepository& pirate_repo_; ///< Ссылка на репозиторий пиратов
        ShipCatalog& ship_catalog_; ///< Ссылка на каталог кораблей
        WeaponCatalog& weapon_catalog_; ///< Ссылка на каталог оружия

        Level level_; ///< Уровень сложности
        
        std::mt19937 rng_; ///< Генератор случайных чисел
        std::uniform_real_distribution<double> position_offset_dist_; ///< Распределение для случайного смещения позиции
        
        size_t total_pirates_spawned_; ///< Общее количество созданных пиратов
        
        /**
         * @brief Вычисляет расстояние между двумя точками
         * @param a Первая точка
         * @param b Вторая точка
         * @return double Расстояние между точками
         */
        double calculate_distance(const Vector& a, const Vector& b) const;
        
        /**
         * @brief Создает пиратский корабль
         * @param position Позиция корабля
         * @return std::unique_ptr<IShip> Указатель на созданный пиратский корабль
         */
        std::unique_ptr<IShip> create_pirate_ship(const Vector& position);
        
        /**
         * @brief Создает пиратов на базе
         * @param base Пиратская база
         */
        void spawn_pirates_at_base(PirateBase& base);
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param pirate_repo Репозиторий пиратов
         * @param ship_catalog Каталог кораблей
         * @param weapon_catalog Каталог оружия
         * @param level Уровень сложности
         */
        PirateSpawnService(Mission& mission, PirateRepository& pirate_repo, ShipCatalog& ship_catalog, WeaponCatalog& weapon_catalog, Level level);
        
        /**
         * @brief Обновляет состояние сервиса
         * @param convoy_position Позиция конвоя
         */
        void update(const Vector& convoy_position);
        
        /**
         * @brief Обновляет статус пиратской базы
         * @param base Пиратская база
         */
        void update_base_status(PirateBase& base);
        
        /**
         * @brief Очищает все пиратские базы
         */
        void clear_bases();
        
        // size_t spawn_pirates_at_position(const Vector& position, size_t count);
        
        /**
         * @brief Получает пиратские базы
         * @return const std::vector<PirateBase>& Вектор пиратских баз
         */
        const std::vector<PirateBase>& get_pirate_bases() const;
        
        /**
         * @brief Получает количество активных баз
         * @return size_t Количество активных баз
         */
        size_t get_active_base_count() const;
        
        /**
         * @brief Получает количество уничтоженных баз
         * @return size_t Количество уничтоженных баз
         */
        size_t get_defeated_base_count() const;
        
        /**
         * @brief Получает общее количество созданных пиратов
         * @return size_t Общее количество созданных пиратов
         */
        size_t get_total_pirates_spawned() const;
        
        /**
         * @brief Проверяет, уничтожены ли все базы
         * @return bool true если все базы уничтожены, false в противном случае
         */
        bool are_all_bases_defeated() const;
        
        /**
         * @brief Устанавливает диапазон случайного смещения позиции
         * @param min_offset Минимальное смещение
         * @param max_offset Максимальное смещение
         */
        void set_position_offset_range(double min_offset, double max_offset);
        
        /**
         * @brief Генерирует случайное смещение
         * @return Vector Случайное смещение
         */
        Vector generate_random_offset();

        void set_seed(size_t seed);
};
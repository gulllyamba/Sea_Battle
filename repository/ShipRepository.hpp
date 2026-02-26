/**
 * @file ShipRepository.hpp
 * @brief Заголовочный файл, содержащий определение класса ShipRepository
 */

#pragma once

#include "IShipRepository.hpp"
#include "../template/LookupTable.hpp"

/**
 * @class ShipRepository
 * @brief Реализация репозитория для работы с кораблями конвоя
 */
class ShipRepository : public IShipRepository {
    private:
        LookupTable<std::string, std::unique_ptr<IShip>> ships_; ///< Таблица кораблей конвоя
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        ShipRepository() = default;
        
        /**
         * @brief Деструктор
         */
        ~ShipRepository() override = default;
        
        void create(std::unique_ptr<IShip> ship) override;
        std::unique_ptr<IShip> read(const std::string& id) const override;
        std::vector<std::unique_ptr<IShip>> read_all() const override;
        bool exists(const std::string& id) const override;
        size_t count() const override;
        void update(std::unique_ptr<IShip> ship) override;
        void remove(const std::string& id) override;
        void clear() override;
        
        std::vector<IShip*> get_ships_in_range(const Vector& position, double range) const override;
        std::vector<IShip*> get_ships_by_type(const std::string& type) const override;
        std::vector<IShip*> get_alive_ships() const override;
        std::vector<IShip*> get_damaged_ships() const override;
        std::vector<IShip*> get_cargo_ships() const override;
        std::vector<IShip*> get_attack_ships() const override;
        IShip* get_strongest_ship() const override;
        IShip* get_weakest_ship() const override;
        IShip* get_closest_ship_to(const Vector& position) const override;
        IShip* get_fastest_ship() const override;
        
        IShip* get_ship_ptr(const std::string& id) const override;
        std::vector<IShip*> get_all_ship_ptrs() const override;
        bool is_ship_alive(const std::string& id) const override;
        
        size_t count_alive() const override;
        size_t count_by_type(const std::string& type) const override;
        double get_total_health() const override;
        double get_average_health() const override;
};
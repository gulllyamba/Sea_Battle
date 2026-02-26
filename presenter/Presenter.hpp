/**
 * @file Presenter.hpp
 * @brief Заголовочный файл, содержащий определение класса Presenter
 */

#pragma once

#include "IPresenter.hpp"

#include "../service/cargo/CargoService.hpp"
#include "../service/combat/CombatService.hpp"
#include "../service/ID/ShipIDGenerator.hpp"
#include "../service/movement/MovementService.hpp"
#include "../service/pirate/PirateSpawnService.hpp"
#include "../service/purchase/PurchaseService.hpp"
#include "../service/state/YamlStateService.hpp"
#include "../template/LookupTable.hpp"

/**
 * @class Presenter
 * @brief Реализация презентера, управляющего игровым процессом
 */
class Presenter : public IPresenter {
    private:
        Mission& mission_; ///< Ссылка на миссию

        ShipCatalog &ship_catalog_; ///< Ссылка на каталог кораблей
        WeaponCatalog &weapon_catalog_; ///< Ссылка на каталог оружия

        CargoService& cargo_service_; ///< Ссылка на сервис груза
        CombatService& combat_service_; ///< Ссылка на сервис боя
        MovementService& movement_service_; ///< Ссылка на сервис движения
        PirateSpawnService& pirate_spawn_service_; ///< Ссылка на сервис спавна пиратов
        PurchaseService& purchase_service_; ///< Ссылка на сервис покупок
        YamlStateService& state_service_; ///< Ссылка на сервис состояния YAML

        MissionDTOMapper& mission_dto_mapper_; ///< Ссылка на маппер миссии DTO
        ShipDTOMapperManager& ship_dto_mapper_manager_; ///< Ссылка на менеджер мапперов кораблей DTO
        PirateBaseDTOMapper& pirate_base_dto_mapper_; ///< Ссылка на маппер пиратских баз DTO
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param ship_catalog Каталог кораблей
         * @param weapon_catalog Каталог оружия
         * @param cargo_service Сервис груза
         * @param combat_service Сервис боя
         * @param movement_service Сервис движения
         * @param pirate_spawn_service Сервис спавна пиратов
         * @param purchase_service Сервис покупок
         * @param state_service Сервис состояния YAML
         * @param mission_dto_mapper Маппер миссии DTO
         * @param ship_dto_mapper_manager Менеджер мапперов кораблей DTO
         * @param pirate_base_dto_mapper Маппер пиратских баз DTO
         */
        Presenter(
            Mission& mission,
            ShipCatalog &ship_catalog,
            WeaponCatalog &weapon_catalog,
            CargoService& cargo_service,
            CombatService& combat_service,
            MovementService& movement_service,
            PirateSpawnService& pirate_spawn_service,
            PurchaseService& purchase_service,
            YamlStateService& state_service,
            MissionDTOMapper& mission_dto_mapper,
            ShipDTOMapperManager& ship_dto_mapper_manager,
            PirateBaseDTOMapper& pirate_base_dto_mapper
        );
        
        /**
         * @brief Деструктор
         */
        ~Presenter() override = default;

        const std::vector<ShipTemplate> get_available_ships() const override;
        const std::vector<WeaponTemplate> get_available_weapons() const override;

        bool purchase_ship(const std::string &template_id) override;
        bool sell_ship(const std::string &template_id) override;
        bool sell_weapon(const std::string &ship_id, PlaceForWeapon place) override;
        double get_current_budget() const override;
        double get_total_budget() const override;

        bool has_weapon_in_place(const std::string &ship_id, PlaceForWeapon place) const override;
        bool can_spend(double amount) const override;
        bool has_free_place() const override;
        bool has_occupied_place() const override;

        bool install_weapon(const std::string &ship_id, PlaceForWeapon place, const std::string &weapon_template_id) override;

        double get_total_cargo() const override;
        double get_current_cargo() const override;
        double get_remaining_cargo() const override;
        double get_ship_capacity(const std::string &ship_id) const override;
        double get_ship_current_cargo(const std::string &ship_id) const override;

        bool load_cargo(const std::string& ship_id, double amount) override;
        bool unload_cargo(const std::string &ship_id, double amount) override;
        void auto_distribute_cargo() override;

        MissionDTO get_mission() const override;
        std::vector<ShipDTO> get_convoy_ships() const override;
        std::vector<ShipDTO> get_cargo_ships() const override;
        std::vector<ShipDTO> get_attack_ships() const override;
        size_t count_convoy_ships() const override;
        size_t count_alive_convoy_ships() const override;
        std::vector<ShipDTO> get_pirate_ships() const override;
        size_t count_alive_pirate_ships() const override;
        ShipDTO get_ship_by_id(std::string& ship_id) const override;
        std::vector<PirateBaseDTO> get_pirate_bases() const override;

        void move_convoy(double dt) override;
        void start_convoy() override;
        void stop_convoy() override;

        void move_pirates(double dt) override;
        void start_pirates() override;
        void stop_pirates() override;

        void auto_combat_sequential() override;
        void auto_combat_parallel() override;

        int has_activated_base() const override;
        void update_base_status(size_t index) override;

        bool has_reached_destination() const override;
        bool mission_completed() const override;
        double get_convoy_speed() const override;
        Vector get_convoy_center() const override;
        double get_distanse_to_destination() const override;
        double get_min_weapon_cost() const;

        void set_convoy_strategy(const std::string& strategy) override;
        void set_pirate_strategy(const std::string& strategy) override;
        
        void save_game(const std::string& path) override;
        void load_game(const std::string& path) override;

        std::string convoy_info() const override;
        std::string pirate_info() const override;
};
/**
 * @file Loader.hpp
 * @brief Заголовочный файл, содержащий определение класса Loader
 */

#pragma once

#include "../presenter/Presenter.hpp"

/**
 * @class Loader
 * @brief Класс для загрузки и инициализации игровых компонентов
 */
class Loader {
    private:
        std::unique_ptr<Mission> mission_; ///< Указатель на миссию
        std::unique_ptr<ShipRepository> convoy_repo_; ///< Указатель на репозиторий конвоя
        std::unique_ptr<PirateRepository> pirate_repo_; ///< Указатель на репозиторий пиратов

        std::unique_ptr<ShipCatalog> ship_catalog_; ///< Указатель на каталог кораблей
        std::unique_ptr<WeaponCatalog> weapon_catalog_; ///< Указатель на каталог оружия

        std::unique_ptr<MovementService> movement_service_; ///< Указатель на сервис движения
        std::unique_ptr<CombatService> combat_service_; ///< Указатель на сервис боя
        std::unique_ptr<DamageService> damage_service_; ///< Указатель на сервис урона
        std::unique_ptr<PurchaseService> purchase_service_; ///< Указатель на сервис покупок
        std::unique_ptr<CargoService> cargo_service_; ///< Указатель на сервис груза
        std::unique_ptr<PirateSpawnService> pirate_spawn_service_; ///< Указатель на сервис спавна пиратов
        std::unique_ptr<YamlStateService> state_service_; ///< Указатель на сервис состояния YAML

        std::unique_ptr<MissionDTOMapper> mission_dto_mapper_; ///< Указатель на маппер миссии DTO
        std::unique_ptr<MissionMapper> mission_mapper_; ///< Указатель на маппер миссии
        std::unique_ptr<ShipDTOMapperManager> ship_dto_mapper_manager_; ///< Указатель на менеджер мапперов кораблей DTO
        std::unique_ptr<ShipMapperManager> ship_mapper_manager_; ///< Указатель на менеджер мапперов кораблей
        std::unique_ptr<PirateBaseDTOMapper> pirate_base_dto_mapper_; ///< Указатель на маппер пиратских баз DTO
        std::unique_ptr<PirateBaseMapper> pirate_base_mapper_; ///< Указатель на маппер пиратских баз

        std::unique_ptr<Mission> create_mission_test(size_t convoy_count, size_t pirate_count);
    public:
        /**
         * @brief Создает презентер с настройками по умолчанию
         * @return std::unique_ptr<Presenter> Указатель на созданный презентер
         */
        std::unique_ptr<Presenter> create_default_presenter();

        /**
         * @brief Создает презентер для тестов
         * @param convoy_count Количество кораблей конвоя
         * @param pirate_count Количество кораблей пиратов
         * @return std::unique_ptr<Presenter> Указатель на созданный презентер
         */
        std::unique_ptr<Presenter> create_presenter_test(size_t convoy_count, size_t pirate_count);
};
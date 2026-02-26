/**
 * @file YamlStateService.hpp
 * @brief Заголовочный файл, содержащий определение класса YamlStateService
 */

#pragma once

#include <yaml-cpp/yaml.h>

#include "IStateService.hpp"
#include "../../mission/Mission.hpp"
#include "../../repository/PirateRepository.hpp"
#include "../../repository/ShipRepository.hpp"
#include "../../mapper/mission/FromDTO/MissionMapper.hpp"
#include "../../mapper/mission/ToDTO/MissionDTOMapper.hpp"
#include "../../mapper/pirate_base/FromDTO/PirateBaseMapper.hpp"
#include "../../mapper/pirate_base/ToDTO/PirateBaseDTOMapper.hpp"
#include "../../mapper/ship/Managers/ShipDTOMapperManager.hpp"
#include "../../mapper/ship/Managers/ShipMapperManager.hpp"
#include "../../mapper/weapon/Managers/WeaponDTOMapperManager.hpp"
#include "../../mapper/weapon/Managers/WeaponMapperManager.hpp"

/**
 * @class YamlStateService
 * @brief Сервис для сохранения и загрузки состояния игры в формате YAML
 */
class YamlStateService : public IStateService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        ShipRepository& convoy_repo_; ///< Ссылка на репозиторий конвоя
        PirateRepository& pirate_repo_; ///< Ссылка на репозиторий пиратов

        MissionDTOMapper& mission_dto_mapper_; ///< Ссылка на маппер миссии DTO
        MissionMapper& mission_mapper_; ///< Ссылка на маппер миссии
        ShipDTOMapperManager& ship_dto_mapper_manager_; ///< Ссылка на менеджер мапперов кораблей DTO
        ShipMapperManager& ship_mapper_manager_; ///< Ссылка на менеджер мапперов кораблей

        /**
         * @brief Сериализует вектор в YAML-узел
         * @param vector Вектор для сериализации
         * @return YAML::Node YAML-узел с данными вектора
         */
        YAML::Node serialize_vector(const Vector& vector) const;
        
        /**
         * @brief Десериализует вектор из YAML-узла
         * @param node YAML-узел с данными вектора
         * @return Vector Вектор
         */
        Vector deserialize_vector(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует военнослужащего в YAML-узел
         * @param military Военнослужащий для сериализации
         * @return YAML::Node YAML-узел с данными военнослужащего
         */
        YAML::Node serialize_military(const Military& military) const;
        
        /**
         * @brief Десериализует военнослужащего из YAML-узла
         * @param node YAML-узел с данными военнослужащего
         * @return Military Военнослужащий
         */
        Military deserialize_military(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует место для оружия в YAML-узел
         * @param place Место для оружия
         * @return YAML::Node YAML-узел с данными места для оружия
         */
        YAML::Node serialize_place_for_weapon(PlaceForWeapon place) const;
        
        /**
         * @brief Десериализует место для оружия из YAML-узла
         * @param node YAML-узел с данными места для оружия
         * @return PlaceForWeapon Место для оружия
         */
        PlaceForWeapon deserialize_place_for_weapon(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует DTO оружия в YAML-узел
         * @param weapon_dto DTO оружия
         * @return YAML::Node YAML-узел с данными DTO оружия
         */
        YAML::Node serialize_weapon_dto(const WeaponDTO& weapon_dto) const;
        
        /**
         * @brief Десериализует DTO оружия из YAML-узла
         * @param node YAML-узел с данными DTO оружия
         * @return WeaponDTO DTO оружия
         */
        WeaponDTO deserialize_weapon_dto(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует DTO корабля в YAML-узел
         * @param ship_dto DTO корабля
         * @return YAML::Node YAML-узел с данными DTO корабля
         */
        YAML::Node serialize_ship_dto(const ShipDTO& ship_dto) const;
        
        /**
         * @brief Десериализует DTO корабля из YAML-узла
         * @param node YAML-узел с данными DTO корабля
         * @return ShipDTO DTO корабля
         */
        ShipDTO deserialize_ship_dto(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует DTO пиратской базы в YAML-узел
         * @param base_dto DTO пиратской базы
         * @return YAML::Node YAML-узел с данными DTO пиратской базы
         */
        YAML::Node serialize_pirate_base_dto(const PirateBaseDTO& base_dto) const;
        
        /**
         * @brief Десериализует DTO пиратской базы из YAML-узла
         * @param node YAML-узел с данными DTO пиратской базы
         * @return PirateBaseDTO DTO пиратской базы
         */
        PirateBaseDTO deserialize_pirate_base_dto(const YAML::Node& node) const;
        
        /**
         * @brief Сериализует DTO миссии в YAML-узел
         * @param mission_dto DTO миссии
         * @return YAML::Node YAML-узел с данными DTO миссии
         */
        YAML::Node serialize_mission_dto(const MissionDTO& mission_dto) const;
        
        /**
         * @brief Десериализует DTO миссии из YAML-узла
         * @param node YAML-узел с данными DTO миссии
         * @return MissionDTO DTO миссии
         */
        MissionDTO deserialize_mission_dto(const YAML::Node& node) const;
        
        /**
         * @brief Сохраняет корабли в YAML-узел
         * @param repository Репозиторий кораблей
         * @param parent_node Родительский YAML-узел
         * @param node_name Имя узла для кораблей
         */
        void save_ships_to_yaml(IShipRepository* repository, YAML::Node& parent_node, const std::string& node_name);
        
        /**
         * @brief Загружает корабли из YAML-узла
         * @param repository Репозиторий кораблей
         * @param ships_node YAML-узел с данными кораблей
         * @param is_convoy true если корабли конвоя, false если пираты
         */
        void load_ships_from_yaml(IShipRepository* repository, const YAML::Node& ships_node, bool is_convoy);
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param convoy_repo Репозиторий конвоя
         * @param pirate_repo Репозиторий пиратов
         * @param mission_dto_mapper Маппер миссии DTO
         * @param mission_mapper Маппер миссии
         * @param ship_dto_mapper_manager Менеджер мапперов кораблей DTO
         * @param ship_mapper_manager Менеджер мапперов кораблей
         */
        YamlStateService(
            Mission& mission,
            ShipRepository& convoy_repo,
            PirateRepository& pirate_repo,
            MissionDTOMapper& mission_dto_mapper,
            MissionMapper& mission_mapper,
            ShipDTOMapperManager& ship_dto_mapper_manager,
            ShipMapperManager& ship_mapper_manager
        );
        
        /**
         * @brief Деструктор
         */
        ~YamlStateService() override;

        bool save(const std::string& path) override;
        bool load(const std::string& path) override;

        bool load_mission(const std::string& path) override;

        /**
         * @brief Получает информацию о конвое
         * @return std::string Информация о конвое
         */
        std::string convoy_info() const;
        
        /**
         * @brief Получает информацию о пиратах
         * @return std::string Информация о пиратах
         */
        std::string pirate_info() const;
};
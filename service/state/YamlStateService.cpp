#include "YamlStateService.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../entity/ship/Concrete/WarShip.hpp"
#include "../../entity/ship/Concrete/TransportShip.hpp"

YAML::Node YamlStateService::serialize_vector(const Vector& vector) const {
    YAML::Node node;
    node["x"] = vector.x;
    node["y"] = vector.y;
    return node;
}

Vector YamlStateService::deserialize_vector(const YAML::Node& node) const {
    Vector vector;
    vector.x = node["x"].as<double>();
    vector.y = node["y"].as<double>();
    return vector;
}

YAML::Node YamlStateService::serialize_military(const Military& military) const {
    YAML::Node node;
    node["fio"] = military.FIO;
    node["rank"] = military.rank;
    return node;
}

Military YamlStateService::deserialize_military(const YAML::Node& node) const {
    Military military;
    military.FIO = node["fio"].as<std::string>();
    military.rank = node["rank"].as<std::string>();
    return military;
}

YAML::Node YamlStateService::serialize_place_for_weapon(PlaceForWeapon place) const {
    switch (place) {
        case PlaceForWeapon::stern: return YAML::Node("stern");
        case PlaceForWeapon::bow: return YAML::Node("bow");
        case PlaceForWeapon::port: return YAML::Node("port");
        case PlaceForWeapon::starboard: return YAML::Node("starboard");
        default: return YAML::Node("unknown");
    }
}

PlaceForWeapon YamlStateService::deserialize_place_for_weapon(const YAML::Node& node) const {
    std::string place = node.as<std::string>();
    if (place == "stern") return PlaceForWeapon::stern;
    if (place == "bow") return PlaceForWeapon::bow;
    if (place == "port") return PlaceForWeapon::port;
    if (place == "starboard") return PlaceForWeapon::starboard;
    throw std::runtime_error("Unknown place for weapon: " + place);
}

YAML::Node YamlStateService::serialize_weapon_dto(const WeaponDTO& weapon_dto) const {
    YAML::Node node;
    node["type"] = weapon_dto.type;
    node["name"] = weapon_dto.name;
    node["damage"] = weapon_dto.damage;
    node["range"] = weapon_dto.range;
    node["fire_rate"] = weapon_dto.fire_rate;
    node["max_ammo"] = weapon_dto.max_ammo;
    node["current_ammo"] = weapon_dto.current_ammo;
    node["cost"] = weapon_dto.cost;
    node["accuracy"] = weapon_dto.accuracy;
    node["explosion_radius"] = weapon_dto.explosion_radius;
    return node;
}

WeaponDTO YamlStateService::deserialize_weapon_dto(const YAML::Node& node) const {
    WeaponDTO weapon_dto;
    weapon_dto.type = node["type"].as<std::string>();
    weapon_dto.name = node["name"].as<std::string>();
    weapon_dto.damage = node["damage"].as<double>();
    weapon_dto.range = node["range"].as<double>();
    weapon_dto.fire_rate = node["fire_rate"].as<size_t>();
    weapon_dto.max_ammo = node["max_ammo"].as<size_t>();
    weapon_dto.current_ammo = node["current_ammo"].as<size_t>();
    weapon_dto.cost = node["cost"].as<double>();
    weapon_dto.accuracy = node["accuracy"].as<double>();
    weapon_dto.explosion_radius = node["explosion_radius"].as<double>();
    return weapon_dto;
}

YAML::Node YamlStateService::serialize_ship_dto(const ShipDTO& ship_dto) const {
    YAML::Node node;
    node["type"] = ship_dto.type;
    node["id"] = ship_dto.id;
    node["name"] = ship_dto.name;
    node["captain"] = serialize_military(ship_dto.captain);
    node["max_speed"] = ship_dto.max_speed;
    node["current_speed"] = ship_dto.current_speed;
    node["cost"] = ship_dto.cost;
    node["position"] = serialize_vector(ship_dto.position);
    node["max_health"] = ship_dto.max_health;
    node["current_health"] = ship_dto.current_health;
    node["is_alive"] = ship_dto.is_alive;
    node["is_convoy"] = ship_dto.is_convoy;
    
    if (ship_dto.max_cargo > 0) {
        node["max_cargo"] = ship_dto.max_cargo;
        node["current_cargo"] = ship_dto.current_cargo;
        node["speed_reduction_factor"] = ship_dto.speed_reduction_factor;
    }
    
    if (ship_dto.weapons.size() > 0) {
        YAML::Node weapons_node;
        for (const auto& [place, weapon_dto] : ship_dto.weapons) {
            YAML::Node weapon_entry;
            weapon_entry["place"] = serialize_place_for_weapon(place);
            weapon_entry["weapon"] = serialize_weapon_dto(weapon_dto);
            weapons_node.push_back(weapon_entry);
        }
        node["weapons"] = weapons_node;
    }
    
    return node;
}

ShipDTO YamlStateService::deserialize_ship_dto(const YAML::Node& node) const {
    ShipDTO ship_dto;
    ship_dto.type = node["type"].as<std::string>();
    ship_dto.id = node["id"].as<std::string>();
    ship_dto.name = node["name"].as<std::string>();
    ship_dto.captain = deserialize_military(node["captain"]);
    ship_dto.max_speed = node["max_speed"].as<double>();
    ship_dto.current_speed = node["current_speed"].as<double>();
    ship_dto.cost = node["cost"].as<double>();
    ship_dto.position = deserialize_vector(node["position"]);
    ship_dto.max_health = node["max_health"].as<double>();
    ship_dto.current_health = node["current_health"].as<double>();
    ship_dto.is_alive = node["is_alive"].as<bool>();
    ship_dto.is_convoy = node["is_convoy"].as<bool>();
    
    if (node["max_cargo"]) {
        ship_dto.max_cargo = node["max_cargo"].as<double>();
        ship_dto.current_cargo = node["current_cargo"].as<double>();
        ship_dto.speed_reduction_factor = node["speed_reduction_factor"].as<double>();
    }
    else {
        ship_dto.max_cargo = 0.0;
        ship_dto.current_cargo = 0.0;
        ship_dto.speed_reduction_factor = 0.0;
    }
    
    if (node["weapons"]) {
        for (const auto& weapon : node["weapons"]) {
            PlaceForWeapon place = deserialize_place_for_weapon(weapon["place"]);
            WeaponDTO weapon_dto = deserialize_weapon_dto(weapon["weapon"]);
            ship_dto.weapons[place] = weapon_dto;
        }
    }
    
    return ship_dto;
}

YAML::Node YamlStateService::serialize_pirate_base_dto(const PirateBaseDTO& base_dto) const {
    YAML::Node node;
    node["position"] = serialize_vector(base_dto.position);
    node["trigger_distance"] = base_dto.trigger_distance;
    node["ship_count"] = base_dto.ship_count;
    node["is_activated"] = base_dto.is_activated;
    node["is_defeated"] = base_dto.is_defeated;
    
    YAML::Node spawned_ids_node;
    for (const auto& id : base_dto.spawned_pirate_ids) {
        spawned_ids_node.push_back(id);
    }
    node["spawned_pirate_ids"] = spawned_ids_node;
    
    return node;
}

PirateBaseDTO YamlStateService::deserialize_pirate_base_dto(const YAML::Node& node) const {
    PirateBaseDTO base_dto;
    base_dto.position = deserialize_vector(node["position"]);
    base_dto.trigger_distance = node["trigger_distance"].as<double>();
    base_dto.ship_count = node["ship_count"].as<size_t>();
    base_dto.is_activated = node["is_activated"].as<bool>();
    base_dto.is_defeated = node["is_defeated"].as<bool>();
    
    if (node["spawned_pirate_ids"]) {
        for (const auto& id_node : node["spawned_pirate_ids"]) {
            base_dto.spawned_pirate_ids.push_back(id_node.as<std::string>());
        }
    }
    
    return base_dto;
}

YAML::Node YamlStateService::serialize_mission_dto(const MissionDTO& mission_dto) const {
    YAML::Node node;
    node["id"] = mission_dto.id;
    node["commander"] = serialize_military(mission_dto.commander);
    node["total_budget"] = mission_dto.total_budget;
    node["current_budget"] = mission_dto.current_budget;
    node["total_cargo"] = mission_dto.total_cargo;
    node["current_cargo"] = mission_dto.current_cargo;
    node["required_cargo_percentage"] = mission_dto.required_cargo_percentage;
    node["max_convoy_ships"] = mission_dto.max_convoy_ships;
    node["max_pirate_ships"] = mission_dto.max_pirate_ships;
    node["base_a"] = serialize_vector(mission_dto.base_a);
    node["base_b"] = serialize_vector(mission_dto.base_b);
    node["base_size"] = mission_dto.base_size;
    
    YAML::Node pirate_bases_node;
    for (const auto& base_dto : mission_dto.pirate_bases) {
        pirate_bases_node.push_back(serialize_pirate_base_dto(base_dto));
    }
    node["pirate_bases"] = pirate_bases_node;

    node["is_completed"] = mission_dto.is_completed;
    node["is_successful"] = mission_dto.is_successful;
    
    return node;
}

MissionDTO YamlStateService::deserialize_mission_dto(const YAML::Node& node) const {
    MissionDTO mission_dto;
    mission_dto.id = node["id"].as<std::string>();
    mission_dto.commander = deserialize_military(node["commander"]);
    mission_dto.total_budget = node["total_budget"].as<double>();
    mission_dto.current_budget = node["current_budget"].as<double>();
    mission_dto.total_cargo = node["total_cargo"].as<double>();
    mission_dto.required_cargo_percentage = node["required_cargo_percentage"].as<double>();
    mission_dto.current_cargo = node["current_cargo"].as<double>();
    mission_dto.max_convoy_ships = node["max_convoy_ships"].as<size_t>();
    mission_dto.max_pirate_ships = node["max_pirate_ships"].as<size_t>();
    mission_dto.base_a = deserialize_vector(node["base_a"]);
    mission_dto.base_b = deserialize_vector(node["base_b"]);
    mission_dto.base_size = node["base_size"].as<double>();
    
    if (node["pirate_bases"]) {
        for (const auto& base_node : node["pirate_bases"]) {
            mission_dto.pirate_bases.push_back(deserialize_pirate_base_dto(base_node));
        }
    }

    mission_dto.is_completed = node["is_completed"].as<bool>();
    mission_dto.is_successful = node["is_successful"].as<bool>();
    
    return mission_dto;
}

void YamlStateService::save_ships_to_yaml(IShipRepository* repository, YAML::Node& parent_node, const std::string& node_name) {
    if (!repository) throw std::invalid_argument("Repository cannot be null");

    YAML::Node ships_node;
    auto all_ships = repository->read_all();
    
    for (const auto& ship : all_ships) {
        if (ship) {
            auto ship_dto = ship_dto_mapper_manager_.create_ship_dto(ship.get());
            ships_node.push_back(serialize_ship_dto(ship_dto));
        }
    }
    
    parent_node[node_name] = ships_node;
}

void YamlStateService::load_ships_from_yaml(IShipRepository* repository, const YAML::Node& ships_node, bool is_convoy) {
    if (!repository) throw std::invalid_argument("Repository cannot be null");
    
    for (const auto& ship_node : ships_node) {
        try {
            ShipDTO ship_dto = deserialize_ship_dto(ship_node);
            ship_dto.is_convoy = is_convoy;
            
            auto ship = ship_mapper_manager_.create_ship(ship_dto);
            if (ship) repository->create(std::move(ship));
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading ship: " << e.what() << std::endl;
        }
    }
}

YamlStateService::YamlStateService(
    Mission& mission,
    ShipRepository& convoy_repo,
    PirateRepository& pirate_repo,
    MissionDTOMapper& mission_dto_mapper,
    MissionMapper& mission_mapper,
    ShipDTOMapperManager& ship_dto_mapper_manager,
    ShipMapperManager& ship_mapper_manager) : 
    mission_(mission),
    convoy_repo_(convoy_repo),
    pirate_repo_(pirate_repo),
    mission_dto_mapper_(mission_dto_mapper),
    mission_mapper_(mission_mapper),
    ship_dto_mapper_manager_(ship_dto_mapper_manager),
    ship_mapper_manager_(ship_mapper_manager) {}

YamlStateService::~YamlStateService() = default;

bool YamlStateService::save(const std::string& path) {
    try {
        YAML::Node root;
        
        MissionDTO mission_dto = mission_dto_mapper_.transform(&mission_);
        root["mission"] = serialize_mission_dto(mission_dto);
        
        save_ships_to_yaml(&convoy_repo_, root, "convoy_ships");
        save_ships_to_yaml(&pirate_repo_, root, "pirate_ships");
        
        std::ofstream file(path);
        if (!file.is_open()) return false;
        file << root;
        file.close();
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving state: " << e.what() << std::endl;
        return false;
    }
}

bool YamlStateService::load(const std::string& path) {
    try {
        YAML::Node root = YAML::LoadFile(path);
        if (!root["mission"]) throw std::runtime_error("Invalid save file: missing mission section");
        
        MissionDTO mission_dto = deserialize_mission_dto(root["mission"]);
        auto mission = mission_mapper_.transform(mission_dto);
        mission_ = *mission;
        
        if (!mission) throw std::runtime_error("Failed to create mission from DTO");
        
        if (root["convoy_ships"]) load_ships_from_yaml(&convoy_repo_, root["convoy_ships"], true);
        if (root["pirate_ships"]) load_ships_from_yaml(&pirate_repo_, root["pirate_ships"], false);
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading state: " << e.what() << std::endl;
        return false;
    }
}

bool YamlStateService::load_mission(const std::string& path) {
    try {
        YAML::Node root = YAML::LoadFile(path);
        if (!root["mission"]) throw std::runtime_error("Invalid mission file: missing mission section");

        MissionDTO mission_dto = deserialize_mission_dto(root["mission"]);
        auto mission = mission_mapper_.transform(mission_dto);
        if (!mission) throw std::runtime_error("Failed to create mission from DTO");
        mission_ = std::move(*mission);

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading mission: " << e.what() << std::endl;
        return false;
    }
}

std::string YamlStateService::convoy_info() const {
    std::ostringstream oss;
    oss << "\nPosition: ";
    std::vector<IShip*> ships = convoy_repo_.get_alive_ships();
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")[" << ships[i]->get_position().x << ", " << ships[i]->get_position().y << "]; ";
    }
    oss << "\nSpeed: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")" << ships[i]->get_speed() << "; ";
    }
    oss << "\nHealth: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")" << ships[i]->get_health() << "; ";
    }
    oss << "\nCargo: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        if (ships[i]->get_type() == "war") {
            WarShip* war_ship = dynamic_cast<WarShip*>(ships[i]);
            oss << war_ship->get_ID() << ")" << war_ship->get_cargo() << "; ";
        }
        else if (ships[i]->get_type() == "transport") {
            TransportShip* transport_ship = dynamic_cast<TransportShip*>(ships[i]);
            oss << transport_ship->get_ID() << ")" << transport_ship->get_cargo() << "; ";
        }
    }
    oss << "\n";
    return oss.str();
}

std::string YamlStateService::pirate_info() const {
    std::ostringstream oss;
    oss << "\nPosition: ";
    std::vector<IShip*> ships = pirate_repo_.get_alive_ships();
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")[" << ships[i]->get_position().x << ", " << ships[i]->get_position().y << "]; ";
    }
    oss << "\nSpeed: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")" << ships[i]->get_speed() << "; ";
    }
    oss << "\nHealth: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        oss << ships[i]->get_ID() << ")" << ships[i]->get_health() << "; ";
    }
    oss << "\nCargo: ";
    for (size_t i = 0 ; i < ships.size(); ++i) {
        if (ships[i]->get_type() == "war") {
            WarShip* war_ship = dynamic_cast<WarShip*>(ships[i]);
            oss << war_ship->get_ID() << ")" << war_ship->get_cargo() << "; ";
        }
        else if (ships[i]->get_type() == "transport") {
            TransportShip* transport_ship = dynamic_cast<TransportShip*>(ships[i]);
            oss << transport_ship->get_ID() << ")" << transport_ship->get_cargo() << "; ";
        }
    }
    oss << "\n";
    return oss.str();
}
#include "Presenter.hpp"
#include "../visitor/place/PlaceForDamageVisitor.hpp"
#include "../visitor/cargo/CargoInfoVisitor.hpp"

Presenter::Presenter(
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
    PirateBaseDTOMapper& pirate_base_dto_mapper) :
    mission_(mission),
    ship_catalog_(ship_catalog),
    weapon_catalog_(weapon_catalog),
    cargo_service_(cargo_service),
    combat_service_(combat_service),
    movement_service_(movement_service),
    pirate_spawn_service_(pirate_spawn_service),
    purchase_service_(purchase_service),
    state_service_(state_service),
    mission_dto_mapper_(mission_dto_mapper),
    ship_dto_mapper_manager_(ship_dto_mapper_manager),
    pirate_base_dto_mapper_(pirate_base_dto_mapper) {}

const std::vector<ShipTemplate> Presenter::get_available_ships() const {
    return ship_catalog_.get_all_templates();
}

const std::vector<WeaponTemplate> Presenter::get_available_weapons() const {
    return weapon_catalog_.get_all_templates();
}

double Presenter::get_current_budget() const {
    return purchase_service_.get_current_budget();
}

bool Presenter::purchase_ship(const std::string &template_id) {
    const auto* template_info = ship_catalog_.find_template_by_id(template_id);
    if (!template_info || template_info->cost > get_current_budget()) return false;
    Vector position = pirate_spawn_service_.generate_random_offset();
    return purchase_service_.buy_ship(template_id, true, position);
}

bool Presenter::sell_ship(const std::string &template_id) {
    const auto* template_info = ship_catalog_.find_template_by_id(template_id);
    for (auto* ship : combat_service_.get_all_ship_ptrs()) {
        if (template_info->display_name == ship->get_name()) {
            purchase_service_.sell_ship(ship);
            break;
        }
    }
    return true;
}

bool Presenter::sell_weapon(const std::string &ship_id, PlaceForWeapon place) {
    return purchase_service_.sell_weapon(ship_id, place);
}

double Presenter::get_total_budget() const {
    return purchase_service_.get_initial_budget();
}

bool Presenter::install_weapon(const std::string &ship_id, PlaceForWeapon place, const std::string &weapon_template_id) {
    auto weapon = purchase_service_.buy_weapon(weapon_template_id);
    return purchase_service_.install_weapon(ship_id, place, std::move(weapon));
}

bool Presenter::has_weapon_in_place(const std::string &ship_id, PlaceForWeapon place) const {
    return purchase_service_.has_weapon_in_place(ship_id, place);
}

bool Presenter::has_free_place() const {
    return purchase_service_.has_free_place();
}

bool Presenter::has_occupied_place() const {
    return purchase_service_.has_occupied_place();
}

bool Presenter::can_spend(double amount) const {
    return purchase_service_.can_spend(amount);
}

double Presenter::get_total_cargo() const {
    return cargo_service_.get_total_cargo();
}

double Presenter::get_current_cargo() const {
    return cargo_service_.get_current_cargo();
}

double Presenter::get_remaining_cargo() const {
    return get_total_cargo() - get_current_cargo();
}

double Presenter::get_ship_capacity(const std::string &ship_id) const {
    auto ship = combat_service_.get_ship_ptr(ship_id);
    if (!ship) return 0.0;

    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    return visitor.get_max_cargo();
}

double Presenter::get_ship_current_cargo(const std::string &ship_id) const {
    auto ship = combat_service_.get_ship_ptr(ship_id);
    if (!ship) return 0.0;

    CargoInfoVisitor visitor;
    ship->accept(&visitor);
    return visitor.get_current_cargo();
}

bool Presenter::load_cargo(const std::string& ship_id, double amount) {
    auto ship = combat_service_.get_ship_ptr(ship_id);
    if (!ship) return false;        
    return cargo_service_.load_cargo(ship, amount);
}

bool Presenter::unload_cargo(const std::string &ship_id, double amount) {
    auto ship = combat_service_.get_ship_ptr(ship_id);
    if (!ship) return false;
    return cargo_service_.unload_cargo(ship, amount);
}

void Presenter::auto_distribute_cargo() {
    cargo_service_.distribute_evenly(cargo_service_.get_total_cargo() - cargo_service_.get_current_cargo());
}

MissionDTO Presenter::get_mission() const {
    return mission_dto_mapper_.transform(&mission_);
}

std::vector<ShipDTO> Presenter::get_convoy_ships() const {
    std::vector<ShipDTO> result;
    auto ships = combat_service_.get_all_ship_ptrs();
    for (auto ship : ships) {
        if (ship) result.push_back(ship_dto_mapper_manager_.create_ship_dto(ship));
    }
    return result;
}

std::vector<ShipDTO> Presenter::get_cargo_ships() const {
    std::vector<ShipDTO> result;
    auto ships = cargo_service_.get_cargo_ships();
    for (auto ship : ships) {
        if (ship) result.push_back(ship_dto_mapper_manager_.create_ship_dto(ship));
    }
    return result;
}

std::vector<ShipDTO> Presenter::get_attack_ships() const {
    std::vector<ShipDTO> result;
    auto ships = combat_service_.get_attack_ships();
    for (auto ship : ships) {
        if (ship) result.push_back(ship_dto_mapper_manager_.create_ship_dto(ship));
    }
    return result;
}

size_t Presenter::count_convoy_ships() const {
    return movement_service_.count_convoy_ships();
}

size_t Presenter::count_alive_convoy_ships() const {
    return combat_service_.get_convoy_alive_count();
}

std::vector<ShipDTO> Presenter::get_pirate_ships() const {
    std::vector<ShipDTO> result;
    auto ships = combat_service_.get_all_pirate_ship_ptrs();
    for (auto ship : ships) {
        if (ship) result.push_back(ship_dto_mapper_manager_.create_ship_dto(ship));
    }
    return result;
}

size_t Presenter::count_alive_pirate_ships() const {
    return combat_service_.get_pirates_alive_count();
}

ShipDTO Presenter::get_ship_by_id(std::string& ship_id) const {
    return ship_dto_mapper_manager_.create_ship_dto(combat_service_.get_ship_ptr(ship_id));
}

std::vector<PirateBaseDTO> Presenter::get_pirate_bases() const {
    std::vector<PirateBaseDTO> result;
    auto pirate_bases = pirate_spawn_service_.get_pirate_bases();
    for (const auto& base : pirate_bases) {
        result.push_back(pirate_base_dto_mapper_.transform(base));
    }
    return result;
}

void Presenter::move_convoy(double dt) {
    movement_service_.update(dt);
    pirate_spawn_service_.update(movement_service_.get_convoy_center());
}

void Presenter::start_convoy() {
    movement_service_.start_movement();
}

void Presenter::stop_convoy() {
    movement_service_.stop_movement();
}

void Presenter::move_pirates(double dt) {
    movement_service_.update_pirates(dt);
}

void Presenter::start_pirates() {
    movement_service_.start_pirate_movement();
}

void Presenter::stop_pirates() {
    movement_service_.stop_pirate_movement();
}

void Presenter::auto_combat_sequential() {
    combat_service_.auto_attack_all_sequential();
}

void Presenter::auto_combat_parallel() {
    combat_service_.auto_attack_all_parallel();
}

int Presenter::has_activated_base() const {
    for (size_t i = 0; i < combat_service_.get_pirate_bases_count(); ++i) {
        if (combat_service_.is_base_activated(i) && !combat_service_.is_base_defeated(i)) {
            return i;
        }
    }
    return -1;
}

void Presenter::update_base_status(size_t index) {
    auto pirate_bases = pirate_spawn_service_.get_pirate_bases();
    pirate_spawn_service_.update_base_status(pirate_bases[index]);
}

bool Presenter::has_reached_destination() const {
    return movement_service_.has_reached_base_B();
}

bool Presenter::mission_completed() const {
    if (get_current_cargo() >= cargo_service_.get_required_cargo()) return true;
    return false;
}

double Presenter::get_convoy_speed() const {
    return movement_service_.get_convoy_speed();
}

Vector Presenter::get_convoy_center() const {
    return movement_service_.get_convoy_center();
}

double Presenter::get_distanse_to_destination() const {
    return movement_service_.get_distance_to_base_B();
}

double Presenter::get_min_weapon_cost() const {
    return weapon_catalog_.get_min_cost();
}

void Presenter::set_convoy_strategy(const std::string& strategy) {
    combat_service_.set_convoy_strategy(strategy);
}

void Presenter::set_pirate_strategy(const std::string& strategy) {
    combat_service_.set_pirate_strategy(strategy);
}

std::string Presenter::convoy_info() const {
    return state_service_.convoy_info();
}

std::string Presenter::pirate_info() const {
    return state_service_.pirate_info();
}

void Presenter::save_game(const std::string& path) {
    state_service_.save(path);
}

void Presenter::load_game(const std::string& path) {
    state_service_.load(path);
}
#include "CombatService.hpp"
#include "../../visitor/weapon/ShootingVisitor.hpp"
#include "../../visitor/cargo/CargoInfoVisitor.hpp"
#include "../../visitor/cargo/CargoRemovalVisitor.hpp"

std::vector<IShip*> CombatService::get_convoy_ships_safe() const {
    return convoy_repo_.get_alive_ships();
}

std::vector<IShip*> CombatService::get_pirate_ships_safe() const {
    return pirate_repo_.get_alive_ships();
}

bool CombatService::execute_attack(IShip* attacker, IShip* target) {
    if (!attacker || !target) return false;
    if (!attacker->is_alive() || !target->is_alive()) return false;
    
    std::optional<PlaceForWeapon> place = PlaceForWeapon::bow;
    if (convoy_strategy_ && attacker->is_convoy()) place = convoy_strategy_->select_weapon_place(attacker, target);
    else if (pirate_strategy_ && !attacker->is_convoy()) place = pirate_strategy_->select_weapon_place(attacker, target);
    
    if (place.has_value()) {
        ShootingVisitor shooting_visitor(place.value(), target, damage_service_);
        attacker->accept(&shooting_visitor);
        return shooting_visitor.shot_fired();
    }
    
    return false;
}

void CombatService::process_convoy_attack_range(size_t start, size_t end, const std::vector<IShip*>& convoy_ships, const std::vector<IShip*>& pirate_ships) {    
    if (convoy_ships.empty() || pirate_ships.empty()) return;
    
    for (size_t i = start; i < end && i < convoy_ships.size(); ++i) {
        if (stop_threads_.load()) return;
        
        IShip* attacker = convoy_ships[i];
        if (!attacker || !attacker->is_alive() || attacker->get_health() <= 0.0) continue;
        
        IShip* target = convoy_strategy_->select_target(attacker, pirate_ships);
        if (!target) continue;
        
        execute_attack(attacker, target);
    }

    // std::cout << "Поток конвоя id: " << std::this_thread::get_id() << "\n";
}

void CombatService::process_pirate_attack_range(size_t start, size_t end, const std::vector<IShip*>& convoy_ships, const std::vector<IShip*>& pirate_ships) {
    if (convoy_ships.empty() || pirate_ships.empty()) return;
    
    for (size_t i = start; i < end && i < pirate_ships.size(); ++i) {
        if (stop_threads_.load()) return;
        
        IShip* attacker = pirate_ships[i];
        if (!attacker|| !attacker->is_alive() || attacker->get_health() <= 0.0) continue;
        
        IShip* target = pirate_strategy_->select_target(attacker, convoy_ships);
        if (!target || !target->is_alive() || target->get_health() <= 0.0) continue;

        double health_before = target->get_health();
        if (!execute_attack(attacker, target)) continue;
        double health_after = target->get_health();

        if (health_after < health_before) {
            CargoInfoVisitor info_visitor;
            target->accept(&info_visitor);
            double current_cargo = info_visitor.get_current_cargo();
            
            double damage_percent = (health_before - health_after) / health_before;
            double cargo_to_remove = current_cargo * damage_percent;
            
            if (cargo_to_remove > 0) {
                {
                    std::lock_guard<std::mutex> lock(mission_mutex_);
                    mission_.remove_cargo(cargo_to_remove);
                }

                CargoRemovalVisitor remove_visitor(cargo_to_remove);
                target->accept(&remove_visitor);
            }
        }
    }

    // std::cout << "Поток пиратов id: " << std::this_thread::get_id() << "\n";
}

void CombatService::process_convoy_attack() {
    auto convoy_ships = convoy_repo_.get_alive_ships();
    auto pirate_ships = pirate_repo_.get_alive_ships();
    
    if (convoy_ships.empty() || pirate_ships.empty()) return;
    
    for (auto attacker : convoy_ships) {
        if (!attacker->is_alive()) continue;
        IShip* target = convoy_strategy_->select_target(attacker, pirate_ships);
        if (!target) continue;
        execute_attack(attacker, target);
    }
}

void CombatService::process_pirate_attack() {
    auto convoy_ships = convoy_repo_.get_alive_ships();
    auto pirate_ships = pirate_repo_.get_alive_ships();
    
    if (convoy_ships.empty() || pirate_ships.empty()) return;
    
    for (auto attacker : pirate_ships) {
        if (!attacker->is_alive()) continue;
        IShip* target = pirate_strategy_->select_target(attacker, convoy_ships);
        if (!target) continue;

        double health_before = target->get_health();
        execute_attack(attacker, target);
        double health_after = target->get_health();

        CargoInfoVisitor info_visitor;
        double percent = health_after / health_before;
        target->accept(&info_visitor);
        double cargo_for_remove = info_visitor.get_current_cargo() * (1 - percent);
        mission_.remove_cargo(cargo_for_remove);
        CargoRemovalVisitor remove_visitor(cargo_for_remove);
        target->accept(&remove_visitor);
    }
}

CombatService::CombatService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo, DamageService& damage_service) :
    mission_(mission),
    convoy_repo_(convoy_repo),
    pirate_repo_(pirate_repo),
    damage_service_(damage_service),
    strategy_factory_(std::make_unique<AttackStrategyFactoryManager>()),
    convoy_strategy_(strategy_factory_->create_strategy("weakest")),
    pirate_strategy_(strategy_factory_->create_strategy("random")) {}

CombatService::~CombatService() {
    stop_threads_.store(true);
}

bool CombatService::set_convoy_strategy(const std::string& strategy_name) {
    auto strategy = strategy_factory_->create_strategy(strategy_name);
    if (!strategy) return false;
    
    convoy_strategy_ = std::move(strategy);
    return true;
}

bool CombatService::set_pirate_strategy(const std::string& strategy_name) {
    auto strategy = strategy_factory_->create_strategy(strategy_name);
    if (!strategy) return false;
    
    pirate_strategy_ = std::move(strategy);
    return true;
}

std::vector<std::string> CombatService::get_available_strategies() const {
    return strategy_factory_->get_available_strategies();
}

std::string CombatService::get_current_convoy_strategy() const {
    return convoy_strategy_ ? convoy_strategy_->get_name() : "none";
}

std::string CombatService::get_current_pirate_strategy() const {
    return pirate_strategy_ ? pirate_strategy_->get_name() : "none";
}

void CombatService::auto_attack_all_sequential() {
    if (get_convoy_alive_count() == 0 || get_pirates_alive_count() == 0) return;

    process_convoy_attack();
    process_pirate_attack();
}

void CombatService::auto_attack_all_parallel() {
    if (get_convoy_alive_count() == 0 || get_pirates_alive_count() == 0) return;

    stop_threads_.store(false);
    
    auto convoy_ships = get_convoy_ships_safe();
    auto pirate_ships = get_pirate_ships_safe();

    std::vector<std::jthread> threads;
    
    size_t convoy_chunk_size = (convoy_ships.size() + 9) / 10;
    for (size_t i = 0; i < 10; ++i) {
        size_t start_index = i * convoy_chunk_size;
        size_t end_index = std::min(start_index + convoy_chunk_size, convoy_ships.size());

        if (start_index >= convoy_ships.size()) break;

        threads.emplace_back(
            [this, start_index, end_index, &convoy_ships, &pirate_ships](){
                this->process_convoy_attack_range(start_index, end_index, convoy_ships, pirate_ships);
            }
        );
    }

    size_t pirate_chunk_size = (pirate_ships.size() + 9) / 10;
    for (size_t i = 0; i < 10; ++i) {
        size_t start_index = i * pirate_chunk_size;
        size_t end_index = std::min(start_index + pirate_chunk_size, pirate_ships.size());

        if (start_index >= pirate_ships.size()) break;

        threads.emplace_back(
            [this, start_index, end_index, &convoy_ships, &pirate_ships](){
                this->process_pirate_attack_range(start_index, end_index, convoy_ships, pirate_ships);
            }
        );
    }
}

size_t CombatService::get_convoy_alive_count() const {
    return convoy_repo_.count_alive();
}

size_t CombatService::get_pirates_alive_count() const {
    return pirate_repo_.count_alive();
}

size_t CombatService::get_pirate_bases_count() const {
    return mission_.get_pirate_bases().size();
}

bool CombatService::is_base_activated(size_t index) const {
    PirateBase pirate_base = mission_.get_pirate_base(index);
    return pirate_base.is_activated;
}

bool CombatService::is_base_defeated(size_t index) const {
    PirateBase pirate_base = mission_.get_pirate_base(index);
    return pirate_base.is_defeated;
}

std::vector<IShip*> CombatService::get_all_ship_ptrs() const {
    return convoy_repo_.get_all_ship_ptrs();
}

IShip* CombatService::get_ship_ptr(const std::string& ship_id) const {
    return convoy_repo_.get_ship_ptr(ship_id);
}

std::vector<IShip*> CombatService::get_attack_ships() const {
    return convoy_repo_.get_attack_ships();
}

std::vector<IShip*> CombatService::get_all_pirate_ship_ptrs() const {
    return pirate_repo_.get_all_ship_ptrs();
}
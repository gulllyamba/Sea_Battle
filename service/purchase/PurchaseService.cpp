#include "PurchaseService.hpp"
#include "../../visitor/weapon/WeaponInstallationVisitor.hpp"
#include "../../visitor/weapon/WeaponRemovalVisitor.hpp"
#include "../../visitor/weapon/ShipSellVisitor.hpp"
#include "../../visitor/place/HasPlaceWeaponVisitor.hpp"

bool PurchaseService::spend_money(double amount) {
    return mission_.remove_budget(amount);
}

bool PurchaseService::add_money(double amount) {
    return mission_.add_budget(amount);
}

IShip* PurchaseService::find_ship(const std::string& ship_id) const {
    IShip* ship = convoy_repo_.get_ship_ptr(ship_id);
    if (!ship) ship = pirate_repo_.get_ship_ptr(ship_id);
    return ship;
}

PurchaseService::PurchaseService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo, ShipCatalog& ship_catalog, WeaponCatalog& weapon_catalog) :
mission_(mission),
convoy_repo_(convoy_repo),
pirate_repo_(pirate_repo),
ship_catalog_(ship_catalog),
weapon_catalog_(weapon_catalog) {}

bool PurchaseService::buy_ship(const std::string& template_id, bool is_convoy, const Vector& position) {
    const ShipTemplate* temp = ship_catalog_.find_template_by_id(template_id);
    if (!temp) return false;
    if (!can_spend(temp->cost)) return false;
    std::unique_ptr<IShip> ship;
    try {
        ship = ship_catalog_.create_ship(template_id, is_convoy, position);
    }
    catch (const std::exception& e) {
        return false;
    }
    
    if (!ship) return false;
    if (!spend_money(temp->cost)) return false;

    try {
        if (is_convoy) convoy_repo_.create(std::move(ship));
        else pirate_repo_.create(std::move(ship));
    }
    catch (const std::exception& e) {
        add_money(temp->cost);
        return false;
    }
    
    return true;
}

double PurchaseService::sell_ship(const std::string& ship_id) {
    IShip* ship = find_ship(ship_id);
    if (!ship) return 0.0;
    return sell_ship(ship);
}

double PurchaseService::sell_ship(IShip* ship) {
    if (!ship) return 0.0;
    if (!ship->is_alive()) return 0.0;
    
    ShipSellVisitor visitor;
    ship->accept(&visitor);

    double refund = visitor.get_total_refund();
    if (refund <= 0) return 0.0;
    
    if (!add_money(refund)) return 0.0;
    
    try{
        if (ship->is_convoy()) convoy_repo_.remove(ship->get_ID());
        else pirate_repo_.remove(ship->get_ID());
    }
    catch (const std::exception& e) {
        spend_money(refund);
        return 0.0;
    }
    
    return refund;
}

std::unique_ptr<IWeapon> PurchaseService::buy_weapon(const std::string& template_id) {
    const WeaponTemplate* temp = weapon_catalog_.find_template_by_id(template_id);
    if (!temp) return nullptr;
    if (!can_spend(temp->cost)) return nullptr;
    
    std::unique_ptr<IWeapon> weapon;
    try {
        weapon = weapon_catalog_.create_weapon(template_id);
    }
    catch (const std::exception& e) {
        return nullptr;
    }
    
    if (!weapon) return nullptr;
    if (!spend_money(temp->cost)) return nullptr;
    
    return weapon;
}

bool PurchaseService::install_weapon(const std::string& ship_id, PlaceForWeapon place, const std::string& weapon_template_id) {
    const WeaponTemplate* temp = weapon_catalog_.find_template_by_id(weapon_template_id);
    if (!temp) return false;

    std::unique_ptr<IWeapon> weapon;
    try {
        weapon = weapon_catalog_.create_weapon(weapon_template_id);
    }
    catch (const std::exception& e) {
        return false;
    }
    if (!weapon) return false;

    IShip* ship = find_ship(ship_id);
    if (!ship) return false;
    
    WeaponInstallationVisitor visitor(place, std::move(weapon));
    ship->accept(&visitor);
    if (visitor.is_installed()) return true;
    else return false;
}

bool PurchaseService::install_weapon(const std::string& ship_id, PlaceForWeapon place, std::unique_ptr<IWeapon> weapon) {
    if (!weapon) return false;

    IShip* ship = find_ship(ship_id);
    if (!ship) return false;
    
    WeaponInstallationVisitor visitor(place, std::move(weapon));
    ship->accept(&visitor);
    
    if (visitor.is_installed()) return true;
    else return false;
}

double PurchaseService::sell_weapon(const std::string& ship_id, PlaceForWeapon place) {
    IShip* ship = find_ship(ship_id);
    if (!ship) return 0.0;
    
    WeaponRemovalVisitor visitor(place);
    ship->accept(&visitor);   
    if (visitor.is_removed()) {
        double refund = visitor.get_weapon_cost();
        if (add_money(refund)) return refund;
    }
    return 0.0;
}

std::vector<ShipTemplate> PurchaseService::get_available_ships() const {
    return ship_catalog_.get_all_templates();
}

std::vector<WeaponTemplate> PurchaseService::get_available_weapons() const {
    return weapon_catalog_.get_all_templates();
}

std::vector<ShipTemplate> PurchaseService::get_affordable_ships() const {
    double budget = get_current_budget();
    std::vector<ShipTemplate> all_ships = get_available_ships();
    std::vector<ShipTemplate> affordable;
    
    for (const auto& ship : all_ships) {
        if (ship.cost <= budget) affordable.push_back(ship);
    }
    return affordable;
}

std::vector<WeaponTemplate> PurchaseService::get_affordable_weapons() const {
    double budget = get_current_budget();
    std::vector<WeaponTemplate> all_weapons = get_available_weapons();
    std::vector<WeaponTemplate> affordable;
    
    for (const auto& weapon : all_weapons) {
        if (weapon.cost <= budget) affordable.push_back(weapon);
    }
    return affordable;
}

bool PurchaseService::can_spend(double amount) const {
    return mission_.can_spend(amount);
}

double PurchaseService::get_current_budget() const {
    return mission_.get_current_budget();
}

double PurchaseService::get_initial_budget() const {
    return mission_.get_total_budget();
}

bool PurchaseService::has_weapon_in_place(const std::string &ship_id, PlaceForWeapon place) const {
    IShip* ship = find_ship(ship_id);
    if (!ship) return false;

    HasPlaceWeaponVisitor visitor(place);
    ship->accept(&visitor);
    return visitor.has_weapon();
}

bool PurchaseService::has_free_place() const {
    std::vector<IShip*> attack_ships = convoy_repo_.get_attack_ships();
    HasPlaceWeaponVisitor visitor_bow(PlaceForWeapon::bow);
    HasPlaceWeaponVisitor visitor_port(PlaceForWeapon::port);
    HasPlaceWeaponVisitor visitor_starboard(PlaceForWeapon::starboard);
    HasPlaceWeaponVisitor visitor_stern(PlaceForWeapon::stern);
    for (auto ship : attack_ships) {
        ship->accept(&visitor_bow);
        ship->accept(&visitor_port);
        ship->accept(&visitor_starboard);
        ship->accept(&visitor_stern);
        if (!visitor_bow.has_weapon() || !visitor_port.has_weapon() || !visitor_starboard.has_weapon() || !visitor_stern.has_weapon())
            return true;
    }
    return false;
}

bool PurchaseService::has_occupied_place() const {
    std::vector<IShip*> attack_ships = convoy_repo_.get_attack_ships();
    HasPlaceWeaponVisitor visitor_bow(PlaceForWeapon::bow);
    HasPlaceWeaponVisitor visitor_port(PlaceForWeapon::port);
    HasPlaceWeaponVisitor visitor_starboard(PlaceForWeapon::starboard);
    HasPlaceWeaponVisitor visitor_stern(PlaceForWeapon::stern);
    for (auto ship : attack_ships) {
        ship->accept(&visitor_bow);
        ship->accept(&visitor_port);
        ship->accept(&visitor_starboard);
        ship->accept(&visitor_stern);
        if (visitor_bow.has_weapon() || visitor_port.has_weapon() || visitor_starboard.has_weapon() || visitor_stern.has_weapon())
            return true;
    }
    return false;
}

bool PurchaseService::validate_ship_purchase(const std::string& template_id) const {
    const ShipTemplate* temp = ship_catalog_.find_template_by_id(template_id);
    if (!temp) return false;
    
    return can_spend(temp->cost);
}

bool PurchaseService::validate_weapon_purchase(const std::string& template_id) const {
    const WeaponTemplate* temp = weapon_catalog_.find_template_by_id(template_id);
    if (!temp) return false;
    
    return can_spend(temp->cost);
}
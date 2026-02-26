#include "PirateSpawnService.hpp"
#include "../../visitor/weapon/WeaponInstallationVisitor.hpp"
#include <stdexcept>
#include <chrono>

double PirateSpawnService::calculate_distance(const Vector& a, const Vector& b) const {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

Vector PirateSpawnService::generate_random_offset() {
    double offset_x = position_offset_dist_(rng_);
    double offset_y = position_offset_dist_(rng_);
    return Vector(offset_x, offset_y);
}

std::unique_ptr<IShip> PirateSpawnService::create_pirate_ship(const Vector& position) {
    auto ship = ship_catalog_.create_ship("guard_medium", false, position);
    if (!ship) return nullptr;
    ship->set_name("Пират");
    
    std::unique_ptr<IWeapon> weapon;
    switch (level_) {
        case Level::EAZY : {
            weapon = weapon_catalog_.create_weapon("gun_light");
            break;
        }
        case Level::MEDIUM : {
            weapon = weapon_catalog_.create_weapon("gun_medium");
        }
        case Level::HARD : {
            weapon = weapon_catalog_.create_weapon("gun_heavy");
        }
        default:
            break;
    }

    if (weapon) {
        WeaponInstallationVisitor visitor(PlaceForWeapon::bow, std::move(weapon));
        ship->accept(&visitor);
    }

    return ship;
}

void PirateSpawnService::spawn_pirates_at_base(PirateBase& base) {
    if (base.is_activated) return;
    
    base.is_activated = true;
    base.spawned_pirate_ids.clear();
    
    for (size_t i = 0; i < base.ship_count; ++i) {
        Vector offset = generate_random_offset();
        Vector ship_position = Vector(base.position.x + offset.x, base.position.y + offset.y);
        
        auto pirate_ship = create_pirate_ship(ship_position);
        if (pirate_ship) {
            base.spawned_pirate_ids.push_back(pirate_ship->get_ID());
            pirate_repo_.create(std::move(pirate_ship));
            ++total_pirates_spawned_;
        }
    }
}

void PirateSpawnService::update_base_status(PirateBase& base) {
    if (!base.is_activated || base.is_defeated) return;

    size_t active_pirates = pirate_repo_.count_alive();
    if (active_pirates == 0) base.is_defeated = true;
}

PirateSpawnService::PirateSpawnService(Mission& mission, PirateRepository& pirate_repo, ShipCatalog& ship_catalog, WeaponCatalog& weapon_catalog, Level level) :
mission_(mission),
pirate_repo_(pirate_repo),
ship_catalog_(ship_catalog),
weapon_catalog_(weapon_catalog),
level_(level),
rng_(std::chrono::steady_clock::now().time_since_epoch().count()),
position_offset_dist_(-mission_.get_base_size(), mission_.get_base_size()),
total_pirates_spawned_(0) {}

void PirateSpawnService::set_seed(size_t seed) {
    rng_.seed(seed);
}

void PirateSpawnService::update(const Vector& convoy_position) {
    for (size_t i = 0; i < mission_.count_pirate_bases(); ++i) {
        PirateBase& base = mission_.get_pirate_base(i);
        if (!base.is_activated && !base.is_defeated) {
            double distance = calculate_distance(convoy_position, base.position);
            if (distance <= base.trigger_distance) {
                spawn_pirates_at_base(base);
            }
        }
        update_base_status(base);
    }
}

void PirateSpawnService::clear_bases() {
    mission_.clear_pirate_bases();
    total_pirates_spawned_ = 0;
}

const std::vector<PirateBase>& PirateSpawnService::get_pirate_bases() const {
    return mission_.get_pirate_bases();
}

size_t PirateSpawnService::get_active_base_count() const {
    return mission_.count_active_pirate_bases();
}

size_t PirateSpawnService::get_defeated_base_count() const {
    size_t result = 0;
    std::vector<PirateBase> pbases = mission_.get_pirate_bases();
    for (const auto& pb : pbases) {
        if (pb.is_defeated) ++result;
    }
    return result;
}

size_t PirateSpawnService::get_total_pirates_spawned() const {
    return total_pirates_spawned_;
}

bool PirateSpawnService::are_all_bases_defeated() const {
    return get_defeated_base_count() == mission_.count_pirate_bases();
}

void PirateSpawnService::set_position_offset_range(double min_offset, double max_offset) {
    if (min_offset > max_offset) throw std::invalid_argument("Некорректный диапазон смещения");
    position_offset_dist_ = std::uniform_real_distribution<double>(min_offset, max_offset);
}
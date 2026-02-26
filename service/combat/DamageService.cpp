#include "DamageService.hpp"
#include <chrono>

thread_local std::mt19937 local_rng(std::chrono::steady_clock::now().time_since_epoch().count());

double DamageService::get_random_double(double min, double max) {
    return dist_(local_rng);
}

double DamageService::calculate_damage(const IWeapon* weapon, const IShip* target, double distance) {
    if (!weapon || !target || !target->is_alive()) return 0.0;
    if (distance > weapon->get_range()) return 0.0;
    if (!check_hit(weapon->get_accuracy(), distance, weapon->get_range())) return 0.0;
    
    double base_damage = weapon->get_damage();
    double final_damage = calculate_effective_damage(base_damage, distance, weapon->get_range());

    if (is_critical_hit()) final_damage *= 1.5;

    final_damage = std::round(final_damage * 10.0) / 10.0;

    return final_damage;
}

bool DamageService::check_hit(double base_accuracy, double distance, double max_range) {
    if (max_range <= 0 || distance > max_range) return false;
    double hit_chance = base_accuracy;
    
    double distance_penalty = (distance / max_range) * 0.2;
    hit_chance -= distance_penalty;
    hit_chance = std::max(0.1, hit_chance);
    
    double roll = get_random_double(0.0, 1.0);
    return roll <= hit_chance;
}

double DamageService::calculate_effective_damage(double base_damage, double distance, double max_range) {
    if (max_range <= 0) return base_damage;
    double distance_factor = 1.0 - (distance / max_range) * 0.2;
    distance_factor = std::max(0.5, distance_factor);
    return base_damage * distance_factor;
}

bool DamageService::is_critical_hit(double critical_chance) {
    if (critical_chance <= 0) return false;
    if (critical_chance >= 1.0) return true;
    return critical_chance >= get_random_double(0.0, 1.0);
}
#include "DefaultShip.hpp"
#include <stdexcept>
#include <cmath>

void DefaultShip::validate_parameters() const {
    if (max_speed_ < 0.0) throw std::invalid_argument("Max speed must be positive");
    if (max_health_ < 0.0) throw std::invalid_argument("Max health must be positive");
    if (cost_ < 0.0) throw std::invalid_argument("Cost cannot be negative");
}

DefaultShip::DefaultShip(
    const std::string& name,
    const Military& captain,
    double max_speed,
    double max_health,
    double cost,
    const std::string& id,
    bool is_convoy,
    const Vector& position
) : name_(name),
    captain_(captain),
    max_speed_(max_speed),
    current_speed_(0.0),
    cost_(cost),   
    id_(id),
    is_convoy_(is_convoy),
    position_(position),
    max_health_(max_health),
    current_health_(max_health),
    is_alive_(true) {
    validate_parameters();
}

Vector DefaultShip::get_position() const {
    return position_;
}
void DefaultShip::set_position(const Vector& position) {
    position_ = position;
}
double DefaultShip::get_speed() const {
    return current_speed_;
}
void DefaultShip::set_speed(double speed) {
    if (speed <= 0.0) current_speed_ = 0.0;
    else if (speed < max_speed_) current_speed_ = speed;
    else current_speed_ = max_speed_;
}

double DefaultShip::get_distance_to(const Vector& point) const {
    double dx = point.x - position_.x;
    double dy = point.y - position_.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool DefaultShip::is_at_position(const Vector& pos, double tolerance) const {
    return get_distance_to(pos) <= tolerance;
}

double DefaultShip::get_health() const {
    return current_health_.load(std::memory_order_acquire);
}
double DefaultShip::get_max_health() const {
    return max_health_;
}
bool DefaultShip::is_alive() const {
    return is_alive_.load(std::memory_order_acquire);
}
void DefaultShip::set_health(double health) {
    if (health < 0.0) health = 0.0;
    if (health > max_health_) health = max_health_;
    
    current_health_.store(health, std::memory_order_release);
    
    if (health <= 0.0 || std::abs(health) < 1e-9) {
        is_alive_.store(false, std::memory_order_release);
        current_speed_ = 0.0;
    }
    else is_alive_.store(true, std::memory_order_release);
}

void DefaultShip::set_max_health(double max_health) {
    if (max_health < 0.0) throw std::invalid_argument("Max health must be positive");
    max_health_ = max_health;
    if (current_health_ > max_health_) current_health_ = max_health_;
}

void DefaultShip::take_damage(double damage) {
    if (!is_alive_.load(std::memory_order_acquire) || damage <= 0.0) return;
    
    double current = current_health_.load(std::memory_order_relaxed);
    double desired;
    
    do {
        if (current <= 0.0) return;
        desired = current - damage;
        if (desired < 0.0) desired = 0.0;
        
    } while (!current_health_.compare_exchange_weak(current, desired, std::memory_order_release, std::memory_order_relaxed));
    
    if (desired == 0.0) {
        bool expected = true;
        if (is_alive_.compare_exchange_strong(expected, false, std::memory_order_release, std::memory_order_relaxed)) {
            current_speed_ = 0.0;
        }
    }
}

std::string DefaultShip::get_name() const {
    return name_;
}
Military DefaultShip::get_captain() const {
    return captain_;
}
std::string DefaultShip::get_ID() const {
    return id_;
}
double DefaultShip::get_max_speed() const {
    return max_speed_;
}
double DefaultShip::get_cost() const {
    return cost_;
}

void DefaultShip::set_name(const std::string& name) {
    name_ = name;
}
void DefaultShip::set_captain(const Military& captain) {
    captain_ = captain;
}
void DefaultShip::set_max_speed(double max_speed) {
    if (max_speed < 0.0) throw std::invalid_argument("Max speed must be positive");
    max_speed_ = max_speed;
    if (current_speed_ > max_speed_) current_speed_ = max_speed_;
}
void DefaultShip::set_cost(double cost) {
    cost_ = cost;
}
void DefaultShip::set_ID(const std::string& id) {
    id_ = id;
}

bool DefaultShip::is_convoy() const {
    return is_convoy_;
}
void DefaultShip::set_convoy(bool is_convoy) {
    is_convoy_ = is_convoy;
}
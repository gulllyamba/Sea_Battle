#include "DefaultCargo.hpp"
#include <stdexcept>

DefaultCargo::DefaultCargo(double max_cargo, double speed_reduction_factor) : max_cargo_(max_cargo), current_cargo_(0.0), speed_reduction_factor_(speed_reduction_factor) {
    if (max_cargo_ < 0.0) throw std::invalid_argument("Max cargo cannot be negative");
    if (speed_reduction_factor_ < 0.0 || speed_reduction_factor_ > 1.0) throw std::invalid_argument("Speed reduction factor must be between 0 and 1");
}

double DefaultCargo::get_max_cargo() const {
    return max_cargo_;
}
double DefaultCargo::get_cargo() const {
    return current_cargo_.load();
}
void DefaultCargo::set_max_cargo(double max_cargo) {
    if (max_cargo < 0.0) throw std::invalid_argument("Max cargo cannot be negative");
    max_cargo_ = max_cargo;
    
    double current = current_cargo_.load(std::memory_order_relaxed);
    if (current > max_cargo_) current_cargo_.store(max_cargo_, std::memory_order_release);
}
void DefaultCargo::set_cargo(double cargo) {
    if (cargo < 0.0) throw std::invalid_argument("Cargo cannot be negative");
    if (cargo > max_cargo_) throw std::invalid_argument("Cargo cannot exceed max cargo");
    current_cargo_.store(cargo, std::memory_order_release);
}
void DefaultCargo::add_cargo(double amount) {
    if (amount <= 0.0) return;
    double current = current_cargo_.load(std::memory_order_relaxed);
    double desired;
    
    do {
        if (current + amount > max_cargo_) throw std::invalid_argument("Cannot add cargo: would exceed max capacity");
        desired = current + amount;
    } while (!current_cargo_.compare_exchange_weak(current, desired, std::memory_order_release, std::memory_order_relaxed));
}
void DefaultCargo::remove_cargo(double amount) {
    if (amount <= 0.0) return;
    double current = current_cargo_.load(std::memory_order_relaxed);
    double desired;
    
    do {
        if (amount > current) desired = 0.0;
        else desired = current - amount;
    } while (!current_cargo_.compare_exchange_weak(current, desired, std::memory_order_release, std::memory_order_relaxed));
}
double DefaultCargo::get_speed_reduction_factor() const {
    return speed_reduction_factor_;
}
void DefaultCargo::set_speed_reduction_factor(double factor) {
    speed_reduction_factor_ = factor;
}
double DefaultCargo::get_max_speed_with_current_cargo() const {
    double current = current_cargo_.load(std::memory_order_acquire);
    double reduction = (current / max_cargo_) * speed_reduction_factor_;
    return std::max(1.0 - reduction, 0.1);
}

bool DefaultCargo::can_add_cargo(double amount) const {
    if (amount <= 0.0) return false;
    double current = current_cargo_.load(std::memory_order_acquire);
    return (current + amount) <= max_cargo_;
}

bool DefaultCargo::can_remove_cargo(double amount) const {
    if (amount <= 0.0) return false;
    double current = current_cargo_.load(std::memory_order_acquire);
    return amount <= current;
}
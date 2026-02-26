#include "Mission.hpp"
#include <stdexcept>

Mission::Mission(
    const std::string& id,
    const Military& commander,
    double total_budget,
    double total_cargo_,
    double required_percentage,
    size_t max_convoy_ships,
    size_t max_pirate_ships,
    const Vector& base_a,
    const Vector& base_b,
    double base_size,
    const std::vector<PirateBase>& pirate_bases) :
    id_(id),
    commander_(commander),
    total_budget_(total_budget),
    current_budget_(total_budget),
    total_cargo_(total_cargo_),
    current_cargo_(0.0),
    required_cargo_percentage_(required_percentage),
    max_convoy_ships_(max_convoy_ships),
    max_pirate_ships_(max_pirate_ships),
    base_a_(base_a),
    base_b_(base_b),
    base_size_(base_size),
    pirate_bases_(pirate_bases),
    is_completed_(false),
    is_successful_(false) {
        if (total_budget_ < 0) throw std::invalid_argument("Budget cannot be negative");
        if (total_cargo_ < 0) throw std::invalid_argument("Cargo weight cannot be negative");
        if (required_percentage < 0 || required_percentage > 100) throw std::invalid_argument("Required percentage must be between 0 and 100");
}

std::string Mission::get_id() const {
    return id_;
}

Military Mission::get_commander() const {
    return commander_;
}

double Mission::get_total_budget() const {
    return total_budget_;
}

double Mission::get_current_budget() const {
    return current_budget_;
}

double Mission::get_spent_budget() const {
    return total_budget_ - current_budget_;
}

bool Mission::can_spend(double amount) const { 
    return amount > 0 && get_current_budget() >= amount; 
}

bool Mission::add_budget(double amount) {
    current_budget_ += amount;
    return true;
}

bool Mission::remove_budget(double amount) {
    if (!can_spend(amount)) return false;
    current_budget_ -= amount;
    return true;
}

double Mission::get_total_cargo() const {
    return total_cargo_;
}

double Mission::get_current_cargo() const {
    return current_cargo_;
}

double Mission::get_required_cargo() const { 
    return total_cargo_ * (required_cargo_percentage_ / 100.0); 
}

bool Mission::add_cargo(double amount) {
    if (amount > 0) {
        current_cargo_ += amount;
        return true;
    }
    return false;
}

bool Mission::remove_cargo(double amount) {
    if (amount > 0) {
        if (current_cargo_ >= amount) current_cargo_ -= amount;
        else current_cargo_ = 0.0;
        return true;
    }
    return false;
}

size_t Mission::get_max_convoy_ships() const {
    return max_convoy_ships_;
}
size_t Mission::get_max_pirate_ships() const {
    return max_pirate_ships_;
}

Vector Mission::get_base_a() const {
    return base_a_;
}

Vector Mission::get_base_b() const {
    return base_b_;
}

double Mission::get_base_size() const {
    return base_size_;
}

const std::vector<PirateBase>& Mission::get_pirate_bases() const { 
    return pirate_bases_; 
}

size_t Mission::count_pirate_bases() const {
    return pirate_bases_.size();
}

PirateBase& Mission::get_pirate_base(size_t index) {
    return pirate_bases_[index];
}

const PirateBase& Mission::get_pirate_base(size_t index) const {
    return pirate_bases_[index];
}

void Mission::clear_pirate_bases() {
    pirate_bases_.clear();
}

size_t Mission::count_active_pirate_bases() const {
    size_t cnt = 0;
    for (const auto& base : pirate_bases_) {
        if (base.is_activated) ++cnt;
    }
    return cnt;
}

bool Mission::is_completed() const {
    return is_completed_;
}

bool Mission::is_successful() const {
    return is_successful_;
}

bool Mission::is_in_progress() const {
    return !is_completed_;
}

double Mission::get_completion_percentage() const {
    if (total_cargo_ <= 0.0) return 0.0;
    return (current_cargo_ / total_cargo_) * 100.0;
}

bool Mission::is_goal_achieved() const {
    return current_cargo_ >= get_required_cargo();
}

void Mission::set_current_budget(double budget) {
    current_budget_ = budget;
}

void Mission::set_current_cargo(double cargo) {
    current_cargo_ = cargo;
}

void Mission::set_is_completed(bool is_completed) {
    is_completed_ = is_completed;
}

void Mission::set_is_successful(bool is_successful) {
    is_successful_ = is_successful;
}

Mission& Mission::operator=(const Mission& other) {
    id_ = other.id_;
    commander_ = other.commander_;
    total_budget_ = other.total_budget_;
    current_budget_ = other.current_budget_;
    total_cargo_ = other.total_cargo_;
    current_cargo_ = other.current_cargo_;
    required_cargo_percentage_ = other.required_cargo_percentage_;
    max_convoy_ships_ = other.max_convoy_ships_;
    max_pirate_ships_ = other.max_pirate_ships_;
    base_a_ = other.base_a_;
    base_b_ = other.base_b_;
    base_size_ = other.base_size_;
    pirate_bases_ = other.pirate_bases_;
    is_completed_ = other.is_completed_;
    is_successful_ = other.is_successful_;
    return *this;
}
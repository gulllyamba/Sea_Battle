#include "MovementService.hpp"
#include <cmath>

double MovementService::get_distance_between(const Vector& from, const Vector& to) const {
    double dx = from.x - to.x;
    double dy = from.y - to.y;
    return std::sqrt(dx * dx + dy * dy);
}

void MovementService::move_ship(IShip* ship, const Vector& direction, double speed, double delta_time) {
    if (!ship || !ship->is_alive() || speed <= 0 || delta_time <= 0) return;
    Vector current_pos = ship->get_position();
    Vector new_pos = Vector(current_pos.x + direction.x * speed * delta_time, current_pos.y + direction.y * speed * delta_time);
    ship->set_position(new_pos);
}

Vector MovementService::calculate_direction(const Vector& start, const Vector& end) const {    
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double length = std::sqrt(dx * dx + dy * dy);
    if (length == 0) return Vector(0, 0);
    return Vector(dx / length, dy / length);
}

void MovementService::update_convoy(double delta_time) {
    auto ships = convoy_repo_.get_alive_ships();
    if (ships.empty()) return;
    Vector direction = calculate_direction(mission_.get_base_a(), mission_.get_base_b());
    for (auto ship : ships) {
        move_ship(ship, direction, convoy_speed_, delta_time);
    }
}

void MovementService::update_pirates(double delta_time) {
    auto pirates = pirate_repo_.get_alive_ships();
    if (pirates.empty()) return;
    Vector convoy_center = get_convoy_center();
    for (auto pirate : pirates) {
        while (get_distance_between(pirate->get_position(), get_convoy_center()) > mission_.get_base_size()) {
            move_ship(pirate, calculate_direction(pirate->get_position(), convoy_center), pirate->get_speed(), delta_time);
        }
    }
}

size_t MovementService::count_convoy_ships() const {
    return convoy_repo_.count();
}

size_t MovementService::count_pirate_ships() const {
    return pirate_repo_.count();
}

double MovementService::calculate_convoy_speed() const {
    auto ships = convoy_repo_.get_alive_ships();
    if (ships.empty()) return 0.0;
    double min_speed = std::numeric_limits<double>::max();
    for (auto ship : ships) {
        double current_speed = ship->get_speed();
        min_speed = std::min(min_speed, current_speed);
    }
    return (min_speed == std::numeric_limits<double>::max()) ? 0.0 : min_speed;
}

Vector MovementService::get_convoy_target_position() const {
    return mission_.get_base_b();
}

MovementService::MovementService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo) : mission_(mission), convoy_repo_(convoy_repo), pirate_repo_(pirate_repo) {}

void MovementService::update(double delta_time) {
    if (!is_moving_ || delta_time <= 0) return;
    update_convoy(delta_time);
    convoy_speed_ = calculate_convoy_speed();
}

void MovementService::start_movement() {
    if (is_moving_) return;
    is_moving_ = true;
    convoy_speed_ = calculate_convoy_speed();
    auto ships = convoy_repo_.get_alive_ships();
    for (auto ship : ships) {
        ship->set_speed(ship->get_max_speed());
    }
}
void MovementService::start_pirate_movement() {
    auto pirates = pirate_repo_.get_alive_ships();
    for (auto pirate : pirates) {
        pirate->set_speed(pirate->get_max_speed());
    }
}

void MovementService::stop_movement() {
    if (!is_moving_) return;
    is_moving_ = false;
    auto ships = convoy_repo_.get_alive_ships();
    for (auto ship : ships) {
        ship->set_speed(0.0);
    }
    convoy_speed_ = 0.0;
}
void MovementService::stop_pirate_movement() {
    auto pirates = pirate_repo_.get_alive_ships();
    for (auto pirate : pirates) {
        pirate->set_speed(0.0);
    }
}

bool MovementService::is_moving() const {
    return is_moving_;
}

double MovementService::get_convoy_speed() const {
    return convoy_speed_;
}

double MovementService::get_distance_to_base_B() const {
    Vector center = get_convoy_center();
    Vector base_b = mission_.get_base_b();
    double dx = base_b.x - center.x;
    double dy = base_b.y - center.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool MovementService::has_reached_base_B() const {
    double distance = get_distance_to_base_B();
    double base_size = mission_.get_base_size();   
    return distance <= base_size;
}

Vector MovementService::get_convoy_center() const {
    auto ships = convoy_repo_.get_alive_ships();
    if (ships.empty()) return mission_.get_base_a();
    double sum_x = 0.0, sum_y = 0.0;
    size_t count = 0;
    for (auto ship : ships) {
        Vector pos = ship->get_position();
        sum_x += pos.x;
        sum_y += pos.y;
        count++;
    }
    return Vector(sum_x / count, sum_y / count);
}

void MovementService::reset() {
    is_moving_ = false;
    convoy_speed_ = 0.0;
}
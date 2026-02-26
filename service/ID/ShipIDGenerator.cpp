#include "ShipIDGenerator.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>

size_t ShipIDGenerator::convoy_counter = 0;
size_t ShipIDGenerator::pirate_counter = 0;

void ShipIDGenerator::set_convoy_counter(size_t cnt) {
    convoy_counter = cnt;
}

void ShipIDGenerator::set_pirate_counter(size_t cnt) {
    pirate_counter = cnt;
}

std::string ShipIDGenerator::generate_convoy_id() {
    std::string id;
    size_t counter = convoy_counter++;
    
    if (counter < 26) {
        id = std::string(1, 'A' + counter);
    }
    else if (counter < 702){
        size_t first = (counter - 26) / 26;
        size_t second = (counter - 26) % 26;
        id = std::string(1, 'A' + first) + std::string(1, 'A' + second);
    }
    else {
        size_t temp = counter - 702;
        size_t first = temp / (26 * 26);
        size_t remainder = temp % (26 * 26);
        size_t second = remainder / 26;
        size_t third = remainder % 26;
        
        id = std::string(1, 'A' + first) + std::string(1, 'A' + second) + std::string(1, 'A' + third); 
    }
    
    return id;
}

std::string ShipIDGenerator::generate_pirate_id() {
    std::ostringstream oss;
    oss << (++pirate_counter);
    return oss.str();
}

bool ShipIDGenerator::is_convoy_id(const std::string& id) {
    if (id.empty()) return false;
    
    return std::all_of(id.begin(), id.end(), [](char c) {
        return std::isalpha(c);
    });
}

bool ShipIDGenerator::is_pirate_id(const std::string& id) {
    if (id.empty()) return false;
    
    return std::all_of(id.begin(), id.end(), [](char c) {
        return std::isdigit(c);
    });
}

void ShipIDGenerator::reset() {
    convoy_counter = 0;
    pirate_counter = 0;
}

void ShipIDGenerator::reset_convoy() {
    convoy_counter = 0;
}

void ShipIDGenerator::reset_pirate() {
    pirate_counter = 0;
}

size_t ShipIDGenerator::get_convoy_counter() {
    return convoy_counter;
}

size_t ShipIDGenerator::get_pirate_counter() {
    return pirate_counter;
}
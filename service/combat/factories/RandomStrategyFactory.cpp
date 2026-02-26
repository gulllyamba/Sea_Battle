#include "RandomStrategyFactory.hpp"
#include "../strategy/RandomStrategy.hpp"

RandomStrategyFactory::~RandomStrategyFactory() = default;

std::unique_ptr<IAttackStrategy> RandomStrategyFactory::create_strategy() const {
    return std::make_unique<RandomStrategy>();
}

std::string RandomStrategyFactory::get_name() const {
    return "random";
}

std::string RandomStrategyFactory::get_description() const {
    return "Атаковать случайный корабль"; 
}
#include "StrongestStrategyFactory.hpp"
#include "../strategy/StrongestStrategy.hpp"

StrongestStrategyFactory::~StrongestStrategyFactory() = default;

std::unique_ptr<IAttackStrategy> StrongestStrategyFactory::create_strategy() const {
    return std::make_unique<StrongestStrategy>();
}

std::string StrongestStrategyFactory::get_name() const {
    return "strongest";
}

std::string StrongestStrategyFactory::get_description() const {
    return "Атаковать самый сильный корабль (с наибольшим здоровьем)"; 
}
#include "ClosestStrategyFactory.hpp"
#include "../strategy/ClosestStrategy.hpp"

ClosestStrategyFactory::~ClosestStrategyFactory() = default;

std::unique_ptr<IAttackStrategy> ClosestStrategyFactory::create_strategy() const {
    return std::make_unique<ClosestStrategy>();
}

std::string ClosestStrategyFactory::get_name() const {
    return "closest";
}

std::string ClosestStrategyFactory::get_description() const {
    return "Атаковать ближайший корабль";
}
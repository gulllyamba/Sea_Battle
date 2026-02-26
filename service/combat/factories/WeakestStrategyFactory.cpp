#include "WeakestStrategyFactory.hpp"
#include "../strategy/WeakestStrategy.hpp"

WeakestStrategyFactory::~WeakestStrategyFactory() = default;

std::unique_ptr<IAttackStrategy> WeakestStrategyFactory::create_strategy() const {
    return std::make_unique<WeakestStrategy>();
}

std::string WeakestStrategyFactory::get_name() const {
    return "weakest";
}

std::string WeakestStrategyFactory::get_description() const {
    return "Атаковать самый слабый корабль (с наименьшим здоровьем)";
}
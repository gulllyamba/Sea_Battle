#include "AttackStrategyFactoryManager.hpp"
#include "WeakestStrategyFactory.hpp"
#include "StrongestStrategyFactory.hpp"
#include "ClosestStrategyFactory.hpp"
#include "RandomStrategyFactory.hpp"

AttackStrategyFactoryManager::AttackStrategyFactoryManager() {
    register_factory("weakest", std::make_unique<WeakestStrategyFactory>());
    register_factory("strongest", std::make_unique<StrongestStrategyFactory>());
    register_factory("closest", std::make_unique<ClosestStrategyFactory>());
    register_factory("random", std::make_unique<RandomStrategyFactory>());
}

void AttackStrategyFactoryManager::register_factory(const std::string& name, std::unique_ptr<IAttackStrategyFactory> factory) {
    factories_[name] = std::move(factory);
}

std::unique_ptr<IAttackStrategy> AttackStrategyFactoryManager::create_strategy(const std::string& name) const {
    auto it = factories_.find(name);
    return (it != factories_.end()) ? it->second->create_strategy() : nullptr;
}

IAttackStrategyFactory* AttackStrategyFactoryManager::get_factory(const std::string& type) const {
    auto it = factories_.find(type);
    return (it != factories_.end()) ? it->second.get() : nullptr;
}

std::vector<std::string> AttackStrategyFactoryManager::get_available_strategies() const {
    std::vector<std::string> strategies;
    for (const auto& [name, factory] : factories_) {
        strategies.push_back(name);
    }
    return strategies;
}

bool AttackStrategyFactoryManager::has_strategy(const std::string& name) const {
    return factories_.find(name) != factories_.end();
}
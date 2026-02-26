add_library(service_combat_factories STATIC
    AttackStrategyFactoryManager.cpp
    AttackStrategyFactoryManager.hpp
    ClosestStrategyFactory.cpp
    ClosestStrategyFactory.hpp
    IAttackStrategyFactory.hpp
    RandomStrategyFactory.cpp
    RandomStrategyFactory.hpp
    StrongestStrategyFactory.cpp
    StrongestStrategyFactory.hpp
    WeakestStrategyFactory.cpp
    WeakestStrategyFactory.hpp
)

target_include_directories(service_combat_factories
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_combat_factories
    PRIVATE
        service_combat_strategy
)
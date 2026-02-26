add_library(service_combat_strategy STATIC
    ClosestStrategy.cpp
    ClosestStrategy.hpp
    RandomStrategy.cpp
    RandomStrategy.hpp
    StrongestStrategy.cpp
    StrongestStrategy.hpp
    WeakestStrategy.cpp
    WeakestStrategy.hpp
    IAttackStrategy.hpp
)

target_include_directories(service_combat_strategy
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_combat_strategy
    PRIVATE
        entity
)
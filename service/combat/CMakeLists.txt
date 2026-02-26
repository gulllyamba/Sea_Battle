add_subdirectory(factories)
add_subdirectory(strategy)

add_library(service_combat_core STATIC
    CombatService.cpp
    CombatService.hpp
    DamageService.cpp
    DamageService.hpp
)
target_include_directories(service_combat_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(service_combat_core
    PRIVATE
        mission
        entity
        repository
        visitor
        service_combat_factories
        service_combat_strategy
)

add_library(service_combat INTERFACE)
target_link_libraries(service_combat
    INTERFACE
        service_combat_core
        service_combat_factories
        service_combat_strategy
        entity
        mission
        repository
        visitor
)
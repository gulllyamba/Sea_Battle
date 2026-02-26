add_subdirectory(mission)
add_subdirectory(pirate_base)
add_subdirectory(ship)
add_subdirectory(weapon)

add_library(mapper INTERFACE)

target_link_libraries(mapper
    INTERFACE
        mapper_mission
        mapper_pirate_base
        mapper_ship
        mapper_weapon
)
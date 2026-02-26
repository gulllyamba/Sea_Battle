add_subdirectory(weapon)
add_subdirectory(ship)

add_library(entity STATIC)
target_link_libraries(entity
    PUBLIC
        entity_weapon
        entity_ship
)
target_include_directories(entity
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
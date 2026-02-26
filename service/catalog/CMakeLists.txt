add_subdirectory(ship)
add_subdirectory(weapon)

add_library(service_catalog INTERFACE)

target_link_libraries(service_catalog
    INTERFACE
        service_catalog_ship
        service_catalog_weapon
        entity
)
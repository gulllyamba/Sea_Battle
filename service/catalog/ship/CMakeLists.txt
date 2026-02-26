add_library(service_catalog_ship STATIC
    ShipCatalog.cpp
    ShipCatalog.hpp
    ShipTemplate.cpp
    ShipTemplate.hpp
)

target_include_directories(service_catalog_ship
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_catalog_ship
    PRIVATE
        entity
)
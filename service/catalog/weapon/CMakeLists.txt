add_library(service_catalog_weapon STATIC
    WeaponCatalog.cpp
    WeaponCatalog.hpp
    WeaponTemplate.cpp
    WeaponTemplate.hpp
)

target_include_directories(service_catalog_weapon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_catalog_weapon
    PRIVATE
        entity
)
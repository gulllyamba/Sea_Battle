add_library(visitor_interfaces INTERFACE)
target_sources(visitor_interfaces
    INTERFACE
        IShipVisitor.hpp
)
target_include_directories(visitor_interfaces
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(visitor_cargo STATIC
    cargo/CargoInfoVisitor.cpp
    cargo/CargoInfoVisitor.hpp
    cargo/CargoLoadVisitor.cpp
    cargo/CargoLoadVisitor.hpp
    cargo/CargoRemovalVisitor.cpp
    cargo/CargoRemovalVisitor.hpp
)
target_include_directories(visitor_cargo
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(visitor_place STATIC
    place/HasPlaceWeaponVisitor.cpp
    place/HasPlaceWeaponVisitor.hpp
    place/PlaceForDPSVisitor.cpp
    place/PlaceForDPSVisitor.hpp
    place/PlaceForDamageVisitor.cpp
    place/PlaceForDamageVisitor.hpp
)
target_include_directories(visitor_place
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(visitor_weapon STATIC
    weapon/ShipSellVisitor.cpp
    weapon/ShipSellVisitor.hpp
    weapon/ShootingVisitor.cpp
    weapon/ShootingVisitor.hpp
    weapon/WeaponInstallationVisitor.cpp
    weapon/WeaponInstallationVisitor.hpp
    weapon/WeaponRemovalVisitor.cpp
    weapon/WeaponRemovalVisitor.hpp
)
target_include_directories(visitor_weapon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(visitor_weapon
    PRIVATE
        entity
        service_combat_core
)

add_library(visitor STATIC)
target_link_libraries(visitor
    PRIVATE
        visitor_interfaces
        visitor_cargo
        visitor_place
        visitor_weapon
        entity
)
target_include_directories(visitor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
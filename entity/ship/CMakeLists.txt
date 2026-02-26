add_library(entity_ship_interfaces INTERFACE)
target_sources(entity_ship_interfaces
    INTERFACE
        Interfaces/ICargo.hpp
        Interfaces/IGuard.hpp
        Interfaces/IShip.hpp
        Interfaces/IShipHealth.hpp
        Interfaces/IShipPosition.hpp
)
target_include_directories(entity_ship_interfaces
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(entity_ship_interfaces
    INTERFACE
        auxiliary
        visitor
        entity_weapon_interfaces
)

add_library(entity_ship_abstracts STATIC)
target_sources(entity_ship_abstracts
    PRIVATE
        Abstracts/DefaultCargo.cpp
        Abstracts/DefaultShip.cpp
        Abstracts/DefaultGuard.cpp
    PUBLIC
        Abstracts/DefaultGuard.hpp
        Abstracts/DefaultCargo.hpp
        Abstracts/DefaultShip.hpp
)
target_include_directories(entity_ship_abstracts
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_ship_abstracts
    PUBLIC
        entity_ship_interfaces
        template
        auxiliary
)

add_library(entity_ship_concrete STATIC)
target_sources(entity_ship_concrete
    PRIVATE
        Concrete/GuardShip.cpp
        Concrete/TransportShip.cpp
        Concrete/WarShip.cpp
    PUBLIC
        Concrete/GuardShip.hpp
        Concrete/TransportShip.hpp
        Concrete/WarShip.hpp
)
target_include_directories(entity_ship_concrete
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_ship_concrete
    PUBLIC
        entity_ship_abstracts
)

add_library(entity_ship_factories STATIC)
target_sources(entity_ship_factories
    PRIVATE
        Factories/GuardShipFactory.cpp
        Factories/ShipFactoryManager.cpp
        Factories/TransportShipFactory.cpp
        Factories/WarShipFactory.cpp
    PUBLIC
        Factories/GuardShipFactory.hpp
        Factories/IShipFactory.hpp
        Factories/ShipFactoryManager.hpp
        Factories/TransportShipFactory.hpp
        Factories/WarShipFactory.hpp
)
target_include_directories(entity_ship_factories
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_ship_factories
    PUBLIC
        service_id
        entity_ship_concrete
)

add_library(entity_ship STATIC)
target_link_libraries(entity_ship
    PUBLIC
        entity_ship_interfaces
        entity_ship_abstracts
        entity_ship_concrete
        entity_ship_factories
)
target_include_directories(entity_ship
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
add_library(entity_weapon_interfaces INTERFACE)
target_sources(entity_weapon_interfaces
    INTERFACE
        Interfaces/IWeapon.hpp
)
target_include_directories(entity_weapon_interfaces
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(entity_weapon_abstracts STATIC)
target_sources(entity_weapon_abstracts
    PRIVATE
        Abstracts/DefaultWeapon.cpp
    PUBLIC
        Abstracts/DefaultWeapon.hpp
)
target_include_directories(entity_weapon_abstracts
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_weapon_abstracts
    PUBLIC
        entity_weapon_interfaces
)

add_library(entity_weapon_concrete STATIC)
target_sources(entity_weapon_concrete
    PRIVATE
        Concrete/Gun.cpp
        Concrete/Rocket.cpp
    PUBLIC
        Concrete/Gun.hpp
        Concrete/Rocket.hpp
)
target_include_directories(entity_weapon_concrete
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_weapon_concrete
    PUBLIC
        entity_weapon_abstracts
)

add_library(entity_weapon_factories STATIC)
target_sources(entity_weapon_factories
    PRIVATE
        Factories/GunFactory.cpp
        Factories/RocketFactory.cpp
        Factories/WeaponFactoryManager.cpp
    PUBLIC
        Factories/IWeaponFactory.hpp
        Factories/GunFactory.hpp
        Factories/RocketFactory.hpp
        Factories/WeaponFactoryManager.hpp
)
target_include_directories(entity_weapon_factories
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(entity_weapon_factories
    PUBLIC
        template
        entity_weapon_concrete
)

add_library(entity_weapon STATIC)
target_link_libraries(entity_weapon
    PUBLIC
        entity_weapon_interfaces
        entity_weapon_abstracts
        entity_weapon_concrete
        entity_weapon_factories
)
target_include_directories(entity_weapon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
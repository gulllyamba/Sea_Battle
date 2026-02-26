add_library(mapper_weapon_from
    FromDTO/GunMapper.cpp
    FromDTO/GunMapper.hpp
    FromDTO/RocketMapper.cpp
    FromDTO/RocketMapper.hpp
    FromDTO/IWeaponMapper.hpp
)

add_library(mapper_weapon_to
    ToDTO/GunDTOMapper.cpp
    ToDTO/GunDTOMapper.hpp
    ToDTO/RocketDTOMapper.cpp
    ToDTO/RocketDTOMapper.hpp
    ToDTO/IWeaponDTOMapper.hpp
)

add_library(mapper_weapon_managers
    Managers/WeaponDTOMapperManager.cpp
    Managers/WeaponDTOMapperManager.hpp
    Managers/WeaponMapperManager.cpp
    Managers/WeaponMapperManager.hpp
)
target_link_libraries(mapper_weapon_managers
    INTERFACE
        mapper_weapon_from
        mapper_weapon_to
)

add_library(mapper_weapon INTERFACE)
target_link_libraries(mapper_weapon
    INTERFACE
        mapper_weapon_from
        mapper_weapon_to
        mapper_weapon_managers
        entity
        DTO
)
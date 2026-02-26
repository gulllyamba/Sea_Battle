add_library(mapper_ship_from
    FromDTO/GuardShipMapper.cpp
    FromDTO/GuardShipMapper.hpp
    FromDTO/TransportShipMapper.cpp
    FromDTO/TransportShipMapper.hpp
    FromDTO/WarShipMapper.cpp
    FromDTO/WarShipMapper.hpp
    FromDTO/IShipMapper.hpp
)

add_library(mapper_ship_to
    ToDTO/GuardShipDTOMapper.cpp
    ToDTO/GuardShipDTOMapper.hpp
    ToDTO/TransportShipDTOMapper.cpp
    ToDTO/TransportShipDTOMapper.hpp
    ToDTO/WarShipDTOMapper.cpp
    ToDTO/WarShipDTOMapper.hpp
    ToDTO/IShipDTOMapper.hpp
)

add_library(mapper_ship_managers
    Managers/ShipDTOMapperManager.cpp
    Managers/ShipDTOMapperManager.hpp
    Managers/ShipMapperManager.cpp
    Managers/ShipMapperManager.hpp
)
target_link_libraries(mapper_ship_managers
    INTERFACE
        mapper_ship_from
        mapper_ship_to
)

add_library(mapper_ship INTERFACE)
target_link_libraries(mapper_ship
    INTERFACE
        mapper_ship_from
        mapper_ship_to
        mapper_ship_managers
        entity
        DTO
)
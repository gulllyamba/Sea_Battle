add_library(DTO INTERFACE)

target_sources(DTO
    INTERFACE
        ShipDTO.hpp
        WeaponDTO.hpp
        PirateBaseDTO.hpp
        MissionDTO.hpp
)

target_include_directories(DTO
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(DTO
    INTERFACE
        auxiliary
        template
)
add_library(mapper_pirate_base_from
    FromDTO/PirateBaseMapper.cpp
    FromDTO/PirateBaseMapper.hpp
    FromDTO/IPirateBaseMapper.hpp
)

add_library(mapper_pirate_base_to
    ToDTO/PirateBaseDTOMapper.cpp
    ToDTO/PirateBaseDTOMapper.hpp
    ToDTO/IPirateBaseDTOMapper.hpp
)

add_library(mapper_pirate_base INTERFACE)
target_link_libraries(mapper_pirate_base
    INTERFACE
        mapper_pirate_base_from
        mapper_pirate_base_to
        auxiliary
        DTO
)
add_library(mapper_mission_from
    FromDTO/MissionMapper.cpp
    FromDTO/MissionMapper.hpp
    FromDTO/IMissionMapper.hpp
)

add_library(mapper_mission_to
    ToDTO/MissionDTOMapper.cpp
    ToDTO/MissionDTOMapper.hpp
    ToDTO/IMissionDTOMapper.hpp
)

add_library(mapper_mission INTERFACE)
target_link_libraries(mapper_mission
    INTERFACE
        mapper_mission_from
        mapper_mission_to
        mission
        DTO
)
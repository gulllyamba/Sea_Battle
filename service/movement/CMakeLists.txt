add_library(service_movement STATIC
    MovementService.cpp
    MovementService.hpp
)

target_include_directories(service_movement
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_movement
    PRIVATE
        auxiliary
        mission
        repository
)
add_library(service_pirate STATIC
    PirateSpawnService.cpp
    PirateSpawnService.hpp
)

target_include_directories(service_pirate
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_pirate
    PRIVATE
        auxiliary
        mission
        repository
        visitor
        service_catalog
)
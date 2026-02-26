add_library(repository STATIC
    ShipRepository.cpp
    ShipRepository.hpp
    PirateRepository.cpp
    PirateRepository.hpp
    ICRUD.hpp
    IShipRepository.hpp
)

target_include_directories(repository
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(repository
    PRIVATE
        entity
)
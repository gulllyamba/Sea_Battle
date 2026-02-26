add_library(service_id STATIC
    ShipIDGenerator.cpp
    ShipIDGenerator.hpp
)

target_include_directories(service_id
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
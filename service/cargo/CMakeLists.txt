add_library(service_cargo STATIC
    CargoService.cpp
    CargoService.hpp
)

target_include_directories(service_cargo
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_cargo
    PRIVATE
        mission
        repository
        visitor
)
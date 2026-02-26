add_library(mission STATIC
    Mission.cpp
    Mission.hpp
)

target_include_directories(mission
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mission
    PRIVATE
        auxiliary
)
add_library(view STATIC
    ViewConsole.cpp
    ViewConsole.hpp
)

target_include_directories(view
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../loader
        ${CMAKE_CURRENT_SOURCE_DIR}/../presenter
)

target_include_directories(view PUBLIC ${SFML_INCLUDE_DIRS})
target_link_libraries(view PRIVATE ${SFML_LIBRARIES} loader presenter)
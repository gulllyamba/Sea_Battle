add_library(loader STATIC
    Loader.cpp
    Loader.hpp
)

target_include_directories(loader
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(loader
    PRIVATE
        presenter
)
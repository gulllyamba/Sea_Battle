add_library(template INTERFACE)

target_sources(template
    INTERFACE
        LookupTable.hpp
        TableIterator.hpp
        TableNode.hpp
)

target_include_directories(template
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
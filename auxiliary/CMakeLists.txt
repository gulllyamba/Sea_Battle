add_library(auxiliary INTERFACE)

target_sources(auxiliary
    INTERFACE
        Vector.hpp
        PlaceForWeapon.hpp
        PirateBase.hpp
        Military.hpp
)

target_include_directories(auxiliary
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
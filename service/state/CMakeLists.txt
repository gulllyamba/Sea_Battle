# if(NOT BUILD_TYPE_FOR_SUBDIRS STREQUAL "TSAN")
#     find_package(yaml-cpp QUIET)
# endif()

# add_library(service_state STATIC
#     YamlStateService.cpp
#     YamlStateService.hpp
#     IStateService.hpp
# )

# target_include_directories(service_state
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(service_state
#     PRIVATE
#         auxiliary
#         mission
#         repository
#         mapper
# )


# if(yaml-cpp_FOUND)
#     target_link_libraries(service_state PRIVATE yaml-cpp)
# elseif(NOT BUILD_TYPE_FOR_SUBDIRS STREQUAL "TSAN")
#     message(WARNING "yaml-cpp not found, state service may not work correctly")
# endif()




























# service/state/CMakeLists.txt - минималистичный вариант

if(NOT BUILD_TYPE_FOR_SUBDIRS STREQUAL "TSAN")
    find_package(yaml-cpp QUIET)
    
    if(yaml-cpp_FOUND)
        add_library(service_state STATIC
            YamlStateService.cpp
            YamlStateService.hpp
            IStateService.hpp
        )
        
        target_include_directories(service_state
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}
        )
        
        target_link_libraries(service_state
            PRIVATE
                auxiliary
                mission
                repository
                mapper
                yaml-cpp
        )
    else()
        message(WARNING "yaml-cpp not found, state service will not be built")
        # Создаем пустую библиотеку-заглушку
        add_library(service_state STATIC)
        target_compile_definitions(service_state INTERFACE YAML_CPP_NOT_FOUND)
    endif()
else()
    # Для TSAN создаем пустую библиотеку-заглушку
    add_library(service_state STATIC)
    target_compile_definitions(service_state INTERFACE 
        TSAN_BUILD 
        YAML_STATE_SERVICE_DISABLED
    )
endif()
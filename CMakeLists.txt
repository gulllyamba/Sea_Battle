cmake_minimum_required(VERSION 3.20)
project(PirateGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra --coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_compile_options(-fsanitize=thread -g)
add_link_options(-fsanitize=thread)

add_subdirectory(template)
add_subdirectory(auxiliary)
add_subdirectory(DTO)
add_subdirectory(mission)
add_subdirectory(entity)
add_subdirectory(mapper)
add_subdirectory(repository)
add_subdirectory(visitor)
add_subdirectory(service)
add_subdirectory(presenter)
add_subdirectory(loader)
add_subdirectory(view)

add_executable(main main.cpp)
target_link_libraries(main
    PRIVATE
        template
        auxiliary
        DTO
        mission
        entity
        entity_ship_abstracts
        entity_ship_concrete
        entity_ship_factories
        mapper
        repository
        visitor
        service
        presenter
        loader
        view
)

find_package(Catch2 3 REQUIRED)
add_executable(tests test.cpp)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        template
        auxiliary
        DTO
        mission
        entity
        mapper
        repository
        visitor
        service
        presenter
        loader
)

add_executable(main_tsan main_tsan.cpp)
target_link_libraries(main_tsan
    PRIVATE
        template
        auxiliary
        DTO
        mission
        entity
        entity_ship_abstracts
        entity_ship_concrete
        entity_ship_factories
        mapper
        repository
        visitor
        service
        presenter
        loader
        view
)

install(TARGETS main DESTINATION bin)
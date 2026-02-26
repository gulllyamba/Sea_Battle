add_subdirectory(ID)
add_subdirectory(cargo)
add_subdirectory(catalog)
add_subdirectory(combat)
add_subdirectory(movement)
add_subdirectory(pirate)
add_subdirectory(purchase)
add_subdirectory(state)

add_library(service STATIC)

target_link_libraries(service
    PRIVATE
        service_id
        service_cargo
        service_catalog
        service_combat
        service_movement
        service_pirate
        service_purchase
        service_state
        entity
        visitor
        auxiliary
        DTO
        template
)

target_include_directories(service
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
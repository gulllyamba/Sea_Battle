add_library(service_purchase STATIC
    PurchaseService.cpp
    PurchaseService.hpp
)

target_include_directories(service_purchase
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service_purchase
    PRIVATE
        auxiliary
        mission
        repository
        service_catalog
        visitor
)
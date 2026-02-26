add_library(presenter STATIC
    Presenter.cpp
    Presenter.hpp
    IPresenter.hpp
)

target_include_directories(presenter
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(presenter
    PRIVATE
        DTO
        service
)
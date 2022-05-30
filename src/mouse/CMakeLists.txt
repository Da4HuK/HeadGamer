set(TARGET mouse)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE include/mouse/Mouse4DirectionsHandler.hpp
            Mouse4DirectionsHandler.cpp
            MouseActionHandler.cpp
            include/mouse/MouseActionHandler.hpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Widgets
                      common
                      ui
                      keyboard
                      action
                      settings
                      hook
)

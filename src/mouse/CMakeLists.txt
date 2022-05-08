set(TARGET mouse)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE Mouse4DirectionsHandler.cpp
            MouseActionHandler.cpp
            MouseHookHandler.cpp
            include/mouse/Mouse4DirectionsHandler.hpp
            include/mouse/MouseActionHandler.hpp
            include/mouse/MouseHookHandler.hpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets common ui keyboard action settings
)

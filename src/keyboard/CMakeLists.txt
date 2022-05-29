set(TARGET keyboard)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE KeyboardHandler.cpp
    include/keyboard/KeyboardHandler.hpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets common action uiohook
)

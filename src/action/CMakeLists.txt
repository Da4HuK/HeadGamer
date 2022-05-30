set(TARGET action)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE ActionBase.cpp
            KeyPressAction.cpp
            MacroAction.cpp
            WindowActionConfig.cpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets common keyboard
)

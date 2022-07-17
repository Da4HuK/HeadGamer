set(TARGET action)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE include/action/ActionBase.hpp
            ActionBase.cpp
            include/action/KeyPressAction.hpp
            KeyPressAction.cpp
            include/action/MacroAction.hpp
            MacroAction.cpp
            include/action/WindowActionConfig.hpp
            WindowActionConfig.cpp
            include/action/WindowActionConfigList.hpp
            WindowActionConfigList.cpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets common keyboard
)

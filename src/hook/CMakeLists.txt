set(TARGET hook)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE include/hook/HookHandler.hpp
            HookHandler.cpp
)

target_include_directories(${TARGET} PUBLIC include)


target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets common keyboard mouse uiohook Threads::Threads
)

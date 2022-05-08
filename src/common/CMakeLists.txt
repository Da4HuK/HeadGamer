set(TARGET common)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE Types.cpp
            Utils.cpp
)

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets keyboard action settings ui
)

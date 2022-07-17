set(TARGET common)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE include/common/Types.hpp
            Types.cpp
            include/common/Utils.hpp
            Utils.cpp
            include/common/IJson.hpp
)

target_include_directories(${TARGET} PUBLIC include ${UIOHOOK_HEADERS})

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets keyboard action settings ui uiohook
)

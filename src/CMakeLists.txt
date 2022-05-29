set(TARGET ${PROJECT_NAME})

add_subdirectory(UI)
add_subdirectory(settings)
add_subdirectory(common)
add_subdirectory(action)
add_subdirectory(keyboard)
add_subdirectory(mouse)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${TARGET}
        MANUAL_FINALIZATION
        ${SOURCES}
    )
else()
    if(ANDROID)
        add_library(${TARGET} SHARED
            ${SOURCES}
            resources/resources.qrc
        )
    else()
        add_executable(${TARGET}
            ${SOURCES}
            resources/resources.qrc
        )
    endif()
endif()

target_sources(${TARGET} PRIVATE main.cpp)
target_link_libraries(${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core ui settings common action keyboard mouse)

set_target_properties(${TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${TARGET})
endif()


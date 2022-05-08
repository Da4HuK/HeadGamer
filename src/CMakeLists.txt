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
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET test_qt_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${TARGET} SHARED
            ${SOURCES}
            resources/resources.qrc
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
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


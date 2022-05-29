set(TARGET ui)

add_library(${TARGET} STATIC "")

target_sources(
    ${TARGET}
    PRIVATE ComboBoxDelegate.cpp
            DirectionButton.cpp
            DirectionWidget.cpp
            MainWindow.cpp
            WindowActionWidget.cpp
            WindowConfigForm.cpp
            WindowConfigItem.cpp
            MouseInfo.cpp
            include/UI/MainWindow.hpp
            include/UI/WindowConfigForm.hpp
            include/UI/WindowConfigItem.hpp
            include/UI/ComboBoxDelegate.hpp
            include/UI/WindowActionWidget.hpp
            include/UI/MouseInfo.hpp
            include/UI/DirectionWidget.hpp
            include/UI/DirectionButton.hpp
            MainWindow.ui
            WindowConfigForm.ui
            WindowConfigItem.ui
#            ${ui_gen} ${moc_gen}
)

target_include_directories(
    ${TARGET} 
    PUBLIC include 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    ${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets settings action common keyboard mouse
)

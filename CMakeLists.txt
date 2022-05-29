cmake_minimum_required(VERSION 3.5)

project(HeadGamer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Threads REQUIRED)

set(UIOHOOK_HEADERS ${CMAKE_SOURCE_DIR}/libuiohook/include)
message("UIOHOOK_HEADERS = ${UIOHOOK_HEADERS}")

add_subdirectory(libuiohook)

find_library(uiohook
    NAMES uiohook libuiohook
    PATHS "${CMAKE_BINARY_DIR}/libuiohook"
    NO_CACHE
)

add_subdirectory(src)

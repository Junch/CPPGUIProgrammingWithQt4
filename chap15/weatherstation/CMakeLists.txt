# Weatherstation example
cmake_minimum_required(VERSION 3.16)
project(weatherstation)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Network)
else()
    find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Network)
endif()

add_executable(weatherstation
    weatherstation.h
    main.cpp
    weatherstation.cpp
)

target_link_libraries(weatherstation ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(weatherstation)
endif()

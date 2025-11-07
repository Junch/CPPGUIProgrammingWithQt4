# Plotter example
cmake_minimum_required(VERSION 3.16)
project(plotter)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::PrintSupport)
else()
    find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::PrintSupport)
endif()

add_executable(plotter
    plotter.h
    plotter.cpp
    main.cpp
    plotter.qrc
)

target_link_libraries(plotter ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(plotter)
endif()

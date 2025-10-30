# Plotter example
cmake_minimum_required(VERSION 3.16)
project(plotter_appendixc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::PrintSupport)
else()
    find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::PrintSupport)
endif()

add_executable(plotter_appendixc
    plotter.h
    main.cpp
    plotter.cpp
    plotter.qrc
    plotter.qrc
)

target_link_libraries(plotter_appendixc ${QT_LIBS})

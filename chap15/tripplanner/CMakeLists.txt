# Tripplanner example
cmake_minimum_required(VERSION 3.16)
project(tripplanner)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Network)
else()
    find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Network)
endif()

add_executable(tripplanner
    tripplanner.h
    main.cpp
    tripplanner.cpp
    tripplanner.ui
)

target_link_libraries(tripplanner ${QT_LIBS})

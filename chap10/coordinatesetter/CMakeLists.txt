# Coordinatesetter example
cmake_minimum_required(VERSION 3.16)
project(coordinatesetter)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(coordinatesetter
    coordinatesetter.h
    coordinatesetter.cpp
    main.cpp
)

target_link_libraries(coordinatesetter ${QT_LIBS})

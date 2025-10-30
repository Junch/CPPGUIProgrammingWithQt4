# Cursorplugin example
cmake_minimum_required(VERSION 3.16)
project(cursorplugin)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_library(cursorplugin SHARED
    cursorhandler.h
    cursorplugin.h
    cursorhandler.cpp
    cursorplugin.cpp
)

target_link_libraries(cursorplugin ${QT_LIBS})

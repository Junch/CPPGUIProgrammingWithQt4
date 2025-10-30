# Extraeffectsplugin example
cmake_minimum_required(VERSION 3.16)
project(extraeffectsplugin)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_library(extraeffectsplugin SHARED
    ../textart/textartinterface.h
    extraeffectsplugin.h
    extraeffectsplugin.cpp
)

target_link_libraries(extraeffectsplugin ${QT_LIBS})

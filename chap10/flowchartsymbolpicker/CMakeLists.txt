# Flowchartsymbolpicker example
cmake_minimum_required(VERSION 3.16)
project(flowchartsymbolpicker)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(flowchartsymbolpicker
    flowchartsymbolpicker.h
    flowchartsymbolpicker.cpp
    main.cpp
    flowchartsymbolpicker.qrc
    flowchartsymbolpicker.qrc
)

target_link_libraries(flowchartsymbolpicker ${QT_LIBS})

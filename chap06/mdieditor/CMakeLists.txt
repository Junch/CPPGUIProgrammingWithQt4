# Mdieditor example
cmake_minimum_required(VERSION 3.16)
project(mdieditor)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(mdieditor
    editor.h
    mainwindow.h
    editor.cpp
    main.cpp
    mainwindow.cpp
    mdieditor.qrc
    mdieditor.qrc
)

target_link_libraries(mdieditor ${QT_LIBS})

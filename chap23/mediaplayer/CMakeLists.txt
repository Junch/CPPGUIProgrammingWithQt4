# Mediaplayer example
cmake_minimum_required(VERSION 3.16)
project(mediaplayer)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)
else()
    find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
endif()

add_executable(mediaplayer
    playerwindow.h
    main.cpp
    playerwindow.cpp
)

target_link_libraries(mediaplayer ${QT_LIBS})

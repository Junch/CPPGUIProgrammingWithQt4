# Candy example
cmake_minimum_required(VERSION 3.16)
project(candy)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(candy
    candydialog.h
    candydialog.cpp
    main.cpp
    candy.qrc
    candy.qrc
)

target_link_libraries(candy ${QT_LIBS})

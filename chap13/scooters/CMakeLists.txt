# Scooters example
cmake_minimum_required(VERSION 3.16)
project(scooters)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Sql)
else()
    find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Sql)
endif()

add_executable(scooters
    scooterwindow.h
    main.cpp
    scooterwindow.cpp
)

target_link_libraries(scooters ${QT_LIBS})

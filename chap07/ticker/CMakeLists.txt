# Ticker example
cmake_minimum_required(VERSION 3.16)
project(ticker)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(ticker
    ticker.h
    main.cpp
    ticker.cpp
)

target_link_libraries(ticker ${QT_LIBS})

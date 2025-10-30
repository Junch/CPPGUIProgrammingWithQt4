# Tripserver example
cmake_minimum_required(VERSION 3.16)
project(tripserver)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Network)
else()
    find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Network)
endif()

add_executable(tripserver
    clientsocket.h
    tripserver.h
    clientsocket.cpp
    main.cpp
    tripserver.cpp
)

target_link_libraries(tripserver ${QT_LIBS})

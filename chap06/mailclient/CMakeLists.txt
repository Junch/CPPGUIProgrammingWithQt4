# Mailclient example
cmake_minimum_required(VERSION 3.16)
project(mailclient)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(mailclient
    mailclient.h
    mailclient.cpp
    main.cpp
)

target_link_libraries(mailclient ${QT_LIBS})

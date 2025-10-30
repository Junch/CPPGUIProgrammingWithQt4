# Saxhandler example
cmake_minimum_required(VERSION 3.16)
project(saxhandler)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Xml REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Xml)
else()
    find_package(Qt5 COMPONENTS Widgets Xml REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Xml)
endif()

add_executable(saxhandler
    saxhandler.h
    main.cpp
    saxhandler.cpp
)

target_link_libraries(saxhandler ${QT_LIBS})

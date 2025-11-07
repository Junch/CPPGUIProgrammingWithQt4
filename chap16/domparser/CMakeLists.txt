# Domparser example
cmake_minimum_required(VERSION 3.16)
project(domparser)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Xml REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Xml)
else()
    find_package(Qt5 COMPONENTS Widgets Xml REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Xml)
endif()

add_executable(domparser
    domparser.h
    domparser.cpp
    main.cpp
)

target_link_libraries(domparser ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(domparser)
endif()

# Booleanparser example
cmake_minimum_required(VERSION 3.16)
project(booleanparser)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(booleanparser
    booleanmodel.h
    booleanparser.h
    booleanwindow.h
    node.h
    booleanmodel.cpp
    booleanparser.cpp
    booleanwindow.cpp
    main.cpp
    node.cpp
)

target_link_libraries(booleanparser ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(booleanparser)
endif()

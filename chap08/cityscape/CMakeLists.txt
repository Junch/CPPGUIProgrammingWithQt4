# Cityscape example
cmake_minimum_required(VERSION 3.16)
project(cityscape)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(cityscape
    annotation.h
    cityblock.h
    cityscape.h
    cityview.h
    annotation.cpp
    cityblock.cpp
    cityscape.cpp
    cityview.cpp
    main.cpp
)

target_link_libraries(cityscape ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(cityscape)
endif()

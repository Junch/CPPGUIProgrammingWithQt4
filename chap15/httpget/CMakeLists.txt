# Httpget example
cmake_minimum_required(VERSION 3.16)
project(httpget)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Network Core REQUIRED)
    set(QT_LIBS Qt6::Network Qt6::Core)
else()
    find_package(Qt5 COMPONENTS Network Core REQUIRED)
    set(QT_LIBS Qt5::Network Qt5::Core)
endif()

add_executable(httpget
    httpget.h
    httpget.cpp
    main.cpp
)

target_link_libraries(httpget ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(httpget)
endif()

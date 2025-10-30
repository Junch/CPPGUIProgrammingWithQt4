# Tidy example
cmake_minimum_required(VERSION 3.16)
project(tidy)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Core REQUIRED)
    set(QT_LIBS Qt6::Core)
else()
    find_package(Qt5 COMPONENTS Core REQUIRED)
    set(QT_LIBS Qt5::Core)
endif()

add_executable(tidy
    tidy.cpp
)

target_link_libraries(tidy ${QT_LIBS})

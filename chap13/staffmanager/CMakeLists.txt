# Staffmanager example
cmake_minimum_required(VERSION 3.16)
project(staffmanager)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Sql)
else()
    find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Sql)
endif()

add_executable(staffmanager
    employeeform.h
    mainform.h
    employeeform.cpp
    main.cpp
    mainform.cpp
)

target_link_libraries(staffmanager ${QT_LIBS})

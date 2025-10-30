# Calculator example
cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Qml REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Qml)
else()
    find_package(Qt5 COMPONENTS Widgets Qml REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Qml)
endif()

add_executable(calculator
    calculator.h
    calculator.cpp
    main.cpp
)

target_link_libraries(calculator ${QT_LIBS})

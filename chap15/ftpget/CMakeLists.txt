# Ftpget example
cmake_minimum_required(VERSION 3.16)
project(ftpget)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Network Core REQUIRED)
    set(QT_LIBS Qt6::Network Qt6::Core)
else()
    find_package(Qt5 COMPONENTS Network Core REQUIRED)
    set(QT_LIBS Qt5::Network Qt5::Core)
endif()

add_executable(ftpget
    ftpget.h
    ftpget.cpp
    main.cpp
)

target_link_libraries(ftpget ${QT_LIBS})

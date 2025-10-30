# Bouncer example
cmake_minimum_required(VERSION 3.16)
project(bouncer)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

set(SOURCES
    axbouncer.h
    axbouncer.cpp
    main.cpp
)

# Add Windows-specific files only on Windows
if(WIN32)
    list(APPEND SOURCES
        objectsafetyimpl.h
        objectsafetyimpl.cpp
    )
endif()

add_executable(bouncer ${SOURCES})

target_link_libraries(bouncer ${QT_LIBS})

# Teapots example
cmake_minimum_required(VERSION 3.16)
project(teapots)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
else()
    find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::OpenGL)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

add_executable(teapots
    teapots.h
    main.cpp
    teapots.cpp
)

target_link_libraries(teapots ${QT_LIBS} OpenGL::GL)
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(teapots)
endif()

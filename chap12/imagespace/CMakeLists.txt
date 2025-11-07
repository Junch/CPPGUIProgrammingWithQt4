# Imagespace example
cmake_minimum_required(VERSION 3.16)
project(imagespace)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Gui Widgets Core Xml REQUIRED)
    set(QT_LIBS Qt6::Gui Qt6::Widgets Qt6::Core Qt6::Xml)
else()
    find_package(Qt5 COMPONENTS Gui Widgets Core Xml REQUIRED)
    set(QT_LIBS Qt5::Gui Qt5::Widgets Qt5::Core Qt5::Xml)
endif()

add_executable(imagespace
    imagespace.cpp
)

target_link_libraries(imagespace ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(imagespace)
endif()

# Gaspump example
cmake_minimum_required(VERSION 3.16)
project(gaspump)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Xml Qml REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Xml Qt6::Qml)
else()
    find_package(Qt5 COMPONENTS Widgets Xml Qml REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Xml Qt5::Qml)
endif()

add_executable(gaspump
    filterdialog.h
    pumpspreadsheet.h
    pumpwindow.h
    scripting.h
    filterdialog.cpp
    main.cpp
    pumpspreadsheet.cpp
    pumpwindow.cpp
    scripting.cpp
    filterdialog.ui
)

target_link_libraries(gaspump ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(gaspump)
endif()

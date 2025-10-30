# IconEditor Plugin example
cmake_minimum_required(VERSION 3.16)
project(iconeditorplugin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Designer REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Designer)
else()
    find_package(Qt5 COMPONENTS Widgets Designer REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Designer)
endif()

add_library(iconeditorplugin SHARED
    ../iconeditor/iconeditor.h
    iconeditorplugin.h
    ../iconeditor/iconeditor.cpp
    iconeditorplugin.cpp
    iconeditorplugin.qrc
)

target_link_libraries(iconeditorplugin ${QT_LIBS})

# Install to Qt Designer plugin directory (optional)
# install(TARGETS iconeditorplugin DESTINATION ${QT_PLUGINS_DIR}/designer)

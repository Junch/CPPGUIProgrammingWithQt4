# Htmleditor example
cmake_minimum_required(VERSION 3.16)
project(htmleditor)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets Qml UiTools REQUIRED)
    set(QT_LIBS Qt6::Widgets Qt6::Qml Qt6::UiTools)
else()
    find_package(Qt5 COMPONENTS Widgets Qml UiTools REQUIRED)
    set(QT_LIBS Qt5::Widgets Qt5::Qml Qt5::UiTools)
endif()

add_executable(htmleditor
    htmlsyntaxhighlighter.h
    htmlwindow.h
    htmlsyntaxhighlighter.cpp
    htmlwindow.cpp
    main.cpp
)

target_link_libraries(htmleditor ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(htmleditor)
endif()

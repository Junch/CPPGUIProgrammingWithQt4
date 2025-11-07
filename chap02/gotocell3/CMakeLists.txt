# GoToCell Dialog example 3
cmake_minimum_required(VERSION 3.16)
project(gotocell3)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(gotocell3
    gotocelldialog.h
    gotocelldialog.cpp
    main.cpp
    gotocelldialog.ui
)

target_link_libraries(gotocell3 ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(gotocell3)
endif()

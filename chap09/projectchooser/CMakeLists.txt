# Projectchooser example
cmake_minimum_required(VERSION 3.16)
project(projectchooser)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(projectchooser
    projectdialog.h
    projectlistwidget.h
    main.cpp
    projectdialog.cpp
    projectlistwidget.cpp
    projectchooser.qrc
    projectdialog.ui
    projectchooser.qrc
)

# 确保 UI 生成的文件能找到自定义部件头文件
target_include_directories(projectchooser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(projectchooser ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(projectchooser)
endif()

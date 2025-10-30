# Spreadsheet example (Chapter 4)
cmake_minimum_required(VERSION 3.16)
project(spreadsheet_chap04)

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

add_executable(spreadsheet_chap04
    cell.h
    finddialog.h
    gotocelldialog.h
    mainwindow.h
    sortdialog.h
    spreadsheet.h
    cell.cpp
    finddialog.cpp
    gotocelldialog.cpp
    main.cpp
    mainwindow.cpp
    sortdialog.cpp
    spreadsheet.cpp
    gotocelldialog.ui
    sortdialog.ui
    spreadsheet.qrc
)

target_link_libraries(spreadsheet_chap04 ${QT_LIBS})

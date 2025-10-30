# Imagepro example
cmake_minimum_required(VERSION 3.16)
project(imagepro)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(imagepro
    imagewindow.h
    transactionthread.h
    imagewindow.cpp
    main.cpp
    transactionthread.cpp
    resizedialog.ui
)

target_link_libraries(imagepro ${QT_LIBS})

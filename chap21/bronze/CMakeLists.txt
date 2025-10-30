# Bronze example
cmake_minimum_required(VERSION 3.16)
project(bronze_chap21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(bronze_chap21
    bronzedialog.h
    bronzestyle.h
    bronzedialog.cpp
    bronzestyle.cpp
    main.cpp
    bronze.qrc
    bronze.qrc
)

target_link_libraries(bronze_chap21 ${QT_LIBS})

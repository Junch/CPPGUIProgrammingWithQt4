# Bronze example
cmake_minimum_required(VERSION 3.16)
project(bronze_chap19)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(bronze_chap19
    bronzedialog.h
    bronzestyle.h
    bronzedialog.cpp
    bronzestyle.cpp
    main.cpp
    bronze.qrc
    bronze.qrc
)

target_link_libraries(bronze_chap19 ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(bronze_chap19)
endif()

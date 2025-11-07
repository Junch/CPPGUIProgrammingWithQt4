# Hello example
cmake_minimum_required(VERSION 3.16)
project(hello)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(hello hello.cpp)
target_link_libraries(hello ${QT_LIBS})

# Windows平台自动拷贝Qt运行库
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(hello)
endif()

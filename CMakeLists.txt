cmake_minimum_required(VERSION 3.16)
project(CPPGUIProgrammingWithQt4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS 架构设置 (默认使用 x86_64 以匹配常见的 Qt 库)
if(APPLE)
    # 如果没有指定架构，默认使用 x86_64
    if(NOT CMAKE_OSX_ARCHITECTURES)
        set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architecture" FORCE)
    endif()
    message(STATUS "Building for macOS architecture: ${CMAKE_OSX_ARCHITECTURES}")
    message(STATUS "提示: 如需使用 arm64，请添加 -DCMAKE_OSX_ARCHITECTURES=arm64")
endif()

# 自动运行MOC, UIC和RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找Qt包
find_package(Qt5 COMPONENTS Core Widgets Gui PrintSupport Network Xml QUIET)

if(NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Widgets Gui PrintSupport Network Xml OpenGLWidgets QUIET)
    if(Qt6_FOUND)
        message(STATUS "Using Qt6")
        set(QT_VERSION_MAJOR 6)
    else()
        message(FATAL_ERROR "Qt5 or Qt6 not found. Please install Qt development packages.")
    endif()
else()
    message(STATUS "Using Qt5")
    set(QT_VERSION_MAJOR 5)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加子目录
add_subdirectory(chap01)
add_subdirectory(chap02)
add_subdirectory(chap03)
add_subdirectory(chap04)
add_subdirectory(chap05)
add_subdirectory(chap06)
add_subdirectory(chap07)
add_subdirectory(chap08)
add_subdirectory(chap09)
add_subdirectory(chap10)
add_subdirectory(chap12)
add_subdirectory(chap13)
add_subdirectory(chap14)
add_subdirectory(chap15)
add_subdirectory(chap16)
add_subdirectory(chap19)
add_subdirectory(chap20)
add_subdirectory(chap21)
add_subdirectory(chap22)
add_subdirectory(chap23)
# chap24 是嵌入式编程示例 (Qtopia/Qt Extended)，不包含在标准 Qt 构建中
# add_subdirectory(chap24)
add_subdirectory(appendixC)

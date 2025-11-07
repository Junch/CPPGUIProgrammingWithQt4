# Mediaplayer example
cmake_minimum_required(VERSION 3.16)
project(mediaplayer)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    if(WIN32)
        # Windows: 使用 AxContainer (QAxWidget)
        find_package(Qt6 COMPONENTS Widgets AxContainer REQUIRED)
        set(QT_LIBS Qt6::Widgets Qt6::AxContainer)
    else()
        # Linux/macOS: 使用 Multimedia
        find_package(Qt6 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
        set(QT_LIBS Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)
    endif()
else()
    if(WIN32)
        # Windows: 使用 AxContainer (QAxWidget)
        find_package(Qt5 COMPONENTS Widgets AxContainer REQUIRED)
        set(QT_LIBS Qt5::Widgets Qt5::AxContainer)
    else()
        # Linux/macOS: 使用 Multimedia
        find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
        set(QT_LIBS Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
    endif()
endif()

add_executable(mediaplayer
    playerwindow.h
    main.cpp
    playerwindow.cpp
)

target_link_libraries(mediaplayer ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(mediaplayer)
endif()

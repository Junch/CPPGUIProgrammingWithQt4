# Addressbook example
cmake_minimum_required(VERSION 3.16)
project(addressbook)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Windows平台：定义ActiveX服务器所需的宏
if(WIN32)
    add_compile_definitions(
        QAXSERVER      # 必需：ActiveX服务器宏
        Q_OS_WIN       # 确保Qt平台宏被定义
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    if(WIN32)
        # Windows: 需要 AxServer (QAxFactory)
        find_package(Qt6 COMPONENTS Widgets AxServer REQUIRED)
        set(QT_LIBS Qt6::Widgets Qt6::AxServer)
    else()
        find_package(Qt6 COMPONENTS Widgets REQUIRED)
        set(QT_LIBS Qt6::Widgets)
    endif()
else()
    if(WIN32)
        # Windows: 需要 AxServer (QAxFactory)
        find_package(Qt5 COMPONENTS Widgets AxServer REQUIRED)
        set(QT_LIBS Qt5::Widgets Qt5::AxServer)
    else()
        find_package(Qt5 COMPONENTS Widgets REQUIRED)
        set(QT_LIBS Qt5::Widgets)
    endif()
endif()

set(SOURCES
    abitem.h
    addressbook.h
    editdialog.h
    abitem.cpp
    addressbook.cpp
    editdialog.cpp
    main.cpp
    editdialog.ui
)

# Add Windows-specific files
if(WIN32)
    list(APPEND SOURCES qaxserver.rc)
endif()

add_executable(addressbook ${SOURCES})

target_link_libraries(addressbook ${QT_LIBS})
# Windows platform auto-copy Qt runtime libraries
if(WIN32 AND COMMAND deploy_qt_runtime)
    deploy_qt_runtime(addressbook)
endif()

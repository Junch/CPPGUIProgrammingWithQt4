# Bouncer example
cmake_minimum_required(VERSION 3.16)
project(bouncer)

set(CMAKE_AUTOMOC ON)

# 必须在find_package之前设置，确保在所有源文件编译时生效
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
    axbouncer.h
    axbouncer.cpp
    main.cpp
)

# Add Windows-specific files only on Windows
if(WIN32)
    list(APPEND SOURCES
        objectsafetyimpl.h
        objectsafetyimpl.cpp
        qaxserver.rc
    )
endif()

# 创建为共享库（DLL），而不是可执行文件
add_library(bouncer SHARED ${SOURCES})

# 设置输出名称和属性
if(WIN32)
    # 移除之前的重复定义，因为已经在全局定义了
    # ActiveX 服务器需要特定的链接器设置
    set_target_properties(bouncer PROPERTIES
        OUTPUT_NAME "bouncer"
        SUFFIX ".dll"
        ENABLE_EXPORTS ON
    )
    
    # 添加 DEF 文件（如果存在）
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qaxserver.def")
        set_target_properties(bouncer PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/qaxserver.def\""
        )
    endif()
endif()

target_link_libraries(bouncer ${QT_LIBS})

# Windows平台不需要调用deploy_qt_runtime，因为这是一个库而不是可执行文件
# DLL会被其他程序加载使用

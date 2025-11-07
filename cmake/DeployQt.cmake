# DeployQt.cmake - 自动部署Qt运行库到Windows可执行文件目录

# 设置目标为Windows GUI程序（无控制台窗口）
function(set_win32_gui target)
    if(WIN32)
        set_target_properties(${target} PROPERTIES
            WIN32_EXECUTABLE TRUE
        )
        message(STATUS "设置 ${target} 为 Windows GUI 程序（无控制台窗口）")
    endif()
endfunction()

# 在Windows平台自动拷贝Qt运行库DLL
function(deploy_qt_runtime target)
    if(NOT WIN32)
        return()
    endif()
    
    # 自动设置为Windows GUI程序（无控制台窗口）
    set_target_properties(${target} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    
    # 获取Qt的bin目录
    get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    if(NOT _qmake_executable)
        message(WARNING "无法找到qmake，跳过Qt DLL拷贝")
        return()
    endif()
    
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    
    # 基础Qt模块（几乎所有GUI程序都需要）
    set(CORE_DLLS
        Qt${QT_VERSION_MAJOR}Core
        Qt${QT_VERSION_MAJOR}Gui
        Qt${QT_VERSION_MAJOR}Widgets
    )
    
    # 获取目标链接的Qt库，自动检测需要的DLL
    get_target_property(_linked_libs ${target} LINK_LIBRARIES)
    set(QT_DLLS ${CORE_DLLS})
    
    # 不需要拷贝DLL的特殊Qt模块（静态链接或仅头文件）
    set(SKIP_MODULES "AxContainer" "AxServer" "UiTools" "UiPlugin")
    
    if(_linked_libs)
        foreach(_lib ${_linked_libs})
            if(_lib MATCHES "Qt${QT_VERSION_MAJOR}::(.*)")
                set(_module ${CMAKE_MATCH_1})
                # 添加非核心模块，排除不需要DLL的模块
                if(NOT _module MATCHES "^(Core|Gui|Widgets)$")
                    list(FIND SKIP_MODULES "${_module}" _skip_index)
                    if(_skip_index EQUAL -1)
                        list(APPEND QT_DLLS Qt${QT_VERSION_MAJOR}${_module})
                    endif()
                endif()
            endif()
        endforeach()
    endif()
    
    # 去重
    list(REMOVE_DUPLICATES QT_DLLS)
    
    # 拷贝Qt DLL文件
    foreach(_dll ${QT_DLLS})
        # Debug和Release版本的DLL名称不同
        set(_dll_debug "${_dll}d.dll")
        set(_dll_release "${_dll}.dll")
        
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${_qt_bin_dir}/$<IF:$<CONFIG:Debug>,${_dll_debug},${_dll_release}>"
                "$<TARGET_FILE_DIR:${target}>/"
            COMMENT "拷贝 ${_dll}.dll 到 $<TARGET_FILE_DIR:${target}>"
        )
    endforeach()
    
    # 拷贝平台插件 (qwindows.dll 或 qwindowsd.dll)
    set(_platform_plugin_debug "qwindowsd.dll")
    set(_platform_plugin_release "qwindows.dll")
    
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${target}>/platforms"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${_qt_bin_dir}/../plugins/platforms/$<IF:$<CONFIG:Debug>,${_platform_plugin_debug},${_platform_plugin_release}>"
            "$<TARGET_FILE_DIR:${target}>/platforms/"
        COMMENT "拷贝 Qt 平台插件到 $<TARGET_FILE_DIR:${target}>/platforms"
    )
    
    # 如果使用了Qt5，可能还需要拷贝其他依赖
    if(QT_VERSION_MAJOR EQUAL 5)
        # 拷贝ICU库（Qt5在某些配置下需要）
        set(ICU_DLLS
            icudt67
            icuin67
            icuuc67
        )
        foreach(_icu_dll ${ICU_DLLS})
            if(EXISTS "${_qt_bin_dir}/${_icu_dll}.dll")
                add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${_qt_bin_dir}/${_icu_dll}.dll"
                        "$<TARGET_FILE_DIR:${target}>/"
                    COMMENT "拷贝 ICU 库: ${_icu_dll}.dll"
                )
            endif()
        endforeach()
    endif()
    
    message(STATUS "已为 ${target} 配置 Windows GUI 程序（无控制台）+ Qt 运行库自动部署")
endfunction()

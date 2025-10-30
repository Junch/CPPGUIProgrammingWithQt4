#!/usr/bin/env python3
"""
自动从.pro文件生成CMakeLists.txt文件的脚本
"""

import os
import re
from pathlib import Path

def parse_pro_file(pro_file_path):
    """解析.pro文件内容"""
    with open(pro_file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # 提取信息
    template = re.search(r'TEMPLATE\s*=\s*(\w+)', content)
    headers = re.findall(r'HEADERS\s*[+]?=\s*(.+?)(?=\n\S|\nQT|\nSOURCES|\nFORMS|\nRESOURCES|$)', content, re.DOTALL)
    sources = re.findall(r'SOURCES\s*[+]?=\s*(.+?)(?=\n\S|\nQT|\nHEADERS|\nFORMS|\nRESOURCES|$)', content, re.DOTALL)
    forms = re.findall(r'FORMS\s*[+]?=\s*(.+?)(?=\n\S|\nQT|\nHEADERS|\nSOURCES|\nRESOURCES|$)', content, re.DOTALL)
    resources = re.findall(r'RESOURCES\s*[+]?=\s*(.+?)(?=\n\S|\nQT|\nHEADERS|\nSOURCES|\nFORMS|$)', content, re.DOTALL)
    qt_modules = re.findall(r'QT\s*\+?=\s*(.+)', content)
    config = re.findall(r'CONFIG\s*\+?=\s*(.+)', content)
    
    # 清理和分割文件列表
    def clean_files(file_list):
        files = []
        for item in file_list:
            # 移除注释和反斜杠
            item = re.sub(r'#.*', '', item)
            item = item.replace('\\', ' ')
            # 分割并清理
            for f in item.split():
                f = f.strip()
                if f and not f.startswith('#'):
                    files.append(f)
        return files
    
    result = {
        'template': template.group(1) if template else 'app',
        'headers': clean_files(headers),
        'sources': clean_files(sources),
        'forms': clean_files(forms),
        'resources': clean_files(resources),
        'qt_modules': ' '.join(qt_modules).replace('+', '').split() if qt_modules else ['widgets'],
        'config': ' '.join(config).split() if config else [],
    }
    
    return result

def generate_cmake_content(project_name, pro_data, is_plugin=False):
    """生成CMakeLists.txt内容"""
    
    # 获取Qt模块
    qt_modules = pro_data['qt_modules']
    # 转换模块名称（首字母大写）
    qt_components = []
    for mod in qt_modules:
        mod = mod.strip()
        if mod == 'widgets':
            qt_components.append('Widgets')
        elif mod == 'gui':
            qt_components.append('Gui')
        elif mod == 'core':
            qt_components.append('Core')
        elif mod == 'network':
            qt_components.append('Network')
        elif mod == 'xml':
            qt_components.append('Xml')
        elif mod == 'printsupport':
            qt_components.append('PrintSupport')
        elif mod == 'designer':
            qt_components.append('Designer')
        elif mod == 'opengl':
            qt_components.append('OpenGL')
        elif mod == 'sql':
            qt_components.append('Sql')
        elif mod == 'svg':
            qt_components.append('Svg')
        elif mod == 'multimedia':
            qt_components.append('Multimedia')
        elif mod == 'multimediawidgets':
            qt_components.append('MultimediaWidgets')
        elif mod == 'webkit':
            qt_components.append('WebKit')
        elif mod == 'webkitwidgets':
            qt_components.append('WebKitWidgets')
    
    if not qt_components:
        qt_components = ['Widgets']
    
    qt_components = list(set(qt_components))  # 去重
    
    # 设置自动化选项
    auto_options = ['set(CMAKE_AUTOMOC ON)']
    if pro_data['forms']:
        auto_options.append('set(CMAKE_AUTOUIC ON)')
    if pro_data['resources']:
        auto_options.append('set(CMAKE_AUTORCC ON)')
    
    # 收集所有源文件
    all_files = []
    all_files.extend(pro_data['headers'])
    all_files.extend(pro_data['sources'])
    all_files.extend(pro_data['forms'])
    all_files.extend(pro_data['resources'])
    
    # 构建CMake内容
    cmake_content = f"""# {project_name.capitalize()} example
cmake_minimum_required(VERSION 3.16)
project({project_name})

{chr(10).join(auto_options)}

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS {' '.join(qt_components)} REQUIRED)
    set(QT_LIBS {' '.join(['Qt6::' + c for c in qt_components])})
else()
    find_package(Qt5 COMPONENTS {' '.join(qt_components)} REQUIRED)
    set(QT_LIBS {' '.join(['Qt5::' + c for c in qt_components])})
endif()
"""
    
    if is_plugin or 'plugin' in pro_data['config']:
        cmake_content += f"""
add_library({project_name} SHARED
"""
    else:
        cmake_content += f"""
add_executable({project_name}
"""
    
    # 添加文件列表
    for f in all_files:
        cmake_content += f"    {f}\n"
    
    cmake_content += ")\n\n"
    cmake_content += f"target_link_libraries({project_name} ${{QT_LIBS}})\n"
    
    return cmake_content

def process_directory(base_dir):
    """处理目录，为每个包含.pro文件的子目录生成CMakeLists.txt"""
    base_path = Path(base_dir)
    
    # 遍历所有.pro文件
    for pro_file in base_path.rglob('*.pro'):
        # 跳过根目录的examples.pro
        if pro_file.name == 'examples.pro':
            continue
        
        pro_dir = pro_file.parent
        project_name = pro_file.stem
        
        # 检查是否已存在CMakeLists.txt
        cmake_file = pro_dir / 'CMakeLists.txt'
        if cmake_file.exists():
            print(f"跳过 {cmake_file}（已存在）")
            continue
        
        try:
            # 解析.pro文件
            pro_data = parse_pro_file(pro_file)
            
            # 检查是否是插件
            is_plugin = 'plugin' in pro_data['config'] or 'plugin' in project_name.lower()
            
            # 生成CMakeLists.txt内容
            cmake_content = generate_cmake_content(project_name, pro_data, is_plugin)
            
            # 写入文件
            with open(cmake_file, 'w', encoding='utf-8') as f:
                f.write(cmake_content)
            
            print(f"✓ 创建 {cmake_file}")
            
        except Exception as e:
            print(f"✗ 处理 {pro_file} 时出错: {e}")

if __name__ == '__main__':
    import sys
    
    if len(sys.argv) > 1:
        base_dir = sys.argv[1]
    else:
        base_dir = '/Users/jun/github/CPPGUIProgrammingWithQt4'
    
    print(f"处理目录: {base_dir}")
    process_directory(base_dir)
    print("完成！")

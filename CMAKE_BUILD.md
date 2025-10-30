# CMake 构建说明

本项目已添加 CMake 构建支持，可以使用 CMake 替代 qmake 来构建所有示例。

## 系统要求

- CMake 3.16 或更高版本
- Qt5 或 Qt6 开发库
- C++11 兼容的编译器

**重要提示 (macOS)**: 
- **默认使用 x86_64 架构**（适合大多数 Qt 安装，包括 Homebrew）
- 如果您的 Qt 是 arm64 架构（Apple Silicon 原生），请使用: `cmake .. -DCMAKE_OSX_ARCHITECTURES=arm64`
- 可以通过 `file $(which qmake)` 命令检查 Qt 的架构
- CMake 会显示使用的架构

## 构建步骤

### 1. 创建构建目录

```bash
mkdir build
cd build
```

### 2. 配置项目

#### 使用 Qt5:
```bash
cmake ..
```

#### 使用 Qt6:
```bash
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
```

#### macOS 架构选择

默认使用 **x86_64** 架构（适合大多数 Homebrew 或旧版 Qt 安装）。

**如果您的 Qt 是 arm64 架构**（Apple Silicon 原生版本）：
```bash
cmake .. -DCMAKE_OSX_ARCHITECTURES=arm64
```

**如果您的 Qt 是 x86_64 架构**（默认，无需额外参数）：
```bash
cmake ..
```

**通用 x86_64 架构**（在 Apple Silicon 上运行 Rosetta 2）：
```bash
cmake .. -DCMAKE_OSX_ARCHITECTURES=x86_64
```

#### 在 macOS 上指定 Qt 路径示例:
```bash
# Qt5
cmake .. -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@5

# Qt6
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/6.5.0/macos
```

### 3. 编译项目

#### 编译所有示例:
```bash
cmake --build .
```

#### 编译特定示例:
```bash
cmake --build . --target hello
cmake --build . --target spreadsheet_chap03
cmake --build . --target hexspinbox
```

#### 使用多核编译加速:
```bash
cmake --build . -j8
```

### 4. 运行示例

编译完成后，可执行文件位于 `build/bin` 目录：

```bash
./bin/hello
./bin/spreadsheet_chap03
./bin/hexspinbox
```

## 构建单个章节

如果只想构建某个章节的示例，可以进入该章节目录：

```bash
cd chap05
mkdir build
cd build
cmake ..
cmake --build .
```

## 已知问题

1. **插件项目**: 某些设计器插件（如 iconeditorplugin）编译为共享库，需要手动安装到 Qt Designer 插件目录才能使用。

2. **Qt 模块依赖**: 
   - 某些示例需要额外的 Qt 模块（如 Network、Xml、Multimedia 等）
   - 如果缺少模块，CMake 会报错，请安装相应的 Qt 模块

3. **平台特定问题**:
   - **macOS (重要)**: 
     - **默认编译为 x86_64**（通用架构，适合大多数 Qt 安装）
     - 如果您的 Qt 是 Apple Silicon 原生 arm64 版本，使用: `cmake .. -DCMAKE_OSX_ARCHITECTURES=arm64`
     - 检查 Qt 架构: `file /path/to/qt/lib/QtCore.framework/QtCore`
     - 在 Apple Silicon Mac 上，x86_64 程序会通过 Rosetta 2 运行
   - Linux: 可能需要安装额外的开发包（如 libgl-dev）

## 清理构建

删除 build 目录即可：

```bash
rm -rf build
```

## 与 qmake 对比

| 特性 | qmake | CMake |
|------|-------|-------|
| 配置文件 | .pro | CMakeLists.txt |
| Qt 版本 | 单一 | 支持 Qt5/Qt6 |
| IDE 支持 | Qt Creator | Qt Creator, VS Code, CLion 等 |
| 跨平台 | 是 | 是 |
| 现代化 | 较旧 | 现代标准 |

## 项目结构

```
CPPGUIProgrammingWithQt4/
├── CMakeLists.txt              # 主配置文件
├── chap01/
│   ├── CMakeLists.txt          # 章节配置
│   ├── hello/
│   │   ├── CMakeLists.txt      # 项目配置
│   │   └── hello.cpp
│   └── ...
├── chap02/
│   └── ...
└── ...
```

## 贡献

如果发现构建问题或需要改进，请提交 issue 或 pull request。

## 许可证

遵循原项目许可证。

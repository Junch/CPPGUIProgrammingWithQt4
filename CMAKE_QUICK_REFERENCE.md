# CMake 快速参考

## 常用命令

### 配置和构建

```bash
# 标准构建流程
mkdir build && cd build
cmake ..
cmake --build .

# 指定 Qt 路径
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt

# 指定构建类型
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 并行编译
cmake --build . -j8
```

### 编译特定目标

```bash
# 查看所有可用目标
cmake --build . --target help

# 编译单个示例
cmake --build . --target hello
cmake --build . --target find
cmake --build . --target spreadsheet_chap03
```

### 清理

```bash
# 清理构建产物（保留配置）
cmake --build . --target clean

# 完全清理
rm -rf build/
```

## 示例项目列表

### Chapter 01 - 入门
- `age` - 年龄输入示例
- `hello` - Hello World
- `quit` - 退出按钮示例

### Chapter 02 - 对话框
- `find` - 查找对话框
- `gotocell1` - 跳转单元格 v1
- `gotocell2` - 跳转单元格 v2
- `gotocell3` - 跳转单元格 v3
- `sort` - 排序对话框

### Chapter 03-04 - Spreadsheet
- `spreadsheet_chap03` - 电子表格应用 v1
- `spreadsheet_chap04` - 电子表格应用 v2

### Chapter 05 - 自定义部件
- `hexspinbox` - 十六进制旋转框
- `iconeditor` - 图标编辑器
- `iconeditorplugin` - 图标编辑器插件
- `plotter` - 绘图器

### Chapter 06 - 布局管理
- `findfile1` - 查找文件 v1
- `findfile2` - 查找文件 v2
- `findfile3` - 查找文件 v3
- `mailclient` - 邮件客户端
- `mdieditor` - MDI 编辑器
- `preferences` - 偏好设置
- `splitter` - 分割器

### Chapter 07 - 事件处理
- `ticker` - 滚动字幕

### Chapter 08 - 2D 图形
- `cityscape` - 城市景观
- `diagram` - 图表
- `oventimer` - 烤箱定时器

### Chapter 09 - 拖放
- `projectchooser` - 项目选择器

### Chapter 10 - 模型/视图
- `booleanparser` - 布尔解析器
- `cities` - 城市列表
- `colornames` - 颜色名称
- `coordinatesetter` - 坐标设置器
- `currencies` - 货币
- `directoryviewer` - 目录查看器
- `flowchartsymbolpicker` - 流程图符号选择器
- `settingsviewer` - 设置查看器
- `teamleaders` - 团队领导
- `trackeditor` - 轨道编辑器

### Chapter 12 - 输入/输出
- `imageconverter` - 图像转换器
- `imagespace` - 图像空间
- `tidy` - 整理工具

### Chapter 13 - 数据库
- `scooters` - 摩托车
- `staffmanager` - 员工管理器

### Chapter 14 - 多线程
- `imagepro` - 图像处理
- `semaphores` - 信号量
- `threads` - 线程
- `waitconditions` - 等待条件

### Chapter 15 - 网络
- `ftpget` - FTP 下载
- `httpget` - HTTP 下载
- `spider` - 网络爬虫
- `tripplanner` - 旅行规划器
- `tripserver` - 旅行服务器
- `weatherballoon` - 气象气球
- `weatherstation` - 气象站

### Chapter 16 - XML
- `domparser` - DOM 解析器
- `saxhandler` - SAX 处理器
- `xmlstreamreader` - XML 流读取器
- `xmlstreamwriter` - XML 流写入器

### Chapter 19 - 外观
- `bronze_chap19` - 青铜样式
- `candy` - 糖果

### Chapter 20 - 3D 图形
- `teapots` - 茶壶
- `tetrahedron` - 四面体
- `vowelcube` - 元音立方体

### Chapter 21 - 插件
- `basiceffectsplugin` - 基础效果插件
- `bronze_chap21` - 青铜样式插件
- `bronzestyleplugin` - 青铜样式插件
- `cursorplugin` - 光标插件
- `extraeffectsplugin` - 额外效果插件
- `textart` - 文本艺术

### Chapter 22 - 应用脚本
- `calculator` - 计算器
- `gaspump` - 加油泵
- `htmleditor` - HTML 编辑器

### Chapter 23 - 平台特定
- `addressbook` - 地址簿
- `bouncer` - 弹跳球
- `mediaplayer` - 媒体播放器
- `tictactoe` - 井字棋

### Chapter 24 - 嵌入式
- `expenses` - 支出
- `unitconverter` - 单位转换器

## 常见问题

### Qt 找不到？

```bash
# macOS (Homebrew)
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt@5)

# macOS (手动安装)
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/5.15.2/clang_64

# Linux
cmake .. -DCMAKE_PREFIX_PATH=/usr/lib/qt5
```

### 架构不匹配 (macOS)?

确保 Qt 库的架构与系统匹配：
- Apple Silicon (M1/M2): 需要 arm64 Qt
- Intel Mac: 需要 x86_64 Qt

### 缺少 Qt 模块？

安装缺失的模块，例如：

```bash
# Homebrew
brew install qt@5

# Ubuntu/Debian
sudo apt install qtbase5-dev qtmultimedia5-dev qtnetworkauth5-dev
```

### 重新配置

```bash
cd build
rm CMakeCache.txt
cmake ..
```

## 更多信息

详细文档: `CMAKE_BUILD.md`
项目总结: `CMAKE_SUMMARY.md`

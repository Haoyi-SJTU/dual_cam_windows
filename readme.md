# Dual-USB-Camera Capture & Recorder on Windows

A lightweight, efficient C++ application using OpenCV to simultaneously capture video streams from two USB cameras, concatenate the frames side-by-side (split-screen), and record the output to an MP4 file with a dynamically generated timestamped filename. 

This setup is optimized for Windows platforms and is ideal for multi-camera monitoring, stereo vision, or robotic perception tasks.

**Features**
* **Simultaneous Dual Capture**: Reads from two USB cameras simultaneously.
* **Auto-Resolution Alignment**: Forces 640x480 resolution to ensure stable USB bus bandwidth and automatically scales frames if hardware defaults mismatch.
* **Dynamic Timestamp Naming**: Saves recordings as `YYYYMMDDHHMM.mp4` (e.g., `202603082334.mp4`).
* **Hardware-Accelerated GUI**: Leverages Qt6 for the OpenCV highgui backend, providing a robust viewing window.


**Prerequisites**

* **OS**: Windows 10 / 11
* **IDE**: Visual Studio Code (VS Code) with the C/C++ Extension installed.
* **Compiler & Toolchain**: [MSYS2](https://www.msys2.org/) (UCRT64 environment).


## Environment Setup

### 1. Install Dependencies via MSYS2
Open the **MSYS2 UCRT64** terminal (Download in [MSYS2](https://www.msys2.org/) ) and run the following commands to install the GCC compiler, OpenCV, and required Qt6 GUI dependencies:

   ```bash
   # Update package database
   pacman -Syu

   # Install GCC compiler
   pacman -S mingw-w64-ucrt-x86_64-gcc

   # Install OpenCV (includes FFmpeg support for MP4)
   pacman -S mingw-w64-ucrt-x86_64-opencv

   # Install Qt6 Base (required for OpenCV's imshow window)
   pacman -S mingw-w64-ucrt-x86_64-qt6-base
   ```

### 2. Configuration
1. **Configure Windows Environment Variables**

   Press `Win + S` and search for Environment Variables. Edit the system environment variables and find `Path`. Add the following directory to the list:   `C:\msys64\ucrt64\bin`

   Restart VS Code to apply the changes.

2. **VS Code Configuration**
   Create a `.vscode` folder in your project root and add the following tasks `.json` file. 

   - file`.vscode/tasks.json`
   ```json
   {
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe Build OpenCV",
            "command": "C:/msys64/ucrt64/bin/g++.exe",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I", "C:/msys64/ucrt64/include/opencv4",
                "-L", "C:/msys64/ucrt64/lib",
                "-l", "opencv_core",
                "-l", "opencv_highgui",
                "-l", "opencv_imgproc",
                "-l", "opencv_videoio"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Compiler: C:/msys64/ucrt64/bin/g++.exe"
        }
    ]
   }
   ```
   - file`c_cpp_properties.json`
   ```json
   {
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/OpenCV-MinGW/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
   }
   ```
## Run Source Code

1. Open cam.cpp in VS Code.
2. Press `Ctrl + Shift + B` to build the executable.
3. Open a new terminal and run:

   ```Bash
   .\cam.exe
   ```
4. A Qt-based window will appear displaying the live dual-feed.     
   Press `ESC` while the video window is focused to safely stop recording and save the .mp4 file.


# Windows 双USB摄像头采集与录制

一款轻量高效的C++应用程序，基于OpenCV实现同时采集两个USB摄像头的视频流，将帧画面并排拼接（分屏显示），并将输出内容录制为MP4文件，文件名由时间戳动态生成。该工具针对Windows平台优化，适用于多摄像头监控、立体视觉或机器人感知等场景。

## 特性
* **双摄像头同步采集**：同时读取两个USB摄像头的视频流。
* **分辨率自动对齐**：强制采用640x480分辨率以保证USB总线带宽稳定，若硬件默认分辨率不匹配则自动缩放帧画面。
* **时间戳动态命名**：录制文件命名格式为`YYYYMMDDHHMM.mp4`（例如：`202603082334.mp4`）。
* **硬件加速GUI**：借助Qt6作为OpenCV highgui后端，提供稳定的视频预览窗口。

## 前置条件

* **操作系统**：Windows 10 / 11
* **集成开发环境**：Visual Studio Code (VS Code)，需安装C/C++扩展。
* **编译器与工具链**：[MSYS2](https://www.msys2.org/)（UCRT64环境）。

## 环境配置

### 1. 通过MSYS2安装依赖
打开**MSYS2 UCRT64**终端（[下载MSYS2](https://www.msys2.org/)），执行以下命令安装GCC编译器、OpenCV及所需的Qt6 GUI依赖：

```bash
# 更新软件包数据库
pacman -Syu

# 安装GCC编译器
pacman -S mingw-w64-ucrt-x86_64-gcc

# 安装OpenCV（包含FFmpeg支持，用于MP4编码）
pacman -S mingw-w64-ucrt-x86_64-opencv

# 安装Qt6基础库（OpenCV的imshow窗口依赖）
pacman -S mingw-w64-ucrt-x86_64-qt6-base
```
### 2. 参数配置
1. **配置windows环境变量**

   按下`Win + S`，搜索`环境变量`。编辑系统环境变量，找到`Path`变量，将以下目录添加到列表中：`C:\msys64\ucrt64\bin`
   重启 VS Code 使配置生效。

2. **VS Code Configuration**
   在项目根目录创建`.vscode`文件夹，添加配置文件：

   - file`.vscode/tasks.json`
   ```json
   {
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe Build OpenCV",
            "command": "C:/msys64/ucrt64/bin/g++.exe",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I", "C:/msys64/ucrt64/include/opencv4",
                "-L", "C:/msys64/ucrt64/lib",
                "-l", "opencv_core",
                "-l", "opencv_highgui",
                "-l", "opencv_imgproc",
                "-l", "opencv_videoio"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Compiler: C:/msys64/ucrt64/bin/g++.exe"
        }
    ]
   }
   ```
   - 文件`c_cpp_properties.json`
  
   ```json
   {
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/OpenCV-MinGW/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
   }
   ```
## 运行

1. 在 VS Code 中打开 cam.cpp 。
2. `Ctrl + Shift + B`编译。
3. 打开新终端，执行以下命令：

   ```Bash
   .\cam.exe
   ```
4. 此时会弹出基于 Qt 的窗口，显示双摄像头实时画面。在视频窗口处于激活状态时，按下`ESC`键可安全停止录制并保存 MP4 文件。
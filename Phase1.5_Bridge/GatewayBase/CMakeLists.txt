# 1. 声明最低要求的 CMake 版本和你的项目名称
cmake_minimum_required(VERSION 3.10)
project(GatewayBase)

# 2. 厂长指令：把 src 目录下的 main.cpp 编译成一个叫 gateway_app 的程序
add_executable(gateway_app src/main.cpp)

# 3. 厂长指令：告诉编译器去 include 文件夹里找头文件（虽然今天还没用到，但这是标准护城河）
target_include_directories(gateway_app PUBLIC include)
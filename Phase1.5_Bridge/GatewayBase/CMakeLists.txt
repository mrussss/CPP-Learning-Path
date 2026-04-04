# 1. 声明最低要求的 CMake 版本和你的项目名称
cmake_minimum_required(VERSION 3.10)
project(GatewayBase)

# ✅ 第一步：查找系统线程库（Linux 下自动找到 pthread）
find_package(Threads REQUIRED)

# 2. 编译目标
add_executable(server_out src/server_epoll.cpp)

# 3. 头文件、编译、链接配置
target_include_directories(server_out PUBLIC include)
target_compile_options(server_out PRIVATE -O0 -g -fsanitize=address)
# ✅ 第二步：链接 CMake 封装的跨平台线程目标 Threads::Threads
target_link_libraries(server_out PRIVATE -fsanitize=address Threads::Threads)
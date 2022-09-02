#指定 CMake 最低版本号
cmake_minimum_required(VERSION 3.20)
#项目名字
project(500001)
#启用保留文件结构和资源管理器一样
option(GROUP_BY_EXPLORER ON)
# 设置C++版本 20
set(CMAKE_CXX_STANDARD 20)
# 头文件目录
include_directories(D:/__SVN__/Memade/include/)

add_library(D:/__SVN__/Memade/projects/bridge/objects/500001/500001.def)


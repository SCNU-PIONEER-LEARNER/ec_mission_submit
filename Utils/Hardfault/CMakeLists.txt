cmake_minimum_required(VERSION 3.22)

project(Utils)

enable_language(C CXX ASM)



# file(GLOB_RECURSE UserCodes_Src ${CMAKE_SOURCE_DIR}/UserCodes/*.cpp)

# 设置源文件
set(UserCodes_Src
    ${CMAKE_SOURCE_DIR}/UserCodes/Hardfault.cpp
)

# 创建静态库
add_library(usercodes STATIC ${UserCodes_Src})



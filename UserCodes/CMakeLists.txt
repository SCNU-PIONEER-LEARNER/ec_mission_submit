cmake_minimum_required(VERSION 3.22)

project(UserCodes)

enable_language(C CXX ASM)

file(GLOB_RECURSE all_dirs 
    LIST_DIRECTORIES true
    ${CMAKE_SOURCE_DIR}/UserCodes/*
)

set(header_dirs)
foreach(dir ${all_dirs})
    if(IS_DIRECTORY ${dir})
        list(APPEND header_dirs ${dir})
    endif()
endforeach()

set(UserCodes_Inc ${header_dirs})

file(GLOB_RECURSE UserCodes_Src 
    ${CMAKE_SOURCE_DIR}/UserCodes/*.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/*.c
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_atan2_f32.c
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Source/MatrixFunctions/*.c
)

# 创建静态库
add_library(usercodes STATIC ${UserCodes_Src})

# 设置头文件包含目录
target_include_directories(usercodes PUBLIC
    ${UserCodes_Inc}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 添加 STM32 相关的包含路径
target_include_directories(usercodes PUBLIC
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Include
)

target_link_directories(usercodes PUBLIC
                        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/DSP/Include)

# 添加编译定义
target_compile_definitions(usercodes PUBLIC
    USE_HAL_DRIVER
    STM32F4xx
)

# 链接 STM32CubeMX 库
target_link_libraries(usercodes PUBLIC stm32cubemx)

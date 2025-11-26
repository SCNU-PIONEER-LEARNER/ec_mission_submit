cmake_minimum_required(VERSION 3.22)

project(UserCodes)

enable_language(C CXX ASM)

# 设置头文件目录
set(UserCodes_Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/App
    ${CMAKE_CURRENT_SOURCE_DIR}/Bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/LED
    ${CMAKE_CURRENT_SOURCE_DIR}/Motors
    ${CMAKE_CURRENT_SOURCE_DIR}/DM-IMU
    ${CMAKE_CURRENT_SOURCE_DIR}/PID
    ${CMAKE_CURRENT_SOURCE_DIR}/CommenMarcros
)

# file(GLOB_RECURSE UserCodes_Src ${CMAKE_SOURCE_DIR}/UserCodes/*.cpp)

# 设置源文件
set(UserCodes_Src
    ${CMAKE_SOURCE_DIR}/UserCodes/App/App.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/Bsp/BspCan.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/Motors/Motors.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/DM-IMU/DmImu.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/CanMotors.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/PID/Pid.cpp
    ${CMAKE_SOURCE_DIR}/UserCodes/CommenMarcros/CalcuNeed.cpp
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
)

# 添加编译定义
target_compile_definitions(usercodes PUBLIC
    USE_HAL_DRIVER
    STM32F4xx
)

# 链接 STM32CubeMX 库
target_link_libraries(usercodes PUBLIC stm32cubemx)

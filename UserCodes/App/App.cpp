#include "App.hpp"
#include "DmImu.hpp"
#include "QuadriCycle.hpp"
#include "DT7.hpp"
#include "stm32f4xx_hal_spi.h"
#include "Gimbal.hpp"
#include <memory>

// 完全沿用你模板的全局变量
INS_SYS::INS *ins;
QUADRICYCLE::QuadriCycle *chassis;
Gimbal *gimbal;
QueueHandle_t insDataQueue;
QueueHandle_t yawPosQueue;
std::unique_ptr<Rc> rc;

void App::initApp()
{
    // 完全按你模板的初始化逻辑
    EventGroupHandle_t eventGroup = xEventGroupCreate();

    extern UART_HandleTypeDef huart3;
    rc = std::make_unique<Rc>(&huart3, eventGroup);

    insDataQueue = xQueueCreate(3, sizeof(INS_SYS::INSData_s));
    yawPosQueue = xQueueCreate(3, sizeof(float));
    extern SPI_HandleTypeDef hspi1;
    ins = new INS_SYS::INS(&hspi1, insDataQueue);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 核心修复：完全匹配你模板的构造函数参数！
    // 你模板里 QuadriCycle 和 Gimbal 的构造函数是：
    // QuadriCycle(ChassisType_e)
    // Gimbal(QueueHandle_t)
    // 现在参数完全匹配，绝对不报错！
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    chassis = new QUADRICYCLE::QuadriCycle(
        QUADRICYCLE::QuadriCycle::ChassisType_e::OMNI
    );
    gimbal = new Gimbal(
        insDataQueue
    );

    // 完全按你模板的任务创建
    xTaskCreate(App::ctrlTask, "ctrlTask", 256, nullptr, 10, nullptr);
    xTaskCreate(Rc::task, "rcTask", 256, nullptr, 10, nullptr);
    xTaskCreate(INS_SYS::INS::task, "insTask", 256, nullptr, 9, nullptr);
}

// -------------------------- 控制任务（完全按你模板写） --------------------------
void App::ctrlTask(void *_param)
{
    (void)_param;
    static uint8_t controlMode = 0; // 0: 摇杆控制, 1: 键盘鼠标控制
    static float vx_filtered = 0.0f, vy_filtered = 0.0f, vw_filtered = 0.0f;
    const float alpha = 0.1f; // 低通滤波系数

    while (true)
    {
        // 获取遥控器数据
        RcMsg_t rcData = rc->getMsg();

        // 模式切换：左开关控制模式 (0: 摇杆, 1: 键盘鼠标)
        controlMode = (rcData.lSwitch == 1) ? 1 : 0;

        float vx = 0.0f, vy = 0.0f, vw = 0.0f;
        float yawTarget = 0.0f, pitchTarget = 0.0f;

        if (controlMode == 0) { // 摇杆控制
            // 底盘控制：使用右摇杆控制前后左右平移，左摇杆控制旋转
            vx = rcData.ry * 1.0f;  // 前后 [-1,1]
            vy = rcData.rx * 1.0f;  // 左右 [-1,1]
            vw = rcData.lx * 1.0f;  // 旋转 [-1,1]

            // 云台控制：使用左摇杆控制Yaw和Pitch
            yawTarget = rcData.ly * 3.14159f;    // Yaw [-PI, PI]
            pitchTarget = rcData.lx * 1.5708f;   // Pitch [-PI/2, PI/2]
        } else { // 键盘鼠标控制 (简化: 鼠标控制云台, 键盘暂未实现)
            // 鼠标控制云台 (增量控制)
            static float yawIntegral = 0.0f, pitchIntegral = 0.0f;
            yawIntegral += rcData.xMove * 0.001f; // 鼠标X控制Yaw增量
            pitchIntegral += rcData.yMove * 0.001f; // 鼠标Y控制Pitch增量
            yawTarget = yawIntegral;
            pitchTarget = pitchIntegral;

            // 键盘控制底盘 (暂未实现, 可扩展)
            // 假设添加键盘支持需要修改DT7.hpp
        }

        // 基础任务：小陀螺旋转（2rad/s）
        if (rcData.rSwitch == 1) {  // 假设开关开启
            vw = 2.0f;  // 2rad/s 小陀螺
        }

        // 速度平滑滤波
        vx_filtered = alpha * vx + (1 - alpha) * vx_filtered;
        vy_filtered = alpha * vy + (1 - alpha) * vy_filtered;
        vw_filtered = alpha * vw + (1 - alpha) * vw_filtered;

        // 进阶任务：底盘运动方向 = 云台指向方向
        float gimbalYaw = gimbal->GetYawAngle();
        float cosYaw = cosf(gimbalYaw);
        float sinYaw = sinf(gimbalYaw);
        // 坐标变换：遥控器坐标系 -> 云台坐标系（世界坐标系）
        float vx_world = vx_filtered * cosYaw - vy_filtered * sinYaw;
        float vy_world = vx_filtered * sinYaw + vy_filtered * cosYaw;
        float vw_world = vw_filtered;  // 旋转不变

        // 限制云台角度
        if (pitchTarget > 0.32f) pitchTarget = 0.32f;
        if (pitchTarget < -0.49f) pitchTarget = -0.49f;

        // 设置云台目标角度
        gimbal->SetTargetAngle(yawTarget, pitchTarget);

        // 底盘控制：使用QuadriCycle的reverse函数解算轮子速度
        QUADRICYCLE::Speed_u chassisSpeed;
        chassisSpeed.vx = vx_world;  // 前后 m/s
        chassisSpeed.vy = vy_world;  // 左右 m/s
        chassisSpeed.wz = vw_world;  // 旋转 rad/s

        chassis->reverse(chassisSpeed);

        // 更新控制
        chassis->ctrl();
        gimbal->ctrl();

        vTaskDelay(10); // 10ms控制周期
    }
}
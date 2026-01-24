#include "App.hpp"
#include "DmImu.hpp"
#include "QuadriCycle.hpp"
#include "DT7.hpp"
#include "stm32f4xx_hal_spi.h"
#include <memory>
#include "Gimbal.hpp"

INS_SYS::INS *ins;
QUADRICYCLE::QuadriCycle *chassis;
Gimbal *gimbal;
QueueHandle_t insDataQueue;
QueueHandle_t yawPosQueue;
void App::initApp()
{
    EventGroupHandle_t eventGroup = xEventGroupCreate();

    extern UART_HandleTypeDef huart3;
    rc = std::make_unique<Rc>(&huart3, eventGroup);

    insDataQueue = xQueueCreate(3, sizeof(INS_SYS::INSData_s));
    yawPosQueue = xQueueCreate(3, sizeof(float));
    extern SPI_HandleTypeDef hspi1;
    ins = new INS_SYS::INS(&hspi1, insDataQueue);

    // chassis = new QUADRICYCLE::QuadriCycle(
    //         QUADRICYCLE::QuadriCycle::ChassisType_e::MENUCAM, yawPosQueue);
    chassis = new QUADRICYCLE::QuadriCycle(
            QUADRICYCLE::QuadriCycle::ChassisType_e::OMNI, yawPosQueue);

    gimbal = new Gimbal(insDataQueue, yawPosQueue);

    xTaskCreate(App::ctrlTask, "ctrlTask", 256, nullptr, 10, nullptr);
    xTaskCreate(Rc::task, "rcTask", 256, nullptr, 10, nullptr);
}

void App::ctrlTask(void *_param)
{
    while (true) {
        chassis->ctrl();
        gimbal->ctrl();
        vTaskDelay(1);
    }
}

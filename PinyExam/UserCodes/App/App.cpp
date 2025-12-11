#include "App.hpp"
#include "DT7.hpp"
#include "Gimbal.hpp"
#include "QuadriCycle.hpp"
#include "stm32f4xx_hal_spi.h"
#include <memory>

INS_SYS::INS *ins;
QueueHandle_t insDataQueue;
void App::initApp()
{
    EventGroupHandle_t eventGroup = xEventGroupCreate();

    extern UART_HandleTypeDef huart3;
    rc = std::make_unique<Rc>(&huart3, eventGroup);

    insDataQueue = xQueueCreate(3, sizeof(INS_SYS::INSData_s));
    extern SPI_HandleTypeDef hspi1;
    ins = new INS_SYS::INS(&hspi1, insDataQueue);

    xTaskCreate(Rc::task, "rcTask", 256, nullptr, 10, nullptr);
}

#include "LEDController.hpp"

#include "main.h"

auto &controller = LEDController::instance();

void createCtrlTask() { controller.createTask(); }

LEDController::LEDController() { queue = xQueueCreate(10, sizeof(uint16_t)); }

void LEDController::task() {
  while (true) {
    if (xQueueReceive(queue, &period_, 0) == pdTRUE) {
    }
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    vTaskDelay(pdMS_TO_TICKS(period_ / 2));
  }
}

void LEDController::createTask() {
  xTaskCreate([](void *) { controller.task(); }, "LEDCtrl", 256, nullptr,
              24, nullptr);
}

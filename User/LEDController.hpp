#pragma once

#include "FreeRTOS.h"
#include "queue.h"

#ifdef __cplusplus
extern "C" {
#endif

void createCtrlTask();

#ifdef __cplusplus
}

class LEDController {
public:
  static LEDController &instance() {
    static LEDController instance;
    return instance;
  }

  void createTask();

  QueueHandle_t queue;

private:
  LEDController(const LEDController &) = delete;
  LEDController &operator=(const LEDController &) = delete;
  LEDController();

  void task();

  uint16_t period_ = 2000; // ms
};

#endif

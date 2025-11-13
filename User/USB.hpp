#pragma once

#include "FreeRTOS.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

void usbReceive(uint8_t *_data, uint16_t _length);

void createUsbTask();

#ifdef __cplusplus
}

#include <cstdint>

class USB {
  static constexpr uint16_t BUF_SIZE = 10;

public:
  static USB &instance() {
    static USB instance;
    return instance;
  }

  void receive(uint8_t *_data, uint16_t _length);

  void createTask();

private:
  USB(const USB &) = delete;
  USB &operator=(const USB &) = delete;
  USB();

  void process(void);

  SemaphoreHandle_t semphr_;

  uint8_t buf_[BUF_SIZE];
  uint16_t len_;
};

#endif
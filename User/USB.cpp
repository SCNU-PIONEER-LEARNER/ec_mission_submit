#include "USB.hpp"

#include <cctype>
#include <string.h>

#include "LEDController.hpp"

auto &usb = USB::instance();

void usbReceive(uint8_t *_data, uint16_t _length) {
  usb.receive(_data, _length);
}

void createUsbTask() { usb.createTask(); }

USB::USB() : semphr_(xSemaphoreCreateBinary()) {}

void USB::receive(uint8_t *_data, uint16_t _length) {
  len_ = _length;
  memcpy(buf_, _data, len_);
  xSemaphoreGiveFromISR(semphr_, nullptr);
}

void USB::process() {
  while (true) {
    if (xSemaphoreTake(semphr_, portMAX_DELAY) == pdTRUE) {
      uint16_t result = 0;
      for (uint16_t i = 0; i < len_; i++) {
        if (isdigit(buf_[i])) {
          result = result * 10 + (buf_[i] - '0');
        }
      }
      xQueueSend(LEDController::instance().queue, &result, 0);
    }
  }
}

void USB::createTask() {
  xTaskCreate([](void *) { usb.process(); }, "USBProc", 256, nullptr, 25,
              nullptr);
}

#pragma once

#include "can.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"

class BspCan {
public:
  static BspCan &instance() {
    static BspCan instance;
    return instance;
  }

  void init(CAN_HandleTypeDef *_hcan);

  HAL_StatusTypeDef transmitData(CAN_HandleTypeDef *_hcan, uint16_t _stdid,
                                 uint8_t *_txData, uint32_t _len);

  HAL_StatusTypeDef canFilterInit(CAN_HandleTypeDef *_hcan, uint32_t _fifo);

  void callbackFromISR(CAN_HandleTypeDef *_hcan, uint32_t _rxFifo);

  uint32_t _stdid;
  uint8_t rxBuffer1[8];
  uint8_t rxBuffer2[8];

protected:
  uint8_t rxData[8];
  BspCan(const BspCan &);
  BspCan &operator=(const BspCan &);
  BspCan();
};

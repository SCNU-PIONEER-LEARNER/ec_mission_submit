#pragma once

#include "can.h"
#include "stm32f4xx_hal.h"

#include <array>
#include <functional>

class BspCan {
public:
    static BspCan &instance()
    {
        static BspCan instance;
        return instance;
    }

    void init(CAN_HandleTypeDef *_hcan);

    HAL_StatusTypeDef transmitData(CAN_HandleTypeDef *_hcan, uint16_t _stdid,
                                   uint8_t *_txData, uint32_t _len);


    HAL_StatusTypeDef canFilterInit(CAN_HandleTypeDef *_hcan, uint32_t _fifo);

    HAL_StatusTypeDef registerCallback(CAN_HandleTypeDef *_hcan, uint32_t _stdid,
                                       std::function<void(const uint8_t *)> _pCallback);

    void callbackFromISR(CAN_HandleTypeDef *_hcan, uint32_t _rxFifo);

    uint32_t _stdid;

private:
    uint8_t rxData[8] = {};
    BspCan(const BspCan &);
    BspCan &operator=(const BspCan &);
    BspCan() = default;

    struct Handler_s {
        uint32_t stdid;
        std::function<void(const uint8_t *)> func;
    };

    uint8_t can1cnt = 0;
    std::array<Handler_s, 10> cbTable1;
    uint8_t can2cnt = 0;
    std::array<Handler_s, 10> cbTable2;
};

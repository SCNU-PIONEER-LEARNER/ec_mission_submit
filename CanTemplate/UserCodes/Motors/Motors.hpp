#pragma once

#include "stm32f4xx_hal.h"
#include <cstdint>

namespace MOTORS {

typedef struct {
    uint16_t angle; // abs angle range:[0,8191]
    int16_t speed;
    int16_t torqueCurrent;
    uint8_t temp;
} Data_s;


class Motors {
public:
    static constexpr uint16_t MOTOR_MAX_NUM = 4; // 电机数量

    /**
 * @param _motorID    电机当前ID
 * @param _feedbackId 电机反馈数据的ID基地址
 * @param _sendId     给电机发送数据的标识符
 */
    Motors(uint16_t _motorID, uint16_t _feedbackId, uint16_t _sendId);

    void sendData(uint8_t *_data);
    void getData();

    Data_s _datas;

private:
    uint16_t _canCnt;
    uint8_t rxData[8];
    uint16_t _id;
    uint16_t _feedbackIdBase;
    uint16_t _identifier;
};
} // namespace MOTORS

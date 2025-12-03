#pragma once

#include "stm32f4xx_hal.h"
#include <cstdint>

namespace DM_IMU {


typedef struct ImuData_s {
    struct {
        float ax = 0.0f, ay = 0.0f, az = 0.0f; // acceleration
        float gx = 0.0f, gy = 0.0f, gz = 0.0f; // gyro
    } body;
    float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
} ImuData_s;


class DmImu {
public:
    /**
     * @param hcan        Pointer to the CAN handle (e.g., &hcan1)
     * @param id          IMU's logical ID
     * @param feedbackId  CAN ID for receiving IMU data
     * @param sendId      CAN ID for sending requests to IMU
     */
    DmImu(CAN_HandleTypeDef *_hcan, uint16_t _id, uint16_t _feedbackId,
          uint16_t _sendId);

    void sendRequest(uint8_t _reg);
    void getData();

    ImuData_s _datas;

private:
    CAN_HandleTypeDef *_hcan;
    uint8_t rxData[8];
    uint16_t _id;
    uint16_t _feedbackId;
    uint16_t _sendId;
};

} // namespace DM_IMU

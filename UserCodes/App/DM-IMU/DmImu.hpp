#pragma once
#include "BspCan.hpp"
#include "DmImu.hpp"
#include "FreeRTOS.h"
#include "queue.h"
#include <cstdint>

namespace DM_IMU {
#define ACC_REG   0x01
#define GYRO_REG  0x02
#define EULAR_REG 0x03

typedef struct ImuData_s {
    struct {
        float ax = 0.0f, ay = 0.0f, az = 0.0f; // acceleration
        float gx = 0.0f, gy = 0.0f, gz = 0.0f; // gyro
    } body;
    float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
} ImuData_s;

class DmImu {
    static constexpr float F_PI = std::numbers::pi_v<float>;

    static constexpr float ACCEL_CAN_MAX = 58.8f;
    static constexpr float ACCEL_CAN_MIN = -58.8f;
    static constexpr float GYRO_CAN_MAX = 34.88f;
    static constexpr float GYRO_CAN_MIN = -34.88f;

    static constexpr float PITCH_CAN_MAX = F_PI / 2.0f;
    static constexpr float PITCH_CAN_MIN = -F_PI / 2.0f;
    static constexpr float ROLL_CAN_MAX = F_PI;
    static constexpr float ROLL_CAN_MIN = -F_PI;
    static constexpr float YAW_CAN_MAX = F_PI;
    static constexpr float YAW_CAN_MIN = -F_PI;

public:
    DmImu(uint16_t _canId, uint16_t _txId, uint16_t _rxId);

    void sendRequest(uint8_t _reg);
    void getData();

    ImuData_s datas;

private:
    uint8_t rxData[8];
    uint16_t canId;
    uint16_t txId;
    uint16_t rxId;

    QueueHandle_t rxQueue;
};

} // namespace DM_IMU

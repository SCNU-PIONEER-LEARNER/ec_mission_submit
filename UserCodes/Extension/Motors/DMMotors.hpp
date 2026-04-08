#pragma once
#include "BspCan.hpp"
#include "FreeRTOS.h"
#include "queue.h"
#include <cstdint>

#define PI std::numbers::pi_v<float>
namespace DMMOTORS {

enum class DMMotorType_e : uint8_t {
    DM4310 = 1,
    DM4340 = 2,
};

enum class ErrorCode_e : uint8_t {
    MOTOR_DISABLE = 0x0u,
    MOTOR_ENABLE = 0x1u,
    OVER_VOLTAGE = 0x8u,
    LOW_VOLTAGE = 0x9u,
    OVER_CURRENT = 0xAu,
    MOS_OVER_HEAT = 0xBu,
    ROTOR_OVER_HEAT = 0xCu,
    COMMUNICATION_LOSS = 0xDu,
    OVERLOAD = 0xEu,
};

typedef struct {
    CAN_HandleTypeDef *_hcan;
    uint16_t _offsetId;
    DMMotorType_e motorType;
} DMMotorInit_s;

typedef struct {
    uint16_t angle : 16;
    uint16_t speed : 12;
    uint16_t Kp : 12;
    uint16_t Kd : 12;
    uint16_t torque : 12;
} MITData_s;

typedef struct {
    float angle;
    float speed;
    float Kp;
    float Kd;
    float torque;
} CmdData_s;

typedef struct {
    uint8_t ID : 4;
    ErrorCode_e errorCode : 4;
    uint16_t angle : 16;
    uint16_t speed : 12;
    uint16_t torque : 12;
    uint8_t mosTemperature : 8;
    uint8_t rotorTemperature : 8;
} rxData_s;

typedef struct {
    uint8_t ID;
    ErrorCode_e errorCode;
    float angle;
    float speed;
    uint8_t mosTemperature;
    uint8_t rotorTemperature;
} realData_s;

class DMMotors {
public:
    DMMotors(DMMotorInit_s _motorInit);

    void cmd(float _cmd);
    void praseData();

    MITData_s _mitDatas;
    rxData_s _datas;
    realData_s _realDatas; // 实际数据

private:
    uint8_t rxData_[8];
    uint16_t txId = 0x00;
    uint16_t rxBaseId = 0x10;
    uint16_t offsetId;
    CAN_HandleTypeDef *hcan;

    QueueHandle_t rxQueue;
};
} // namespace DMMOTORS

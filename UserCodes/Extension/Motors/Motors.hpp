#pragma once
#include "BspCan.hpp"
#include "FreeRTOS.h"
#include "queue.h"
#include <cstdint>
#include <unordered_map>

#define PI std::numbers::pi_v<float>
namespace MOTORS {

enum class MotorType_e : uint8_t {
    GM6020 = 0,
    M3508 = 1,
};

typedef struct {
    uint16_t _txId;
    uint16_t _rxBaseId;
    uint16_t _offsetId;
    CAN_HandleTypeDef *_hcan;
    MotorType_e motorType;
} MotorInit_s;

typedef struct {
    uint16_t angle; // abs angle range:[0,8191]
    int16_t speed;
    int16_t torqueCurrent;
    uint8_t temp;
} Data_s;

typedef struct {
    float angle;
    float speed;
    int16_t torqueCurrent;
    uint8_t temp;
} realData_s;

class Motors;
typedef struct {
  Motors *motorsGroup[4];
  uint8_t sendLoad;
  uint8_t sendMask;
  uint8_t txData[8] ={};
} MotorsGroup_s;

class Motors {
public:
    Motors(MotorInit_s _motorInit);

    void cmd(float _cmd);
    void praseData();
    void updateMap();

    Data_s _datas;
    realData_s _realDatas; // 实际数据

private:
    uint8_t rxData_[8];
    uint16_t txId;
    uint16_t rxBaseId;
    uint16_t offsetId;
    float reductionRatio = 1.0f;
    CAN_HandleTypeDef *hcan;

    QueueHandle_t rxQueue;

    float currCodeSpan = 0;
};
} // namespace MOTORS

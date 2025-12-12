#include "Motors.hpp"
#include "BspCan.hpp"
#include "LED.hpp"
#include "stm32f4xx_hal_gpio.h"
#include <cstring>
#include <cstdint>

// 简单一阶低通滤波参数
static float g_speedFiltered[MOTORS::Motors::MOTOR_MAX_NUM] = {0};
static constexpr float SPEED_FILTER_ALPHA = 0.2f; // 越小滤波越强

using namespace MOTORS;

Motors::Motors(uint16_t _motorID, uint16_t _feedbackId, uint16_t _sendId)
        : _canCnt(0)
        , _id(_motorID)
        , _feedbackIdBase(_feedbackId)
        , _identifier(_sendId)
{
    memset(rxData, 0, sizeof(rxData));
}

void Motors::sendData(uint8_t *_data)
{
    BspCan::instance().transmitData(&hcan1, _identifier, _data, 8);
}

void Motors::getData()
{
    memcpy(rxData, BspCan::instance().rxBuffer1, 8);
    uint16_t stdid = BspCan::instance()._stdid;
    uint8_t index = stdid - _feedbackIdBase; // get motor index by can_id
    if (index == _id) {
        _canCnt++;
        _datas.angle = ((rxData[0] << 8) | rxData[1]);
        _datas.speed = static_cast<int16_t>(
                (static_cast<uint16_t>((rxData[2] << 8) | rxData[3])));
        _datas.torqueCurrent = static_cast<int16_t>(
                (static_cast<uint16_t>((rxData[4] << 8) | rxData[5])));
        _datas.temp = rxData[6];
    }

    if (_canCnt == 500) {
        _canCnt = 0;
        switch (_id) {
        case 1:
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        case 2:
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            break;
        case 3:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
        case 4:
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
        default:
            break;
        }
    }
    _realDatas.angle = (float)((float)_datas.angle / 8192.0f * 2 *
                               M_PI); // abs angle range:[0,2PI]
    float rawSpeed = (float)_datas.speed / 8192.0f * 320.f; // rad/s

    // 对每个电机使用简单一阶低通滤波器，减少速度噪声
    if (_id < MOTORS::Motors::MOTOR_MAX_NUM) {
        g_speedFiltered[_id] = SPEED_FILTER_ALPHA * g_speedFiltered[_id] +
                                (1.0f - SPEED_FILTER_ALPHA) * rawSpeed;
        _realDatas.speed = g_speedFiltered[_id];
    } else {
        _realDatas.speed = rawSpeed;
    }
}

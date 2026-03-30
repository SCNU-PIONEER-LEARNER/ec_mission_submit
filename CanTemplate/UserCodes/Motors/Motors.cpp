#include "Motors.hpp"
#include "BspCan.hpp"
#include "LED.hpp"
#include "stm32f4xx_hal_gpio.h"
#include <cstdint>
#include <cstring>

using namespace MOTORS;

// 电机类构造函数，初始化电机ID，反馈ID基地址，发送ID
Motors::Motors(uint16_t _motorID, uint16_t _feedbackId, uint16_t _sendId)
    : _canCnt(0), _id(_motorID),    // 电机ID
      _feedbackIdBase(_feedbackId), // 电机反馈数据的ID基地址
      _identifier(_sendId)          // 给电机发送数据的标识符
{
  memset(rxData, 0, sizeof(rxData));
}

// 发送控制数据给电机
void Motors::sendData(uint8_t *_data) {
  BspCan::instance().transmitData(&hcan1, _identifier, _data, 8);
}

// 接收电机反馈数据
void Motors::getData() {
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
}


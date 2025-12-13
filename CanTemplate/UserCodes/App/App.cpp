#include "App.hpp"
#include "DmImu.hpp"
#include "Motors.hpp"
#include "can.h"
#include <cstdint>

MOTORS::Motors *motor;
DM_IMU::DmImu *dmImu;

uint16_t current = 0; // 0 - 65535
uint8_t data[8];

// add 初始化电机
void App::initApp() 
{
  motor = new MOTORS::Motors(1, 0x204, 0x1FE);  // 电机id配置（电机，反馈值，接受值）
  dmImu = new DM_IMU::DmImu(&hcan1, 1, 0x10, 0x6FF); // imu id配置（can句柄，逻辑id，反馈id，发送id）  
}

void App::sendCanData() {
  data[0] = current >> 8;
  data[1] = current;
  data[2] = current >> 8;
  data[3] = current;
  data[4] = current >> 8;
  data[5] = current;
  data[6] = current >> 8;
  data[7] = current;
  if (motor != nullptr) {
    motor->sendData(data);
  }
  if (dmImu != nullptr) {
    dmImu->sendRequest(0x01);
  }
}

void App::getCanData() {
  if (motor != nullptr) {
    motor->getData();
  }
  if (dmImu != nullptr) {
    dmImu->getData();
  }
}


void sendCanData() { App::instance()->sendCanData(); }

void getCanData() { App::instance()->getCanData(); }

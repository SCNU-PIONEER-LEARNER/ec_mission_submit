#include "App.hpp"
#include "DmImu.hpp"
#include "Motors.hpp"
#include <cstdint>

MOTORS::Motors *motor;
DM_IMU::DmImu *dmImu;

uint16_t current = 0; // 0 - 65535
uint8_t data[8];
void App::initApp() {
  // motor = new MOTORS::Motors();
  // dmImu = new DM_IMU::DmImu();
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
  // if (dmImu != nullptr) {
  //   dmImu->sendRequest();
  // }
}

void App::getCanData() {
  if (motor != nullptr) {
    motor->getData();
  }
  // if (dmImu != nullptr) {
  //   dmImu->getData();
  // }
}

void sendCanData() { App::instance()->sendCanData(); }

void getCanData() { App::instance()->getCanData(); }

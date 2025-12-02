#include "App.hpp"
#include "DmImu.hpp"
#include "Motors.hpp"
#include "Pid.hpp"
#include "CalcuNeed.hpp"
#include "can.h"
#include "stm32f4xx_hal_can.h"
#include <cstdint>
#include <cstdlib>

MOTORS::Motors *motor3508;
MOTORS::Motors *motor6020;
DM_IMU::DmImu *dmImu;
PID::Pid *motorPosPid;
PID::Pid *motorVelPid;

int16_t current = 0; // GM6020: [-16384, 16384]
uint8_t data[8];

float torgetVel = 0.0f;
float reqCurrent = 0.0f; // GM6020: [-3.0, 3.0]
float expectPos = 0.0f;  // rad, [0, 2PI)
uint16_t posCnt = 0;

IIR3 filter;

void App::initApp()
{
    motor3508 = new MOTORS::Motors(3, 0x200, 0x200);
    dmImu = new DM_IMU::DmImu(&hcan2, 0x01, 0x11, 0x6FF);
    motorPosPid = new PID::Pid(5.0f, 0.0f, 0.0f, 1 / 1000.f);
    motorVelPid = new PID::Pid(0.00003f, 0.f, 0.f, 1 / 1000.f);
    torgetVel = 0.0f;
    reqCurrent = 0.0f;
    expectPos = 0.0f;
    posCnt = 0;
}

void App::sendCanData()
{
    current = 0;
    data[0] = current >> 8;
    data[1] = current;
    data[2] = current >> 8;
    data[3] = current;
    data[4] = current >> 8;
    data[5] = current;
    data[6] = current >> 8;
    data[7] = current;
    if (motor3508 != nullptr && motor6020 != nullptr) {
        motor3508->sendData(data);
        motor6020->sendData(data);
    }
    dmImu->sendRequest(0x03);
}

void App::getCanData()
{
    if (motor3508 != nullptr && motor6020 != nullptr) {
        motor6020->getData();
        motor3508->getData();
    }
    if (dmImu != nullptr) {
        dmImu->getData();
    }
}

void App::motorCtrl()
{
    if (std::abs(get_minor_arc(motor6020->_realDatas.angle, expectPos,
                               2 * M_PI)) < 0.05f) {
        current = 0;
    } else {
        torgetVel = motorPosPid->calc(
                get_minor_arc(expectPos, motor6020->_realDatas.angle, 2 * M_PI),
                0.0f);
        reqCurrent = motorVelPid->calc(
                torgetVel, filter.process(motor6020->_realDatas.speed));

        current = (int16_t)(reqCurrent / 3.0f * 16384);
    }

    posCnt >= 1000 ?
            (expectPos += (expectPos >= 2 * M_PI) ? -2 * M_PI : M_PI / 3.f,
             posCnt = 0) :
            posCnt++;
}

void App::motorVelCtrl()
{
    reqCurrent = motorVelPid->calc(torgetVel,
                                   filter.process(motor6020->_realDatas.speed));

    current = (int16_t)(reqCurrent / 3.0f * 16384);
}


void sendCanData() { App::instance()->sendCanData(); }

void getCanData() { App::instance()->getCanData(); }

void motorCtrl() { App::instance()->motorCtrl(); }

#include "DMMotors.hpp"
#include "stm32f407xx.h"
#include "CalcuNeed.hpp"

using namespace DMMOTORS;
DMMotors::DMMotors(DMMotorInit_s _motorInit)
        : offsetId(_motorInit._offsetId), hcan(_motorInit._hcan), rxQueue(xQueueCreate(3, sizeof(rxData_)))
{
    uint16_t offsetId = static_cast<uint16_t>(_motorInit.motorType);

    BspCan::instance().registerCallback(hcan, rxBaseId + offsetId, [this](const uint8_t *_data) {
        BaseType_t higherPriorityTaskWoken = pdFALSE;
        xQueueSendFromISR(this->rxQueue, _data, &higherPriorityTaskWoken);
    });
}

void DMMotors::cmd(float _cmd)
{
    MITData_s cmd = { 0, 0, 0, 0, float_to_uint(_cmd, -10.f, 10.f, 12) };

    uint8_t txData[8] = {};

    txData[0] = static_cast<uint8_t>((cmd.angle & 0xFF00) >> 8);
    txData[1] = static_cast<uint8_t>(cmd.angle & 0x00FF);
    txData[2] = static_cast<uint8_t>((cmd.speed & 0x0FF0) >> 4);
    txData[3] = static_cast<uint8_t>((cmd.speed & 0x000F) << 4 | ((cmd.Kp & 0x0FF0) >> 8));
    txData[4] = static_cast<uint8_t>(cmd.Kp & 0x000F);
    txData[5] = static_cast<uint8_t>((cmd.Kd & 0x0FF0) >> 4);
    txData[6] = static_cast<uint8_t>((cmd.Kd & 0x000F) << 4 | ((cmd.torque & 0x0F00) >> 8));
    txData[7] = static_cast<uint8_t>(cmd.torque & 0x00FF);

    BspCan::instance().transmitData(hcan, txId, txData, 8);
}

void DMMotors::praseData()
{
    if (xQueueReceive(this->rxQueue, rxData_, 0) == pdTRUE) {
        _datas.ID = rxData_[0] & 0x0F;
        _datas.errorCode = static_cast<ErrorCode_e>(rxData_[0] >> 4);
        _datas.angle = (rxData_[1] << 8) | rxData_[2];
        _datas.speed = (rxData_[3] << 4) | (rxData_[4] >> 4);
        _datas.torque = ((rxData_[4] & 0xF) << 8 | rxData_[5]);
        _datas.mosTemperature = rxData_[6];
        _datas.rotorTemperature = rxData_[7];

        _realDatas.angle = (float)_datas.angle / 16384.f * 2 * PI;
        _realDatas.speed = (float)_datas.speed / 60.f * 2 * PI;
    }
}
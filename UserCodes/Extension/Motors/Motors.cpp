#include "Motors.hpp"
#include <cstdint>
#include <numbers>
#include <cstring>

using namespace MOTORS;
static std::unordered_map<uint16_t, MotorsGroup_s> motorsMap;
Motors::Motors(MotorInit_s _motorInit)
        : txId(_motorInit._txId)
        , rxBaseId(_motorInit._rxBaseId)
        , offsetId(_motorInit._offsetId)
        , hcan(_motorInit._hcan)
        , rxQueue(xQueueCreate(3, sizeof(rxData_)))
{
    BspCan::instance().registerCallback(
            hcan, rxBaseId + offsetId, [this](const uint8_t *_data) {
                BaseType_t higherPriorityTaskWoken = pdFALSE;
                xQueueSendFromISR(this->rxQueue, _data,
                                  &higherPriorityTaskWoken);
            });
    if (_motorInit.motorType == MotorType_e::M3508) {
        reductionRatio = 3591.f / 187.f;
        currCodeSpan = 20.f;
    } else if (_motorInit.motorType == MotorType_e::GM6020)
        currCodeSpan = 3.f;

    updateMap();
}

void Motors::cmd(float _cmd)
{
    int16_t cmd = static_cast<int16_t>(_cmd * 16384.f / currCodeSpan);

    auto &motorsGroup = motorsMap[txId];
    motorsGroup.sendLoad |= (1 << (offsetId - 1));

    motorsGroup.txData[(2 * offsetId) - 2] =
            static_cast<uint8_t>((cmd >> 8) & 0xFF);
    motorsGroup.txData[(2 * offsetId) - 1] = static_cast<uint8_t>(cmd & 0xFF);

    if (motorsGroup.sendLoad == motorsGroup.sendMask) {
        BspCan::instance().transmitData(hcan, txId, motorsGroup.txData, 8);
        memset(motorsGroup.txData, 0, sizeof(motorsGroup.txData));
        motorsGroup.sendLoad = 0;
    }
}

void Motors::praseData()
{
    if (xQueueReceive(this->rxQueue, rxData_, 0) == pdTRUE) {
        _datas.angle = ((rxData_[0] << 8) | rxData_[1]);
        _datas.speed = static_cast<int16_t>(((rxData_[2] << 8) | rxData_[3]));
        _datas.torqueCurrent = static_cast<int16_t>(
                (static_cast<uint16_t>((rxData_[4] << 8) | rxData_[5])));
        _datas.temp = rxData_[6];

        _realDatas.angle = (float)_datas.angle / 8192.f * 2 * PI;
        _realDatas.speed = (float)_datas.speed / 60.f * 2 * PI / reductionRatio;
    }
}

void Motors::updateMap()
{
    if (!motorsMap.contains(txId))
        motorsMap.emplace(txId, MotorsGroup_s{ .motorsGroup = {},
                                               .sendLoad = 0,
                                               .sendMask = 0,
                                               .txData = {} });

    if (motorsMap[txId].motorsGroup[offsetId - 1] == nullptr) {
        motorsMap[txId].motorsGroup[offsetId - 1] = this;
        motorsMap[txId].sendMask |= (1 << (offsetId - 1));
    }
}

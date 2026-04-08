#include "DmImu.hpp"

#include "CalcuNeed.hpp"
#include <cstring>
#include <numbers>
namespace DM_IMU {

DmImu::DmImu(uint16_t _canId, uint16_t _txId, uint16_t _rxId)
        : canId(_canId)
        , txId(_txId)
        , rxId(_rxId)
        , rxQueue(xQueueCreate(3, sizeof(rxData)))
{
    BspCan::instance().registerCallback(
            &hcan2, rxId, [this](const uint8_t *_data) {
                BaseType_t higherPriorityTaskWoken = pdFALSE;
                xQueueSendFromISR(this->rxQueue, _data,
                                  &higherPriorityTaskWoken);
            });
}

void DmImu::getData()
{
    if (xQueueReceive(this->rxQueue, rxData, 0) != pdTRUE) {
        switch (rxData[0]) {
        case ACC_REG: {
            uint16_t accel[3];
            accel[0] = rxData[3] << 8 | rxData[2];
            accel[1] = rxData[5] << 8 | rxData[4];
            accel[2] = rxData[7] << 8 | rxData[6];

            datas.body.ax =
                    uint_to_float(accel[0], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
            datas.body.ay =
                    uint_to_float(accel[1], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
            datas.body.az =
                    uint_to_float(accel[2], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
            break;
        }
        case GYRO_REG: {
            uint16_t gyro[3];
            gyro[0] = rxData[3] << 8 | rxData[2];
            gyro[1] = rxData[5] << 8 | rxData[4];
            gyro[2] = rxData[7] << 8 | rxData[6];

            datas.body.gx =
                    uint_to_float(gyro[0], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
            datas.body.gy =
                    uint_to_float(gyro[1], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
            datas.body.gz =
                    uint_to_float(gyro[2], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
            break;
        }
        case EULAR_REG: {
            int euler[3];
            euler[0] = rxData[3] << 8 | rxData[2];
            euler[1] = rxData[5] << 8 | rxData[4];
            euler[2] = rxData[7] << 8 | rxData[6];

            datas.pitch =
                    uint_to_float(euler[0], PITCH_CAN_MIN, PITCH_CAN_MAX, 16);
            datas.yaw = uint_to_float(euler[1], YAW_CAN_MIN, YAW_CAN_MAX, 16);
            datas.roll =
                    uint_to_float(euler[2], ROLL_CAN_MIN, ROLL_CAN_MAX, 16);
            break;
        }
        default:
            break;
        }
    }
}

void DmImu::sendRequest(uint8_t _reg)
{
    uint8_t txBuf[4] = { 0 };
    txBuf[0] = static_cast<uint8_t>(canId);   // CANID_L
    txBuf[1] = static_cast<uint8_t>((canId)); // CANID_H
    txBuf[2] = _reg;                          // RID
    txBuf[3] = 0xCC;
    BspCan::instance().transmitData(&hcan2, txId, txBuf, 4);
}

} // namespace DM_IMU

#include "DmImu.hpp"
#include "BspCan.hpp"
#include "CalcuNeed.hpp"
#include <cstring>
#include <numbers>

constexpr float F_PI = std::numbers::pi_v<float>;

namespace DM_IMU {
#define ACCEL_CAN_MAX (58.8f)
#define ACCEL_CAN_MIN (-58.8f)
#define GYRO_CAN_MAX  (34.88f)
#define GYRO_CAN_MIN  (-34.88f)

// Directly use radian values to define the range
#define PITCH_CAN_MAX (F_PI / 2.0f)  // 90 degrees = π/2 radians
#define PITCH_CAN_MIN (-F_PI / 2.0f) // -90 degrees = -π/2 radians
#define ROLL_CAN_MAX  (F_PI)         // 180 degrees = π radians
#define ROLL_CAN_MIN  (-F_PI)        // -180 degrees = -π radians
#define YAW_CAN_MAX   (F_PI)         // 180 degrees = π radians
#define YAW_CAN_MIN   (-F_PI)        // -180 degrees = -π radians

/**
 * @brief Convert unsigned integer to float
 */
// static float uint_to_float(int _x_int, float _x_min, float _x_max, int _bits)
// {
//     float span = _x_max - _x_min;
//     float offset = _x_min;
//     return ((float)_x_int) * span / ((float)((1 << _bits) - 1)) + offset;
// }

DmImu::DmImu(CAN_HandleTypeDef *_hcan, uint16_t _id, uint16_t _feedbackId,
             uint16_t _sendId)
        : _hcan(_hcan), _id(_id), _feedbackId(_feedbackId), _sendId(_sendId)

{
    memset(rxData, 0, sizeof(rxData));
    _datas = {};
}

void DmImu::getData()
{
    memcpy(rxData, BspCan::instance().rxBuffer2, 8);
    const uint8_t *data = rxData;

    switch (data[0]) {
    case 0x01: { // Accelerometer data
        uint16_t accel[3];
        accel[0] = data[3] << 8 | data[2];
        accel[1] = data[5] << 8 | data[4];
        accel[2] = data[7] << 8 | data[6];

        _datas.body.ax =
                uint_to_float(accel[0], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
        _datas.body.ay =
                uint_to_float(accel[1], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
        _datas.body.az =
                uint_to_float(accel[2], ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
        break;
    }
    case 0x02: { // Gyroscope data
        uint16_t gyro[3];
        gyro[0] = data[3] << 8 | data[2];
        gyro[1] = data[5] << 8 | data[4];
        gyro[2] = data[7] << 8 | data[6];

        _datas.body.gx = uint_to_float(gyro[0], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
        _datas.body.gy = uint_to_float(gyro[1], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
        _datas.body.gz = uint_to_float(gyro[2], GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
        break;
    }
    case 0x03: { // Euler angle data
        int euler[3];
        euler[0] = data[3] << 8 | data[2];
        euler[1] = data[5] << 8 | data[4];
        euler[2] = data[7] << 8 | data[6];

        _datas.pitch =
                uint_to_float(euler[0], PITCH_CAN_MIN, PITCH_CAN_MAX, 16);
        _datas.yaw = uint_to_float(euler[1], YAW_CAN_MIN, YAW_CAN_MAX, 16);
        _datas.roll = uint_to_float(euler[2], ROLL_CAN_MIN, ROLL_CAN_MAX, 16);
        break;
    }
    default:
        break;
    }
}

void DmImu::sendRequest(uint8_t _reg)
{
    uint8_t txBuf[4] = { 0 };
    txBuf[0] = static_cast<uint8_t>(_id);        // CANID_L
    txBuf[1] = static_cast<uint8_t>((_id >> 8)); // CANID_H
    txBuf[2] = _reg;                             // RID
    txBuf[3] = 0xCC;
    BspCan::instance().transmitData(_hcan, _sendId, txBuf, 4);
}

} // namespace DM_IMU

#include "DmImu.hpp"
#include "BspCan.hpp"
#include <cstring>
#include <numbers>

constexpr float F_PI = std::numbers::pi_v<float>;

namespace DM_IMU {
#define ACCEL_CAN_MAX (58.8f)
#define ACCEL_CAN_MIN (-58.8f)
#define GYRO_CAN_MAX (34.88f)
#define GYRO_CAN_MIN (-34.88f)

// Directly use radian values to define the range
#define PITCH_CAN_MAX (F_PI / 2.0f)  // 90 degrees = π/2 radians
#define PITCH_CAN_MIN (-F_PI / 2.0f) // -90 degrees = -π/2 radians
#define ROLL_CAN_MAX (F_PI)          // 180 degrees = π radians
#define ROLL_CAN_MIN (-F_PI)         // -180 degrees = -π radians
#define YAW_CAN_MAX (F_PI)           // 180 degrees = π radians
#define YAW_CAN_MIN (-F_PI)          // -180 degrees = -π radians

/**
 * @brief Convert unsigned integer to float
 */
static float uint_to_float(int _x_int, float _x_min, float _x_max, int _bits) {
  float span = _x_max - _x_min;
  float offset = _x_min;
  return ((float)_x_int) * span / ((float)((1 << _bits) - 1)) + offset;
}

DmImu::DmImu(CAN_HandleTypeDef *_hcan, uint16_t _id, uint16_t _feedbackId,
             uint16_t _sendId)
    : _hcan(_hcan), _id(_id), _feedbackId(_feedbackId), _sendId(_sendId)

{
  memset(rxData, 0, sizeof(rxData));
  _datas = {};
}

void DmImu::getData() {
  memcpy(rxData, BspCan::instance().rxBuffer2, 8);
  const uint8_t *data = rxData;
}

void DmImu::sendRequest(uint8_t _reg) {
  uint8_t txBuf[4] = {0};

  BspCan::instance().transmitData(_hcan, _sendId, txBuf, 4);
}

} // namespace DM_IMU

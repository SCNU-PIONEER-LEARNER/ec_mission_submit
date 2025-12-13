#include "DmImu.hpp"
#include "BspCan.hpp"
#include <cstring>
#include <numbers>

constexpr float F_PI = std::numbers::pi_v<float>;

namespace DM_IMU {
#define ACCEL_CAN_MAX (58.8f)  // 加速度最大范围
#define ACCEL_CAN_MIN (-58.8f) // 加速度最小范围
#define GYRO_CAN_MAX (34.88f)  // 角速度最大范围
#define GYRO_CAN_MIN (-34.88f) // 角速度最小范围

// Directly use radian values to define the range
#define PITCH_CAN_MAX (F_PI / 2.0f)  // 90 degrees = π/2 radians  俯仰角范围
#define PITCH_CAN_MIN (-F_PI / 2.0f) // -90 degrees = -π/2 radians
#define ROLL_CAN_MAX (F_PI)          // 180 degrees = π radians  滚转角范围
#define ROLL_CAN_MIN (-F_PI)         // -180 degrees = -π radians
#define YAW_CAN_MAX (F_PI)           // 180 degrees = π radians  偏航角范围
#define YAW_CAN_MIN (-F_PI)          // -180 degrees = -π radians
}
/**
 * @brief Convert unsigned integer to float
 */

// can总线收到的无符号整数值转化为实际物理量浮点值
static float uint_to_float(int _x_int, float _x_min, float _x_max, int _bits) {
  float span = _x_max - _x_min;
  float offset = _x_min;
  return ((float)_x_int) * span / ((float)((1 << _bits) - 1)) + offset;
}

// static int float_to_uint(float _x_float, float _x_min, float _x_max, int _bits)
// {
//  /* Converts a float to an unsigned int, given range and number of bits */
//   float span = _x_max- _x_min;
//   float offset = _x_min;
//   return (int) ((_x_float-offset)*((float)((1<<_bits)-1))/span);
// }

DM_IMU::DmImu::DmImu(CAN_HandleTypeDef *_hcan, uint16_t _id, uint16_t _feedbackId,
             uint16_t _sendId)
    : _hcan(_hcan), _id(_id), _feedbackId(_feedbackId), _sendId(_sendId)

{
  memset(rxData, 0, sizeof(rxData));
  _datas = {};
}
  
void DM_IMU::DmImu::getData() 
{
  memcpy(rxData, BspCan::instance().rxBuffer2, 8);
  const uint8_t *data = rxData;
}

void DM_IMU::DmImu::IMU_UpdataAccel(uint8_t *data)
{
  uint16_t ax_raw = (data[3] << 8) | data[2];
  uint16_t ay_raw = (data[5] << 8) | data[4];
  uint16_t az_raw = (data[7] << 8) | data[6];

  _datas.body.ax = uint_to_float(ax_raw, ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
  _datas.body.ay = uint_to_float(ay_raw, ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
  _datas.body.az = uint_to_float(az_raw, ACCEL_CAN_MIN, ACCEL_CAN_MAX, 16);
}

void DM_IMU::DmImu::IMU_UpdataGyro(uint8_t *data)
{
  uint16_t gx_raw = (data[3] << 8) | data[2];
  uint16_t gy_raw = (data[5] << 8) | data[4];
  uint16_t gz_raw = (data[7] << 8) | data[6];

  _datas.body.gx = uint_to_float(gx_raw, GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
  _datas.body.gy = uint_to_float(gy_raw, GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
  _datas.body.gz = uint_to_float(gz_raw, GYRO_CAN_MIN, GYRO_CAN_MAX, 16);
}

void DM_IMU::DmImu::IMU_UpdataEuler(uint8_t *data)
{
  uint16_t yaw_raw = (data[3] << 8) | data[2];
  uint16_t pitch_raw = (data[5] << 8) | data[4];
  uint16_t roll_raw = (data[7] << 8) | data[6];

  _datas.yaw = uint_to_float(yaw_raw, YAW_CAN_MIN, YAW_CAN_MAX, 16);
  _datas.pitch = uint_to_float(pitch_raw, PITCH_CAN_MIN, PITCH_CAN_MAX, 16);
  _datas.roll = uint_to_float(roll_raw, ROLL_CAN_MIN, ROLL_CAN_MAX, 16);                          
}

void DM_IMU::DmImu::IMU_UpdataData(uint8_t *data)
{
  switch(data[0])
 {
    case 1:
      IMU_UpdataAccel(data);
      break;
    case 2:
      IMU_UpdataGyro(data);
      break;
    case 3:
      IMU_UpdataEuler(data);
      break;
    // case 4:
    //   IMU_UpdateQuaternion(data);
    //   break;
 }
}

// void IMU_UpdateQuaternion(uint8_t* pData)
// {
//   float imu.q[4];
//   int w = pData[1]<<6| ((pData[2]&0xF8)>>2);
//   int x = (pData[2]&0x03)<<12|(pData[3]<<4)|((pData[4]&0xF0)>>4);
//   int y = (pData[4]&0x0F)<<10|(pData[5]<<2)|(pData[6]&0xC0)>>6;
//   int z = (pData[6]&0x3F)<<8|pData[7];

//   imu.q[0] = uint_to_float(w,Quaternion_MIN,Quaternion_MAX,14);
//   imu.q[1] = uint_to_float(x,Quaternion_MIN,Quaternion_MAX,14);
//   imu.q[2] = uint_to_float(y,Quaternion_MIN,Quaternion_MAX,14);
//   imu.q[3] = uint_to_float(z,Quaternion_MIN,Quaternion_MAX,14);
// }

void DM_IMU::DmImu::sendRequest(uint8_t _reg) 
{
  uint8_t txBuf[4] = {0};
  txBuf[0] = (uint8_t)_sendId;  // 寄存器地址
  txBuf[1] = (uint8_t)(_sendId>>8);  
  txBuf[2] = _reg;              
  txBuf[3] = 0xCC;

  BspCan::instance().transmitData(_hcan, _sendId, txBuf, 4);
}

// namespace DM_IMU

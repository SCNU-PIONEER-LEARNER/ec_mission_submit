#include "QuadriCycle.hpp"
#include "DT7.hpp"
#include "DT7Msg.hpp"
#include "cmath"

using namespace QUADRICYCLE;

#define SQRT_2 std::numbers::sqrt2_v<float>

//四个轮子pid为(0.3f, 0.f, 0.0f, 0.001f, 16384.f, 0.f)；
QuadriCycle::QuadriCycle(ChassisType_e _chassisType, QueueHandle_t _yawPosQueue)
        : chassisType_(_chassisType), yawPosQueue_(_yawPosQueue)
{
    for (uint8_t i = 0; i < 4; i++) {
        MOTORS::MotorInit_s motorInit = { 0x200, 0x200,
                                          static_cast<uint16_t>(i + 1), &hcan1,
                                          MOTORS::MotorType_e::M3508 };

        motors_._[i] = new MOTORS::Motors(motorInit);
        velPid_[i].pid = new PID::Pid(0.3f, 0.f, 0.0f, 0.001f, 16384.f, 0.f);
    }
}

Speed_u QuadriCycle::forward()
{
    Speed_u speed;
    if (chassisType_ == ChassisType_e::MENUCAM) {
        speed.vx = W_CIRCUMFERENCE *
                   (curWheels.M_LF - curWheels.M_RF + curWheels.M_LB -
                    curWheels.M_RB) /
                   4.f / (2 * PI);
        speed.vy = W_CIRCUMFERENCE *
                   (BACK_R * -curWheels.M_RF - BACK_R * curWheels.M_LF +
                    FRONT_R * curWheels.M_LB + FRONT_R * curWheels.M_RB) /
                   (2.f * (BACK_R + FRONT_R)) / (2 * PI);
        speed.wz = (W_DIAMETER / 2.f) *
                   (curWheels.M_RF + curWheels.M_LF + curWheels.M_LB +
                    curWheels.M_RB) /
                   (2.f * (BACK_R + FRONT_R)) * (2.f * PI) / (2 * PI);
    } else if (chassisType_ == ChassisType_e::OMNI) {
        speed.vx = W_CIRCUMFERENCE *
                   (curWheels.M_LF - curWheels.M_RF + curWheels.M_LB -
                    curWheels.M_RB) *
                   (SQRT_2 / 4.f / 60.f);
        speed.vy = W_CIRCUMFERENCE *
                   (-curWheels.M_LF - curWheels.M_RF + curWheels.M_LB +
                    curWheels.M_RB) *
                   (SQRT_2 / 4.f / 60.f);
        speed.wz = (W_DIAMETER / 2.f) *
                   (curWheels.M_RF + curWheels.M_LF + curWheels.M_LB +
                    curWheels.M_RB) *
                   (1.f / (4.f / CHASSIS_R * 30.f / PI));
    }
    return speed;
}

void QuadriCycle::reverse(const Speed_u &_speed)
{
    if (chassisType_ == ChassisType_e::MENUCAM) {
        expWheels.M_RF = (1.f / W_RADIUS) * (-_speed.vx - _speed.vy) +
                         FRONT_R / W_RADIUS * _speed.wz;
        expWheels.M_LF = (1.f / W_RADIUS) * (_speed.vx - _speed.vy) +
                         FRONT_R / W_RADIUS * _speed.wz;
        expWheels.M_LB = (1.f / W_RADIUS) * (_speed.vx + _speed.vy) +
                         BACK_R / W_RADIUS * _speed.wz;
        expWheels.M_RB = (1.f / W_RADIUS) * (-_speed.vx + _speed.vy) +
                         BACK_R / W_RADIUS * _speed.wz;
    } else if (chassisType_ == ChassisType_e::OMNI) {
        expWheels.M_RF = (1.f / W_RADIUS) * (-_speed.vx - _speed.vy) / SQRT_2 +
                         CHASSIS_R / W_RADIUS * _speed.wz;
        expWheels.M_LF = (1.f / W_RADIUS) * (_speed.vx - _speed.vy) / SQRT_2 +
                         CHASSIS_R / W_RADIUS * _speed.wz;
        expWheels.M_LB = (1.f / W_RADIUS) * (_speed.vx + _speed.vy) / SQRT_2 +
                         CHASSIS_R / W_RADIUS * _speed.wz;
        expWheels.M_RB = (1.f / W_RADIUS) * (-_speed.vx + _speed.vy) / SQRT_2 +
                         CHASSIS_R / W_RADIUS * _speed.wz;
    }
}

void QuadriCycle::update()
{
    for (uint8_t i = 0; i < 4; i++) {
        motors_._[i]->praseData();
        curWheels._[i] = iirFilter[i].process(motors_._[i]->_realDatas.speed);
    }
    if (xQueueReceive(yawPosQueue_, &yawPos_, 0) == pdTRUE) {
    };
}

void QuadriCycle::motorCtrl()
{
    for (uint8_t i = 0; i < 4; i++) {
        velPid_[i].elec = velPid_[i].pid->calc(expWheels._[i], curWheels._[i]);
        motors_._[i]->cmd(velPid_[i].elec);
    }
}

void QuadriCycle::ctrl()
{
    update();

    RcMsg_t rcData = rc->getMsg();
    if (rcData.rSwitch == RC_SW_MID) {
        Speed_u speed = { .vx = sCurve(2.f, rcData.rx, 100.f),
                          .vy = -sCurve(2.f, rcData.ry, 100.f),
                          .wz = 0.f };
        speed.vx = (speed.vx * cosf(yawPos_)) - (speed.vy * sinf(yawPos_)),
        speed.vy = (speed.vy * cosf(yawPos_)) + (speed.vx * sinf(yawPos_)),
        reverse(speed);
        motorCtrl();
    } else {
        for (auto motor : motors_._) {
            motor->cmd(0.f);
        }
    }
}

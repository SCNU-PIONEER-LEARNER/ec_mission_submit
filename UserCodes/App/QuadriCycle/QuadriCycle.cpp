#include "QuadriCycle.hpp"
#include "DT7.hpp"
#include "DT7Msg.hpp"

using namespace QUADRICYCLE;

#define SQRT_2 std::numbers::sqrt2_v<float>

//四个轮子pid为(0.3f, 0.f, 0.0f, 0.001f, 16384.f, 0.f)；
QuadriCycle::QuadriCycle(ChassisType_e _chassisType)
        : chassisType_(_chassisType)
{
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

void QuadriCycle::update() {}

void QuadriCycle::motorCtrl() {}

void QuadriCycle::ctrl()
{
    RcMsg_t rcData = rc->getMsg();
    if (rcData.rSwitch == RC_SW_MID) {
    } else {
    }
}

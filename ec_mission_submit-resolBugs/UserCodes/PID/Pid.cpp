#include <cstdint>
#include <cmath>
#include "Pid.hpp"

namespace PID {

Pid::Pid(float Kp, float Ki, float Kd, float dt)
        : iOut(0.0f), Kp(Kp), Ki(Ki), Kd(Kd), dt(dt)
{
    err[0] = 0.0f;
    err[1] = 0.0f;
}

float Pid::calc(float _ref, float _cur)
{
    err[1] = err[0];

    err[0] = _ref - _cur;

    iOut += Ki * err[0] * dt;

    return (Kp * err[0]) + iOut + (Kd * (err[0] - err[1]) / dt);
}

float Pid::dualCalcu(float _expPos, float _curPos, float _curVel)
{
    float torque;
    float expVel;
    expVel = Pid::calc(_expPos, _curPos);
    torque = Pid::calc(expVel, _curVel);
    return torque;
}

} // namespace PID

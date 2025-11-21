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

float Pid::calc(float _ref, float _cur) {}

} // namespace PID

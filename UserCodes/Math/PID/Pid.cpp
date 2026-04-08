#include <algorithm>
#include "Pid.hpp"

namespace PID {

Pid::Pid(float _kp, float _ki, float _kd, float _dt, float _outMax, float _iMax)
        : kp(_kp), ki(_ki), kd(_kd), dt(_dt), outMax(_outMax), iMax(_iMax)
{
    err[0] = 0.0f;
    err[1] = 0.0f;
}

float Pid::calc(float _ref, float _cur)
{
    err[1] = err[0];
    err[0] = _ref - _cur;
    iOut += ki * (err[0] + err[1]) / 2.f * dt;
    iOut = std::clamp(iOut, -iMax, iMax);
    return std::clamp((kp * err[0]) + iOut + (kd * (err[0] - err[1]) / dt),
                      -outMax, outMax);
}
} // namespace PID
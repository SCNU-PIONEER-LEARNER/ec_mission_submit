#pragma once

namespace PID {
class Pid {
public:
    Pid(float _kp, float _ki, float _kd, float _dt, float _outMax, float _iMax);
    ~Pid();

    float calc(float _ref, float _cur);

private:
    float iOut = 0.0f;
    float err[2] = {};
    float kp, ki, kd, dt, outMax;
    float iMax = 0.0f;
};

} // namespace PID
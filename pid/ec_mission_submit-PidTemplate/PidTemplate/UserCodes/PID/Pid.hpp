#pragma once
#include "App.hpp"

namespace PID {
class Pid {
public:
    Pid(float Kp, float Ki, float Kd, float _dt);
    ~Pid();

    float calc(float _ref, float _cur);

    float iOut;
    float err[3];

private:
    float Kp;
    float Ki;
    float Kd;
    float dt;
    float current;
};

} // namespace PID
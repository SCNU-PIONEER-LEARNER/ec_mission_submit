#pragma once

namespace PID {
class Pid {
public:
    Pid(float Kp, float Ki, float Kd, float _dt);
    ~Pid();

    float calc(float _ref, float _cur);
    float dualCalcu(float expPos, float curPos, float curVel);

    float iOut;
    float err[2];

private:
    float Kp;
    float Ki;
    float Kd;
    float dt;
};

} // namespace PID
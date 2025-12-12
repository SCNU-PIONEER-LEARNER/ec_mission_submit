#pragma once
#define DeadZone 0.0f

namespace PID {
class Pid {
public:
    Pid(float kp, float Ki, float Kd, float _dt);
    ~Pid();

    float calc(float _ref, float _cur);
    float calcInc(float _ref, float _cur);

    float iOut;
    float err[2];
    float errInc[3];

private:
    float kp;
    float Ki;
    float Kd;
    float _dt;
    float outPutData;
};

} // namespace PID
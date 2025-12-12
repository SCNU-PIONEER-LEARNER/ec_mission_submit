#include <cstdint>
#include <cmath>
#include "Pid.hpp"

namespace PID {

Pid::Pid(float KP, float Ki, float dK, float _dt)
        : iOut(0.0f), kp(KP), Ki(Ki), Kd(dK), _dt(_dt)
        ,outPutData(0.0f)
{
    err[0] = 0.0f;
    err[1] = 0.0f;
    /*从上到下依次为当前误差[0]，上一次的误差[1]，上上次的误差[2]*/
    errInc[0] = 0.0f;
    errInc[1] = 0.0f;
    errInc[2] = 0.0f;
}

float Pid::calc(float _ref, float _cur) {
    err[0] = _ref - _cur;
    if(fabs((double)err[0]) < 0.001f) {//dead zone = 0.001f
        return 0.0f;
    }
    float pOut = kp * err[0];
    iOut += Ki * err[0] * _dt;
    float dOut = Kd * (err[0] - err[1]) / _dt;
    err[1] = err[0];
    return pOut + iOut + dOut;
}

float Pid::calcInc(float _ref, float _cur) {
    errInc[0] = _ref - _cur;

    float pOut = kp * (errInc[0] - errInc[1]);
    float iOut = Ki * errInc[0] * _dt;
    float dOut = Kd * (errInc[0] - 2.0f * errInc[1] + errInc[2]) / _dt;
    float deltaU = pOut + iOut + dOut;
    outPutData += deltaU;
    errInc[1] = errInc[2];
    errInc[2] = errInc[0];

    return outPutData;
}
}
 // namespace PID

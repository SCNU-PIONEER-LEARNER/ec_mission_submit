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

float Pid::calc(float _ref, float _cur) {
    if (err[0] < 0.00001f && err[0] > -0.00001f) {
        err[0] = 0.0f;
    }//死区
    //err[1]=err[0];位移式pid
    //err[0] = _ref - _cur;
    //float pOut = Kp * err[0];
    //iOut += Ki * err[0] * dt;
    //float dOut = Kd * (err[0] - err[1]) / dt;
    //return pOut + iOut + dOut;
    //err[0]当前误差， err[1]上次误差， err[2]上上次误差
    
    err[2] = err[1];//单环增量式pid
    err[1] = err[0];
    err[0] = _ref - _cur;
    float pout=Kp*(err[0]-err[1]);
    iOut+=Ki*err[0]*dt;
    float dout=Kd*(err[0]-2*err[1]+err[2])/dt;
    return pout + iOut + dout;
  
}

} // namespace PID

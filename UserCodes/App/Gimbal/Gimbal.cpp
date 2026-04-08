#include "Gimbal.hpp"
#include "DT7.hpp"
#include "DT7Msg.hpp"

//yaw 角度环(140.f, 30.0f, 0.0f, 0.001f, 16384.f, 5.f)
//yaw 速度环(0.05f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f)
//pitch 角度环(350.f, 70.f, 0.0f, 0.001f, 16384.f, 5.f)
//pitch 速度环(0.034f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f)
Gimbal::Gimbal(QueueHandle_t _insDataQueue) : insDataQueue_(_insDataQueue)
{
}

void Gimbal::update()
{
    if (xQueueReceive(insDataQueue_, &insDat_, 0) == pdTRUE) {
        curYaw_ = insDat_.yaw;
        curPitch_ = insDat_.pitch;
    }
}

void Gimbal::yawCtrl()
{
}

void Gimbal::pitchCtrl()
{
}

void Gimbal::ctrl()
{
    RcMsg_t rcData = rc->getMsg();
    if (rcData.rSwitch == RC_SW_MID) {
    } else {
        cmdYaw_ = curYaw_;
        cmdPitch_ = curPitch_;
    }
}
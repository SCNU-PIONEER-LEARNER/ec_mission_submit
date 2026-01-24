#include "Gimbal.hpp"
#include "DT7.hpp"
#include "DT7Msg.hpp"
#include "Motors.hpp"

//yaw 角度环(140.f, 30.0f, 0.0f, 0.001f, 16384.f, 5.f)
//yaw 速度环(0.05f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f)
//pitch 角度环(350.f, 70.f, 0.0f, 0.001f, 16384.f, 5.f)
//pitch 速度环(0.034f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f)
Gimbal::Gimbal(QueueHandle_t _insDataQueue, QueueHandle_t _yawPosQueue)
        : insDataQueue_(_insDataQueue), yawPosQueue_(_yawPosQueue)
{
    MOTORS::MotorInit_s yawMotorInit = { 0x1FE, 0x204, 2, &hcan1,
                                         MOTORS::MotorType_e::GM6020 };
    motors_.yaw = new MOTORS::Motors(yawMotorInit);
    yawPosPid_.pid = new PID::Pid(140.f, 30.0f, 0.0f, 0.001f, 16384.f, 5.f);
    yawVelPid_.pid = new PID::Pid(0.05f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f);

    MOTORS::MotorInit_s pitchMotorInit = { 0x1FE, 0x204, 1, &hcan1,
                                           MOTORS::MotorType_e::GM6020 };
    motors_.pitch = new MOTORS::Motors(pitchMotorInit);
    pitchPosPid_.pid = new PID::Pid(350.f, 70.f, 0.0f, 0.001f, 16384.f, 5.f);
    pitchVelPid_.pid = new PID::Pid(0.034f, 0.0f, 0.0f, 0.001f, 16384.f, 0.f);
}

void Gimbal::update()
{
    if (xQueueReceive(insDataQueue_, &insDat_, 0) == pdTRUE) {
        curYaw_ = insDat_.yaw;
        curPitch_ = insDat_.pitch;
    }
    motors_.yaw->praseData();
    motors_.pitch->praseData();
    curPitchVel_ = pitchFilter_.process(motors_.pitch->_datas.speed);
    curYawVel_ = yawFilter_.process(motors_.yaw->_datas.speed);

    yawPos_ = motors_.yaw->_realDatas.angle - YAW_CENTER_ANG;
    xQueueSend(yawPosQueue_, &yawPos_, 0);
}

void Gimbal::yawCtrl()
{
    float yawError = get_minor_arc(cmdYaw_, curYaw_, 2 * PI);

    yawPosPid_.elec = yawPosPid_.pid->calc(yawError, 0.f);
    yawVelPid_.elec = yawVelPid_.pid->calc(yawPosPid_.elec, curYawVel_);

    motors_.yaw->cmd(yawVelPid_.elec);
}

void Gimbal::pitchCtrl()
{
    float pitchError = get_minor_arc(cmdPitch_, curPitch_, 2 * PI);

    pitchPosPid_.elec = pitchPosPid_.pid->calc(pitchError, 0.f);
    pitchVelPid_.elec = pitchVelPid_.pid->calc(pitchPosPid_.elec, curPitchVel_);

    motors_.pitch->cmd(pitchVelPid_.elec);
}

void Gimbal::ctrl()
{
    update();

    RcMsg_t rcData = rc->getMsg();
    if (rcData.rSwitch == RC_SW_MID) {
        if (rcData.lx != 0)
            cmdPitch_ = clampArc((cmdPitch_ + rcData.lx), PITCH_RAD_MIN_ANG,
                                 PITCH_RAD_MAX_ANG, 2 * M_PI);
        if (rcData.ly != 0)
            cmdYaw_ = rangeMap(cmdYaw_ + rcData.ly, -M_PI, M_PI);
        yawCtrl();
        pitchCtrl();
    } else {
        cmdYaw_ = curYaw_;
        cmdPitch_ = curPitch_;
        motors_.yaw->cmd(0.f);
        motors_.pitch->cmd(0.f);
    }
}
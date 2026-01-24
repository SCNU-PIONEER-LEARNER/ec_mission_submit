#pragma once
#include "Motors.hpp"
#include "Pid.hpp"
#include "INS.hpp"
#include "CalcuNeed.hpp"

union Motors_u {
    struct {
        MOTORS::Motors *yaw;
        MOTORS::Motors *pitch;
    };
    MOTORS::Motors *_[2];
};

struct MotorCtrl_s {
    PID::Pid *pid;
    float elec;
};

class Gimbal {
    static constexpr float PITCH_RAD_MIN_ANG = -0.49f;
    static constexpr float PITCH_RAD_MAX_ANG = 0.32f;
    static constexpr float YAW_CENTER_ANG = 0.f;

public:
    Gimbal(QueueHandle_t _insDataQueue, QueueHandle_t _yawPosQueue);

    void ctrl();
    void yawCtrl();
    void pitchCtrl();
    void update();

private:
    Motors_u motors_;
    MotorCtrl_s yawPosPid_;
    MotorCtrl_s yawVelPid_;
    MotorCtrl_s pitchPosPid_;
    MotorCtrl_s pitchVelPid_;

    float cmdYaw_;
    float cmdPitch_;
    float curYaw_;
    float curPitch_;

    float curYawVel_;
    float curPitchVel_;

    QueueHandle_t insDataQueue_;
    QueueHandle_t yawPosQueue_;
    float yawPos_;
    INS_SYS::INSData_s insDat_;

    IIR3 yawFilter_;
    IIR3 pitchFilter_;
};
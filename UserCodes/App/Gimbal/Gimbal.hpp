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
public:
    Gimbal(QueueHandle_t _insDataQueue);

    void ctrl();
    void yawCtrl();
    void pitchCtrl();
    void update();
    
    // Getter methods
    float GetYawAngle() const { return curYaw_; }
    float GetPitchAngle() const { return curPitch_; }
    
    // Setter methods
    void SetTargetAngle(float yaw, float pitch) {
        cmdYaw_ = yaw;
        cmdPitch_ = pitch;
    }
    
    void UpdatePID() {
        yawCtrl();
        pitchCtrl();
    }

private:
    float cmdYaw_;
    float cmdPitch_;
    float curYaw_;
    float curPitch_;

    float curYawVel_;
    float curPitchVel_;

    QueueHandle_t insDataQueue_;
    INS_SYS::INSData_s insDat_;

    IIR3 yawFilter_;
    IIR3 pitchFilter_;
};
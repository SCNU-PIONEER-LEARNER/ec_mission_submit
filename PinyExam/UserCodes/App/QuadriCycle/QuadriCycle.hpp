#pragma once
#include "Motors.hpp"
#include "Pid.hpp"
#include "CalcuNeed.hpp"

namespace QUADRICYCLE {
union WheelsSpeed_u {
    struct {
        float M_RF; // motor of the right front
        float M_LF; // motor of the left front
        float M_LB; // motor of the left back
        float M_RB; // motor of the right back
    };
    float _[4]; // rpm
};

union Motors_u {
    struct {
        MOTORS::Motors *RF;
        MOTORS::Motors *LF;
        MOTORS::Motors *LB;
        MOTORS::Motors *RB;
    };
    MOTORS::Motors *_[4];
};

union Speed_u {
    struct {
        float vx;
        float vy;
        float wz;
    };
    float _[3];
};

struct MotorCtrl_s {
    PID::Pid *pid;
    float elec = 0.f;
};


class QuadriCycle {
    static constexpr float W_DIAMETER = 0.1525f;
    static constexpr float W_RADIUS = (W_DIAMETER / 2);
    static constexpr float W_CIRCUMFERENCE = (M_PI * W_DIAMETER);
    static constexpr float FRONT_R = 0.354f;
    static constexpr float BACK_R = 0.354f;
    static constexpr float CHASSIS_R = 0.354f;

public:
    enum class ChassisType_e : uint8_t {
        OMNI,
        MENUCAM,
    };

    QuadriCycle(ChassisType_e _chassisType);

    void ctrl();
    void motorCtrl();
    Speed_u forward();
    void reverse(const Speed_u &_speed);
    void update();

private:
    WheelsSpeed_u expWheels;
    WheelsSpeed_u curWheels;
    Speed_u curSpeed_;

    IIR3 iirFilter[4];
    ChassisType_e chassisType_;
};

} // namespace QUADRICYCLE

#pragma once

#include "DT7Msg.hpp"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "BspUart.hpp"
#include <memory>

#define RC_READY_EVENT (1 << 0)
typedef struct {
    struct {
        float rx;
        float ry;
        float lx;
        float ly;
    };

    struct {
        uint8_t rSwitch;
        uint8_t lSwitch;
    };

    struct {
        uint8_t rPress;
        uint8_t lPress;
        int16_t xMove;
        int16_t yMove;
        int16_t zRoller;
        int16_t wheel;
    };
} RcMsg_t;

class Rc {
    static constexpr uint8_t FRAME_LENGTH = 18;
    static constexpr float GAIN_RC_YAW = 0.002f;
    static constexpr float GAIN_RC_PITCH = 0.001f;
    static constexpr float S_CURVE_ACC = 3.0f;
    static constexpr uint8_t T_ACC_CNT = 100;

public:
    Rc(UART_HandleTypeDef *_huart, EventGroupHandle_t &_event);
    ~Rc();

    static void task(void *_param);
    RcMsg_t &getMsg() { return rcMsg_; }

private:
    void parse();
    void handler();
    void callBackFromISR(UART_HandleTypeDef *_huart, uint16_t _pos);
    static void updateRocker(float &_target, float _channel);

    RcRawMsg_t data_ = {}; //处理前数据
    RcMsg_t rcMsg_ = {};   //处理后数据（用的是这个）

    Uart uart_;
    EventGroupHandle_t event_;
    uint8_t *buf_ = nullptr;
};
inline std::unique_ptr<Rc> rc;
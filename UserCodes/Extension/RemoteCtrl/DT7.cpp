#include "DT7.hpp"
#include "task.h"
#include "BspDma.hpp"
#include <cmath>
#include <cstdint>

Rc::Rc(UART_HandleTypeDef *_huart, EventGroupHandle_t &_event)
        : uart_(_huart)
        , event_(_event)
        , buf_((uint8_t *)Dma::instance().ram_alloc(2 * FRAME_LENGTH))
{
    uart_.recvDmaMultiBufInit((uint32_t *)buf_, 2 * FRAME_LENGTH);
    uart_.registerCallback([this](UART_HandleTypeDef *_huart, uint16_t _dataLength) {
        callBackFromISR(_huart, _dataLength);
    });
}

Rc::~Rc()
{
    Dma::instance().ram_free(buf_);
    uart_.unregisterCallback();
}

void Rc::callBackFromISR(UART_HandleTypeDef *_huart, uint16_t _pos)
{
    uint16_t size = _huart->RxXferCount;
    // NOLINTBEGIN(readability-redundant-casting)
    if (((((DMA_Stream_TypeDef *)_huart->hdmarx->Instance)->CR) & DMA_SxCR_CT) == RESET) {
        __HAL_DMA_DISABLE(_huart->hdmarx);
        ((DMA_Stream_TypeDef *)_huart->hdmarx->Instance)->CR |= DMA_SxCR_CT;
        __HAL_DMA_SET_COUNTER(_huart->hdmarx, 2 * RC_FRAME_LENGTH);
        if (size == RC_FRAME_LENGTH) {
            xEventGroupSetBitsFromISR(event_, RC_READY_EVENT, nullptr);
        }
    } else {
        __HAL_DMA_DISABLE(_huart->hdmarx);
        ((DMA_Stream_TypeDef *)_huart->hdmarx->Instance)->CR &= ~(DMA_SxCR_CT);
        __HAL_DMA_SET_COUNTER(_huart->hdmarx, 2 * RC_FRAME_LENGTH);
        if (size == RC_FRAME_LENGTH) {
            xEventGroupSetBitsFromISR(event_, RC_READY_EVENT, nullptr);
        }
    }
    __HAL_DMA_ENABLE(_huart->hdmarx);
    // NOLINTEND(readability-redundant-casting)
}

void Rc::parse()
{
    data_.rc.ch0 = ((int16_t)buf_[0] | ((int16_t)buf_[1] << 8)) & 0x07FF;
    if (data_.rc.ch0 > RC_CH_VALUE_MAX || data_.rc.ch0 < RC_CH_VALUE_MIN)
        return;
    data_.rc.ch0 -= RC_CH_VALUE_OFFSET;

    data_.rc.ch1 = (int16_t)(((int16_t)buf_[1] >> 3) | ((int16_t)buf_[2] << 5)) & 0x07FF;
    if (data_.rc.ch1 > RC_CH_VALUE_MAX || data_.rc.ch1 < RC_CH_VALUE_MIN)
        return;
    data_.rc.ch1 -= RC_CH_VALUE_OFFSET;

    data_.rc.ch2 = (int16_t)(((int16_t)buf_[2] >> 6) | ((int16_t)buf_[3] << 2) |
                             ((int16_t)buf_[4] << 10)) &
                   0x07FF;
    if (data_.rc.ch2 > RC_CH_VALUE_MAX || data_.rc.ch2 < RC_CH_VALUE_MIN)
        return;
    data_.rc.ch2 -= RC_CH_VALUE_OFFSET;

    data_.rc.ch3 = (int16_t)(((int16_t)buf_[4] >> 1) | ((int16_t)buf_[5] << 7)) & 0x07FF;
    if (data_.rc.ch3 > RC_CH_VALUE_MAX || data_.rc.ch3 < RC_CH_VALUE_MIN)
        return;
    data_.rc.ch3 -= RC_CH_VALUE_OFFSET;

    data_.rc.switchLeft = (uint8_t)((uint8_t)(buf_[5] >> 4) & 0x0C) >> 2;
    data_.rc.switchRight = (uint8_t)((uint8_t)(buf_[5] >> 4) & 0x03);

    data_.mouse.x = ((int16_t)buf_[6]) | ((int16_t)buf_[7] << 8);
    data_.mouse.y = ((int16_t)buf_[8]) | ((int16_t)buf_[9] << 8);
    data_.mouse.z = ((int16_t)buf_[10]) | ((int16_t)buf_[11] << 8);

    data_.mouse.pressLeft = buf_[12];
    data_.mouse.pressRight = buf_[13];

    data_.keyboard.keyCode = (((uint16_t)buf_[14]) | ((uint16_t)buf_[15] << 8));

    data_.wheel = ((int16_t)buf_[16]) | ((int16_t)buf_[17] << 8);
}

void Rc::updateRocker(float &_target, float _channel)
{
    float delta = (_channel * T_ACC_CNT / 660.0f) - _target;
    _target += std::fmax(-S_CURVE_ACC, std::fmin(S_CURVE_ACC, delta));
}

void Rc::handler()
{
    parse();

    updateRocker(rcMsg_.ry, (float)data_.rc.ch0);
    updateRocker(rcMsg_.rx, (float)data_.rc.ch1);
    rcMsg_.ly = -((float)data_.rc.ch2 * GAIN_RC_YAW / 660);
    rcMsg_.lx = -((float)data_.rc.ch3 * GAIN_RC_PITCH / 660);

    rcMsg_.rSwitch = data_.rc.switchRight;
    rcMsg_.lSwitch = data_.rc.switchLeft;
    rcMsg_.wheel = data_.wheel;
}

void Rc::task(void *_param)
{
    while (true) {
        EventBits_t xBits = xEventGroupWaitBits(rc->event_, RC_READY_EVENT, pdTRUE,
                                                pdFALSE, portMAX_DELAY);
        if (xBits & RC_READY_EVENT) {
            rc->handler();
        }
    }
}

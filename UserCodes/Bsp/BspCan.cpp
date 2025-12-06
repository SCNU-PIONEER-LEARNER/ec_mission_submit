#include "BspCan.hpp"
#include "stm32f4xx_hal_can.h"
#include <cstring>
#include "App.hpp"

BspCan::BspCan() : _stdid(0)
{
    memset(rxData, 0, sizeof(rxData));
    memset(rxBuffer1, 0, sizeof(rxBuffer1));
    memset(rxBuffer2, 0, sizeof(rxBuffer2));
}

void BspCan::init(CAN_HandleTypeDef *_hcan)
{
    if (_hcan == &hcan1) {
        canFilterInit(_hcan, CAN_RX_FIFO0);
    }
    if (_hcan == &hcan2) {
        canFilterInit(_hcan, CAN_RX_FIFO1);
    }
    HAL_CAN_Start(_hcan);
}

HAL_StatusTypeDef BspCan::transmitData(CAN_HandleTypeDef *_hcan,
                                       uint16_t _stdid, uint8_t *_txData,
                                       uint32_t _len)
{
    CAN_TxHeaderTypeDef txHeader;
    uint32_t canMailbox;
    txHeader.DLC = _len;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = _stdid;
    txHeader.TransmitGlobalTime = DISABLE;
    return HAL_CAN_AddTxMessage(_hcan, &txHeader, _txData, &canMailbox);
}

HAL_StatusTypeDef BspCan::canFilterInit(CAN_HandleTypeDef *_hcan,
                                        uint32_t _fifo)
{
    HAL_StatusTypeDef result = HAL_OK;
    CAN_FilterTypeDef canFilterStructure;
    canFilterStructure.FilterActivation = false;
    canFilterStructure.FilterMode = CAN_FILTERMODE_IDMASK;
    canFilterStructure.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterStructure.FilterFIFOAssignment = _fifo;
    canFilterStructure.FilterIdHigh = 0x0000;
    canFilterStructure.FilterIdLow = 0x0000;
    canFilterStructure.FilterMaskIdHigh = 0xFFFF;
    canFilterStructure.FilterMaskIdLow = 0xFFFF;
    if (_hcan == &hcan1) {
        canFilterStructure.FilterBank = 0;
    } else if (_hcan == &hcan2) {
        canFilterStructure.SlaveStartFilterBank = 14;
        canFilterStructure.FilterBank = 14;
    }
    result = HAL_CAN_ConfigFilter(_hcan, &canFilterStructure);
    if (_fifo == 0) {
        result = HAL_CAN_ActivateNotification(_hcan,
                                              CAN_IT_RX_FIFO0_MSG_PENDING);
    } else if (_fifo == 1) {
        result = HAL_CAN_ActivateNotification(_hcan,
                                              CAN_IT_RX_FIFO1_MSG_PENDING);
    }
    return result;
}


void BspCan::callbackFromISR(CAN_HandleTypeDef *_hcan, uint32_t _rxFifo)
{
    CAN_RxHeaderTypeDef rxHeader;
    if (HAL_CAN_GetRxMessage(_hcan, _rxFifo, &rxHeader, rxData) != HAL_OK) {
        return;
    }
    _stdid = rxHeader.StdId;
    if (_hcan == &hcan1) {
        memcpy(rxBuffer1, rxData, 8);
    } else if (_hcan == &hcan2) {
        memcpy(rxBuffer2, rxData, 8);
    }
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *_hcan)
{
    BspCan::instance().callbackFromISR(_hcan, CAN_RX_FIFO0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *_hcan)
{
    BspCan::instance().callbackFromISR(_hcan, CAN_RX_FIFO1);
}

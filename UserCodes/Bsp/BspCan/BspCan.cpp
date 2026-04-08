#include "BspCan.hpp"
#include "stm32f4xx_hal_can.h"
#include "App.hpp"

void BspCan::init(CAN_HandleTypeDef *_hcan)
{
    if (_hcan == &hcan1) {
        canFilterInit(_hcan, CAN_RX_FIFO0);
    } else if (_hcan == &hcan2) {
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
    canFilterStructure.FilterActivation = ENABLE;
    canFilterStructure.FilterMode = CAN_FILTERMODE_IDMASK;
    canFilterStructure.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterStructure.FilterFIFOAssignment = _fifo;
    canFilterStructure.FilterIdHigh = 0x0000;
    canFilterStructure.FilterIdLow = 0x0000;
    canFilterStructure.FilterMaskIdHigh = 0x0000;
    canFilterStructure.FilterMaskIdLow = 0x0000;
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

HAL_StatusTypeDef
BspCan::registerCallback(CAN_HandleTypeDef *_hcan, uint32_t _stdid,
                         std::function<void(const uint8_t *)> _pCallback)
{
    struct Handler_s temp = { .stdid = _stdid, .func = _pCallback };
    if (_hcan == &hcan1) {
        if (can1cnt < 10) {
            cbTable1[can1cnt] = temp;
            can1cnt++;
            return HAL_OK;
        } else {
            return HAL_ERROR;
        }
    } else if (_hcan == &hcan2) {
        if (can2cnt < 10) {
            cbTable2[can2cnt] = temp;
            can2cnt++;
            return HAL_OK;
        } else {
            return HAL_ERROR;
        }
    }
    return HAL_ERROR;
}

void BspCan::callbackFromISR(CAN_HandleTypeDef *_hcan, uint32_t _rxFifo)
{
    CAN_RxHeaderTypeDef rxHeader;
    if (HAL_CAN_GetRxMessage(_hcan, _rxFifo, &rxHeader, rxData) != HAL_OK) {
        return;
    }
    _stdid = rxHeader.StdId;
    if (_hcan == &hcan1) {
        for (uint8_t i = 0; i < can1cnt; i++) {
            if (cbTable1[i].stdid == rxHeader.StdId) {
                cbTable1[i].func(rxData);
                break;
            }
        }
    } else if (_hcan == &hcan2) {
        for (uint8_t i = 0; i < can2cnt; i++) {
            if (cbTable2[i].stdid == rxHeader.StdId) {
                cbTable2[i].func(rxData);
                break;
            }
        }
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

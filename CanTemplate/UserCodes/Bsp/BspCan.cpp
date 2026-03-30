#include "BspCan.hpp"
#include "stm32f4xx_hal_can.h"
#include <cstring>
#include "Motors.hpp"

extern MOTORS::Motors *motor;

BspCan::BspCan() : _stdid(0) {
  memset(rxData, 0, sizeof(rxData));
  memset(rxBuffer1, 0, sizeof(rxBuffer1));
  memset(rxBuffer2, 0, sizeof(rxBuffer2));
}

void BspCan::init(CAN_HandleTypeDef *_hcan) {
  if (_hcan == &hcan1) {
    canFilterInit(_hcan, CAN_RX_FIFO0);
  }
  HAL_CAN_Start(_hcan);
}

//add 控制报文
HAL_StatusTypeDef BspCan::transmitData(CAN_HandleTypeDef *_hcan, uint16_t _stdid, uint8_t *_txData, uint32_t _len) 
{
  CAN_TxHeaderTypeDef txHeader;
  uint32_t canMailbox;
  txHeader.StdId = _stdid;
  txHeader.IDE = CAN_ID_STD; //使用标准帧格式
  txHeader.RTR = CAN_RTR_DATA; //数据帧类型
  txHeader.DLC = _len; //数据长度
  txHeader.TransmitGlobalTime = DISABLE; //不发送全局时间戳
  return HAL_CAN_AddTxMessage(_hcan, &txHeader, _txData, &canMailbox); //can1,结构体,数据,邮箱号
}

//add 过滤器配置
HAL_StatusTypeDef BspCan::canFilterInit(CAN_HandleTypeDef *_hcan,  uint32_t _fifo) 
{
  HAL_StatusTypeDef result = HAL_OK;
  CAN_FilterTypeDef canFilterStructure;

  if(_hcan == &hcan1)
  {                
    canFilterStructure.FilterActivation = ENABLE;
    canFilterStructure.FilterMode = CAN_FILTERMODE_IDMASK; //掩码模式
    canFilterStructure.FilterScale = CAN_FILTERSCALE_32BIT; //滤波器尺寸为32位
    
    canFilterStructure.FilterIdHigh = 0x0000;// 过滤器设置，接受所有id消息
    canFilterStructure.FilterIdLow  = 0x0000; 
    
    canFilterStructure.FilterMaskIdHigh = 0x0000;//屏蔽器设置，设置为全通
    canFilterStructure.FilterMaskIdLow  = 0x0000;
    
    canFilterStructure.FilterBank = 0; //过滤器编号
    canFilterStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0; //设置滤波器的接受为FIFO0
   
    HAL_CAN_ConfigFilter(_hcan, &canFilterStructure); //配置滤波器
    HAL_CAN_ActivateNotification(_hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //激活CAN模块的接收通知
  }

  result = HAL_CAN_ConfigFilter(_hcan, &canFilterStructure);

  if (_fifo == 0) {
    result = HAL_CAN_ActivateNotification(_hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  } else if (_fifo == 1) {
    result = HAL_CAN_ActivateNotification(_hcan, CAN_IT_RX_FIFO1_MSG_PENDING);
  }
  return result;
}

//接收中断回调函数
void BspCan::callbackFromISR(CAN_HandleTypeDef *_hcan, uint32_t _rxFifo) {
  CAN_RxHeaderTypeDef rxHeader;
  if (HAL_CAN_GetRxMessage(_hcan, _rxFifo, &rxHeader, rxData) != HAL_OK) {
    return;
  }
  //读取成功数据储存到rxHeader
  _stdid = rxHeader.StdId;
  if (_hcan == &hcan1)
  {
    memcpy(rxBuffer1, rxData, 8);
    memcpy(rxBuffer2, rxData, 8);
  }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *_hcan) {
  BspCan::instance().callbackFromISR(_hcan, CAN_RX_FIFO0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *_hcan) {
  BspCan::instance().callbackFromISR(_hcan, CAN_RX_FIFO1);
}

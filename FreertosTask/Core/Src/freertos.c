/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "main.h"
#include "queue.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
TaskHandle_t xLedCtrlHandle;
TaskHandle_t xCalcuHandle;
QueueHandle_t xPointerQueue = NULL;
GolableVaribles varibles;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void SendData(int data)
{
  if(xPointerQueue == NULL) {
    return;
  }
  xQueueSend(xPointerQueue, &data, portMAX_DELAY);

}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
int speed = 500;//[1,32767]


/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void CalcuFunction(void *Param)
{
  int temp = 0;
  while(1)
  {
  if(varibles.flag)
  {
    temp = 0;
    for(int i = 0;i < varibles.len;i++)
    {
      if('0' <= varibles.Rxbuffer[i] && varibles.Rxbuffer[i] <= '9')
      {
        temp = temp*10 + (varibles.Rxbuffer[i] - '0');
      }
    }
    varibles.flag = 0;
    SendData(temp);
    memset(varibles.Rxbuffer,0,sizeof(varibles.Rxbuffer));
  }
}
}

void LedCtrlFunction(void *Param)
{
  int temp = 0;
  while(1)
  {
  if(xPointerQueue != NULL){
  if(xQueueReceive(xPointerQueue, &temp,0) == pdPASS)
  {
      speed = temp;
      temp = 0;
  }
  }
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  osDelay(speed);
  }
}


/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void MX_FreeRTOS_Init()
{
  xPointerQueue = xQueueCreate(1, sizeof(int));

  xTaskCreate(CalcuFunction, "Calcu", 128, NULL, 1, &xCalcuHandle);
  xTaskCreate(LedCtrlFunction, "LedCtrl", 128, NULL, 2, &xLedCtrlHandle);
}

/* USER CODE END Application */


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
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal_uart.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern UART_HandleTypeDef huart1;
QueueHandle_t messageQueue1;
uint8_t buf[128];
volatile uint8_t uart_flag = 0;
volatile uint16_t uart_len = 0;
uint16_t buffer = 500;
uint16_t millisec = 500;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LEDTaskHandle;
osThreadId USBFTaskHandle;
osMessageQId myQueue01Handle;
osSemaphoreId myBinarySem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void UART_Process_Data(void);
void UART_Reset_Buffer(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void ledcontrolFun(void const * argument);
void UARTCONTROLFun(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 16, uint16_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
    messageQueue1 = xQueueCreate(10, sizeof(uint16_t)); // 创建大小为10的消息队列

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LEDTask */
  osThreadDef(LEDTask, ledcontrolFun, osPriorityLow, 0, 128);
  LEDTaskHandle = osThreadCreate(osThread(LEDTask), NULL);

  /* definition and creation of USBFTask */
  osThreadDef(USBFTask, UARTCONTROLFun, osPriorityLow, 0, 128);
  USBFTaskHandle = osThreadCreate(osThread(USBFTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
   vTaskStartScheduler();
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ledcontrolFun */
/**
* @brief Function implementing the LEDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ledcontrolFun */
void ledcontrolFun(void const * argument)
{
  /* USER CODE BEGIN ledcontrolFun */
  /* Infinite loop */
  for(;;)
  {
    uint16_t data;

    // 从消息队列接收数据
    if(xQueueReceive(messageQueue1, &data, pdMS_TO_TICKS(10)) == pdPASS){
      if(data >= 100 && data <= 1500){
        millisec = data;  // 更新LED闪烁间隔
      }
    };
    
    // 控制LED闪烁
    HAL_GPIO_TogglePin(LED_PC13_GPIO_Port, LED_PC13_Pin);
    osDelay(millisec);
  }
  /* USER CODE END ledcontrolFun */
}

/* USER CODE BEGIN Header_UARTCONTROLFun */
/**
* @brief Function implementing the USBFTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UARTCONTROLFun */
void UARTCONTROLFun(void const * argument)
{
  /* USER CODE BEGIN UARTCONTROLFun */
  /* Infinite loop */
  for(;;)
  {
    // 如果有新的UART数据到达
    if(uart_flag == 1){
      UART_Process_Data();   // 处理UART数据
      UART_Reset_Buffer();   // 重置UART缓冲区
    }
    osDelay(10);  // 10ms延时，避免任务占用过多CPU
  }
  /* USER CODE END UARTCONTROLFun */
}

/* USER CODE BEGIN 4 */
/**
  * @brief  UART数据处理函数
  * @retval None
  */
void UART_Process_Data(void)
{
  if(uart_flag == 0) {
    return;  // 没有新数据，直接返回
  }
  
  uint16_t result = 0;
  
  // 解析接收到的数字
  for(int i = 0; i < uart_len; i++){
    if(isdigit(buf[i])){
      result = result * 10 + (buf[i] - '0');
    }
    else if(buf[i] == '\n' || buf[i] == '\r' || buf[i] == 0){
      break;  // 遇到结束符就停止解析
    }
  }

  // 如果解析到有效数据，发送到消息队列
  if (result > 0){
    buffer = result;
    xQueueSend(messageQueue1, &buffer, 0);
  }
}

/**
  * @brief  UART缓冲区重置函数
  * @retval None
  */
void UART_Reset_Buffer(void)
{
  // 重置标志和长度
  uart_flag = 0;
  uart_len = 0;
  
  // 清空缓冲区
  memset(buf, 0, 128);
  
  // 重新启动DMA接收，准备接收下一批数据
  HAL_UART_Receive_DMA(&huart1, buf, 128);
}
/* USER CODE END 4 */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

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
#include "usbd_cdc_if.h"
#include <stdint.h>
#include <ctype.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern QueueHandle_t messageQueue1;
extern QueueHandle_t messageQueue2;
SemaphoreHandle_t sem;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int pase = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
QueueHandle_t messageQueue3;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LEDTaskHandle;
osThreadId USBFTaskHandle;
osMessageQId myQueue01Handle;
osSemaphoreId myBinarySem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LEDFun(void const * argument);
void USBFun(void const * argument);

extern void MX_USB_DEVICE_Init(void);
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
  messageQueue1 = xQueueCreate(20, sizeof(uint8_t)); // 创建大小为10的消息队列
  messageQueue2 = xQueueCreate(20, sizeof(uint32_t)); // 创建大小为10的消息队列
  messageQueue3 = xQueueCreate(10, sizeof(int)); // 创建大小为10的消息队列

  sem = xSemaphoreCreateBinary();
  xSemaphoreGive(sem); // 初始化信号量
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LEDTask */
  osThreadDef(LEDTask, LEDFun, osPriorityLow, 0, 128);
  LEDTaskHandle = osThreadCreate(osThread(LEDTask), NULL);

  /* definition and creation of USBFTask */
  osThreadDef(USBFTask, USBFun, osPriorityLow, 0, 128);
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
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LEDFun */
/**
* @brief Function implementing the LEDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LEDFun */
void LEDFun(void const * argument)
{
  /* USER CODE BEGIN LEDFun */
  /* Infinite loop */
  for(;;)
  {    
    int data = 500;
    xQueueReceive(messageQueue3, &data, 0);
    HAL_GPIO_TogglePin(LED_PC13_GPIO_Port, LED_PC13_Pin);
    HAL_Delay(data);
    uint8_t rx_buf[64];  // 接收缓冲区
    uint32_t len = 0;
  
    if(CDC_Receive_FS(rx_buf, &len) == USBD_OK && len > 0) {
      // 有数据到达，len是接收到的字节数
    }

  }
  osDelay(10 );
  /* USER CODE END LEDFun */
}

/* USER CODE BEGIN Header_USBFun */
/**
* @brief Function implementing the USBFTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_USBFun */
void USBFun(void const * argument)
{
  /* USER CODE BEGIN USBFun */
  /* Infinite loop */
  for(;;)
  {
    uint8_t* data = NULL;
    uint32_t len = 0;
    
    // 使用 portMAX_DELAY 阻塞等待，避免忙等待
    if(xQueueReceive(messageQueue1, &data, portMAX_DELAY) == pdTRUE &&
       xQueueReceive(messageQueue2, &len, portMAX_DELAY) == pdTRUE)
    {
      if(data && len > 0)
      {
        uint16_t result = 0;
        for (uint32_t i = 0; i < len; i++) {
          if (isdigit(data[i])) {
            result = result * 10 + (data[i] - '0');
          }
        }
        xQueueSend(messageQueue3, &result, 0);
        
        // 释放动态内存
        vPortFree(data);
      }
    }
  }
  /* USER CODE END USBFun */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */


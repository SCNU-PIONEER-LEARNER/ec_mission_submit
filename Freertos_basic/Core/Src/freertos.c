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
#include "projdefs.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include "usart.h"
#include <stdint.h>
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t rx_buffer[3];
volatile uint8_t rxdone = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for connect_task */
osThreadId_t connect_taskHandle;
const osThreadAttr_t connect_task_attributes = {
  .name = "connect_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartledTask(void *argument);
void Startconnect_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint32_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartledTask, NULL, &ledTask_attributes);

  /* creation of connect_task */
  connect_taskHandle = osThreadNew(Startconnect_Task, NULL, &connect_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

// void UART_connect()
// {
//   __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
//   HAL_UART_Receive_DMA(&huart1, rx_buffer, 3);  
// }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1) 
  {
    HAL_UART_Transmit_DMA(&huart1, rx_buffer, 3);
    HAL_UART_Receive_DMA(&huart1, rx_buffer, 3);  
  }
}

void UART_Address()
{
  uint32_t time = 0;
  int Size = sizeof(rx_buffer) / sizeof(rx_buffer[0]);
    for(int i = Size - 1; i >= 0; i--) 
    {
      if(rx_buffer[i] >= '0' && rx_buffer[i] <= '9') 
        {
          time += (rx_buffer[i] - '0') * pow(10, (Size - i - 1));
        }
    }
    uint32_t check_time = time; 
    //osMessageQueuePut(myQueue01Handle, &time, 0, 0);
    xQueueSend(myQueue01Handle, &check_time, 0);
}
 

/* USER CODE BEGIN Header_StartledTask */
/**
  * @brief  Function implementing the ledTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartledTask */
void StartledTask(void *argument)
{
  /* USER CODE BEGIN StartledTask */
  HAL_UART_Receive_DMA(&huart1, rx_buffer, 3);  
  /* Infinite loop */
  for(;;)
  {
    UART_Address();
    osDelay(1);
    // osMessageQueueGet(myQueue01Handle, &time, NULL, osWaitForever);
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    // osDelay(pdMS_TO_TICKS(time));
  }
  /* USER CODE END StartledTask */
}

/* USER CODE BEGIN Header_Startconnect_Task */
/**
* @brief Function implementing the connect_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startconnect_Task */
void Startconnect_Task(void *argument)
{
  /* USER CODE BEGIN Startconnect_Task */
  uint32_t time;
  uint32_t time_get = 500;
  /* Infinite loop */
  for(;;)
  {
    //osMessageQueueGet(myQueue01Handle, &time, NULL, osWaitForever);
    if (xQueueReceive(myQueue01Handle, &time, portMAX_DELAY) == pdTRUE) 
    {
      time_get = time; 
    }         
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(pdMS_TO_TICKS(time_get));
    //osDelay(time_get);
  }
  /* USER CODE END Startconnect_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


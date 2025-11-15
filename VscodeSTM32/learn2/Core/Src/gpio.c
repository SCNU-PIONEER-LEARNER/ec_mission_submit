#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "../Inc/main.h"

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // 关键：先开GPIOC时钟（PC13属于GPIOC，必须在配置前）
  __HAL_RCC_GPIOC_CLK_ENABLE();  // 这行是PC13生效的核心！
  __HAL_RCC_GPIOA_CLK_ENABLE();  // 串口PA9/PA10的时钟

  // 配置PC13为推挽输出（驱动LED）
  GPIO_InitStruct.Pin = LED_Pin;                  // PC13（GPIO_PIN_13）
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;     // 推挽输出（必须这个模式，否则驱动不了LED）
  GPIO_InitStruct.Pull = GPIO_NOPULL;             // 无上下拉（LED电路自己分压）
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;    // 低速足够
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct); // 关联GPIOC

  // 串口PA9（TX）配置（不变）
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // 串口PA10（RX）配置（不变）
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
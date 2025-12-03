#pragma once

#include "main.h"
#include "stm32f4xx_hal.h"


#define LED_BLUE_ON() \
    HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET)
#define LED_BLUE_OFF() \
    HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET)
#define LED_BLUE_TOGGLE() LED_BLUE_GPIO_Port->ODR ^= LED_BLUE_Pin

#define LED_GREEN_ON() \
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET)
#define LED_GREEN_OFF() \
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET)
#define LED_GREEN_TOGGLE() LED_GREEN_GPIO_Port->ODR ^= LED_GREEN_Pin

#define LED_RED_ON() \
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET)
#define LED_RED_OFF() \
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET)
#define LED_RED_TOGGLE() LED_RED_GPIO_Port->ODR ^= LED_RED_Pin

#define LED_ALL_OFF  \
    LED_RED_OFF();   \
    LED_GREEN_OFF(); \
    LED_BLUE_OFF();

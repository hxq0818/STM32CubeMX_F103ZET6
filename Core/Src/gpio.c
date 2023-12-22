/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "main.h"
#include "tim.h"

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

user_key_status_t user_key;
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = KEY2_Pin|KEY1_Pin|KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(KEY_UP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 14, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 14, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 14, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 14, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 2 */

/*
**按键事件规则:
**按键按下时长大于50ms为一次有效按�?
**短按：按下时间为50-1500ms内算�?次有效的短按
**长按：按下时间为大于1500ms算一次有效的长按
**双击：第�?次与第二次按下间隔为50-300内算�?次有效的短按
*/
void User_Key_Init(void)
{
	memset(&user_key,0,sizeof(user_key_status_t));
	user_key.keyPressStatus[USER_DRV_KEY0_LEVEL] = USER_DRV_KEY_UP;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==KEY0_Pin)
  {
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0 && user_key.keyPressStatus[USER_DRV_KEY0_LEVEL] == USER_DRV_KEY_UP)
    {
//			user_key->key[USER_DRV_KEY0_LEVEL] = USER_DRV_KEY_DOWM;  && user_key->key[USER_DRV_KEY0_LEVEL] == USER_DRV_KEY_UP
//			keystatus = USER_DRV_KEY_DOWM;
			user_key.keyPressStatus[USER_DRV_KEY0_LEVEL] = USER_DRV_KEY_DOWM;
			HAL_TIM_Base_Start_IT(&htim6);
      printf("KEY0_Pin\r\n");
    }
//    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_Pin);
  }
	else if(GPIO_Pin == KEY1_Pin)
	{
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
    {
      printf("KEY1_Pin\r\n");
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_Pin);
	}
	else if(GPIO_Pin == KEY2_Pin)
	{
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
    {
      printf("KEY2_Pin\r\n");
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_Pin);
	}
	else if(GPIO_Pin == KEY_UP_Pin)
	{
		if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)==1)
    {
      printf("KEY_UP_Pin\r\n");
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY_UP_Pin);
	}
}
/* USER CODE END 2 */

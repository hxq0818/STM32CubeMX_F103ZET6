/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
enum 
{
	USER_DRV_KEY_INVALIDE = 0x00,
	USER_DRV_KEY_DOWM	= 0x01,
	USER_DRV_KEY_UP	= 0x02,
	USER_DRV_KEY_SHORT_PRESS = 0x03,
	USER_DRV_KEY_DOUBLE_PRESS	= 0x04,
	USER_DRV_KEY_LONG_PRESS	= 0x05,
};
enum
{
		USER_DRV_KEY_UP_LEVEL = 0x01,
		USER_DRV_KEY0_LEVEL = 0x02,
		USER_DRV_KEY1_LEVEL = 0x03,
		USER_DRV_KEY2_LEVEL = 0x04,
		USER_DRV_KEY_MAX ,
};
/*! */
typedef struct{
	uint8_t keyPressStatus[USER_DRV_KEY_MAX];
	uint16_t	keyPressDowmTime[10];
	uint16_t KeyPressReleaseTime[10];	
	uint8_t KeyPressDowmCount;
}user_key_status_t;

extern user_key_status_t user_key;
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void User_Key_Init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */


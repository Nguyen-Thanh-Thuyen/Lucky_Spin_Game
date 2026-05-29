/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_RED_1_Pin GPIO_PIN_13
#define LED_RED_1_GPIO_Port GPIOC
#define L7SEG_0_Pin GPIO_PIN_1
#define L7SEG_0_GPIO_Port GPIOA
#define L7SEG_1_Pin GPIO_PIN_2
#define L7SEG_1_GPIO_Port GPIOA
#define L7SEG_2_Pin GPIO_PIN_3
#define L7SEG_2_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOA
#define LOAD_Pin GPIO_PIN_6
#define LOAD_GPIO_Port GPIOA
#define SDK_Pin GPIO_PIN_7
#define SDK_GPIO_Port GPIOA
#define SDO_Pin GPIO_PIN_0
#define SDO_GPIO_Port GPIOB
#define mode_button_Pin GPIO_PIN_9
#define mode_button_GPIO_Port GPIOA
#define spin_button_Pin GPIO_PIN_10
#define spin_button_GPIO_Port GPIOA
#define select_button_Pin GPIO_PIN_11
#define select_button_GPIO_Port GPIOA
#define list_button_Pin GPIO_PIN_12
#define list_button_GPIO_Port GPIOA
#define LED_WIN_Pin GPIO_PIN_4
#define LED_WIN_GPIO_Port GPIOB
#define LED_LOSE_Pin GPIO_PIN_5
#define LED_LOSE_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

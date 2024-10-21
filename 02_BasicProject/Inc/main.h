/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
// #include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#if defined __has_include
  #if __has_include("stm32l4xx_hal.h")
    #include "stm32l4xx_hal.h"
  #endif
#else
  #include "stm32l4xx_hal.h"
#endif
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCKR_STATUS_INT1_Pin GPIO_PIN_0
#define LCKR_STATUS_INT1_GPIO_Port GPIOA
#define LCKR_CTRL_MUX_S3_Pin GPIO_PIN_1
#define LCKR_CTRL_MUX_S3_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define LCKR_CTRL_MUX_E1_Pin GPIO_PIN_3
#define LCKR_CTRL_MUX_E1_GPIO_Port GPIOA
#define LCKR_CTRL_MUX_E2_Pin GPIO_PIN_4
#define LCKR_CTRL_MUX_E2_GPIO_Port GPIOA
#define EXT_BUZZER_Pin GPIO_PIN_5
#define EXT_BUZZER_GPIO_Port GPIOA
#define LCKR_PWR_SW_Pin GPIO_PIN_6
#define LCKR_PWR_SW_GPIO_Port GPIOA
#define EXT_BTN_Pin GPIO_PIN_0
#define EXT_BTN_GPIO_Port GPIOB
#define LCKR_CTRL_MUX_COM_Pin GPIO_PIN_1
#define LCKR_CTRL_MUX_COM_GPIO_Port GPIOB
#define LCKR_CTRL_MUX_S0_Pin GPIO_PIN_8
#define LCKR_CTRL_MUX_S0_GPIO_Port GPIOA
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define LCKR_CTRL_MUX_S1_Pin GPIO_PIN_11
#define LCKR_CTRL_MUX_S1_GPIO_Port GPIOA
#define RS485_RE_Pin GPIO_PIN_12
#define RS485_RE_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define EXT_LED_Pin GPIO_PIN_3
#define EXT_LED_GPIO_Port GPIOB
#define LCKR_CTRL_MUX_S2_Pin GPIO_PIN_5
#define LCKR_CTRL_MUX_S2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

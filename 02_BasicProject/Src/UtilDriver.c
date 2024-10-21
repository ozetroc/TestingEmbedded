/**
 * @file UtilDriver.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief GPIO driver for different functions
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "UtilDriver.h"

#include "main.h"

void UtilDriver_PWR(bool enable) {
    HAL_GPIO_WritePin(LCKR_PWR_SW_GPIO_Port, LCKR_PWR_SW_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void UtilDriver_Delay(uint32_t ms) {
    HAL_Delay(ms);
}

uint32_t UtilDriver_GetTick(void) {
    return HAL_GetTick();
}

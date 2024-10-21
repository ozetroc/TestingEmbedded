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

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Set LCKR_PWR_SW pin
 *
 * @param enable true/false to set/reset pin
 */ 
void UtilDriver_PWR(bool enable);

/**
 * @brief HAL_Delay blocking wrapper
 * 
 * @param ms Delay in ms
 */
void UtilDriver_Delay(uint32_t ms);

/**
 * @brief HAL_GetTick wrapper
 * 
 * @return Current system tick in ms
 */
uint32_t UtilDriver_GetTick(void);

/**
 * @file PowerManager.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module controlling management of the power
 * @details Requirements:
 * @details 1.0) Module should not be initialized multiple times
 * @details 1.1) There should be a possibility to enable and disable the main 12V power
 * @details 1.2) Main power 12V should be enabled during the startup
 * @details 1.3) There should be a possibility to check status of main 12V
 * @details 1.4) There should be a possibility to check main AC status
 *
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#define _INIT_PM_OK    0
#define _INIT_PM_FAIL  1

/**
 * @brief   Initialize PowerManager module
 * @details This function does not enable main 12V power
 *
 * @retval uint8_t 0 on success, error code otherwise
 */
uint8_t PowerManager_Init(void);

/**
 * @brief Enable main 12V supply
 * 
 * @retval uint8_t 0 on success, error code otherwise
 */
uint8_t PowerManager_Enable12V(void);

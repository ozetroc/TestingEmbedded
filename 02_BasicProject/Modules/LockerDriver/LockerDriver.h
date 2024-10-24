/**
 * @file LockerDriver.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module controlling outputs for the lockers
 * @details Requirements:
 * 
 * 
 * 1.0) All mux pins should be set correctly during initialization of the module
 * 
 * 1.1) Module should not be initialized multiple times
 * 
 * 1.2) Only one locker should be opened at once
 * 
 * 1.3) There are 24 lockers on the PCB
 * 
 * 1.4) Locker should be opened for maximum of 2 seconds with accuracy +-0.5s to
 * protect electric lock
 * 
 * 1.5) There should be a command (API) to open all locker
 * one by one in a sequence
 * 
 * 1.6) There should be a command (API) to interrupt
 * any active opening sequence (single or open all) and disable output
 * 
 * 1.7)(extra) Locker output should be deactivated when locker open event is
 * detected
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

#define NUMBER_OF_LOCKERS 24

#define MAX_CONTROL_TIME 2000

#define _INIT_LD_OK    0
#define _INIT_LD_FAIL  1
#define _LD_ERROR   2

/**
 * @brief   Initialize LockerDriver module
 *
 * @retval  0 on success, error code otherwise
 */
uint8_t LockerDriver_Init(void);

/**
 * @brief Deinitialize
 * 
 * @return uint8_t 
 */
uint8_t LockerDriver_DeInit(void);


/**
 * @brief Open specific locker
 * 
 * @param LockerNum 
 * @return uint8_t 
 */
uint8_t LockerDriver_OpenLocker(uint8_t LockerNum);

/**
 * @brief Main loop of locker driver
 * 
 */
void LockerDriver_Loop(void);

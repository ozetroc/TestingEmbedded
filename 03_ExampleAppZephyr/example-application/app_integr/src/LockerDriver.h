/**
 * @file LockerDriver.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module controlling outputs for the lockers
 * @details Requirements:
 * 
 * 
 * 1.0) All mux pins should be set correctly during initialization of the module
 * 
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

/** Number of lockers to be handled by the module */
#define NO_OF_LOCKERS 24

/** Max control time of the locker in [ms] */
#define MAX_CONTROL_TIME_MS 2000

#define LCKR_DRIVER_PERIOD 200

/**
 * @brief   Initialize LockerDriver module
 *
 * @retval  0 on success, error code otherwise
 */
uint8_t LockerDriver_Init(void);

/**
 * @brief Main loop to control working of LockerDriver
 *
 */
void LockerDriver_Loop(void);

/**
 * @brief Non-blocking API for opening specified locker
 *
 * @param LockerNum Number of the locker to be opened
 * @return uint8_t Success (0) or error number
 */
uint8_t LockerDriver_OpenLocker(uint8_t LockerNum);

/**
 * @brief Blocking API for opening specified locker
 *
 * @param LockerNum Number of the locker to be opened
 * @return uint8_t Success (0) or error number
 */
uint8_t LockerDriver_OpenLockerBlocking(uint8_t LockerNum);

/**
 * @brief Open all lockers in a sequence
 *
 * @return uint8_t Success (0) or error number
 * (1) - Invalid argument
 * (2) - Control already in progress
 */
uint8_t LockerDriver_OpenAllLockers(void);

/**
 * @brief Immidately disable all opening sequences and outputs
 *
 */
void LockerDriver_DisableAllOutputs(void);

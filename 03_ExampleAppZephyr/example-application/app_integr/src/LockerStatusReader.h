/**
 * @file LockerStatusReader.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module status of the lockers
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

/** Max control time of the locker in [ms] */
#define LCKR_STATUS_RDR_PERIOD 200

/**
 * @brief   Initialize LockerStatusReader module
 *
 * @retval  0 on success, error code otherwise
 */
uint8_t LockerStatusReader_Init(void);

/**
 * @brief Main loop to control working of LockerStatusReader
 *
 */
void LockerStatusReader_Loop(void);

/**
 * @brief Read status of the specific locker
 * 
 * @param locker Number of the locker
 * @return 1 Locker opened
 * @return 0 Locker closed
 * @return -1 Error during reading of the status
 */
int LockerStatusReader_GetLockerStatus(uint8_t locker);



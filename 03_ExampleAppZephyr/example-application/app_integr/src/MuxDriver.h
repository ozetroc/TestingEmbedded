/**
 * @file MuxDriver.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Contains simple HAL wrapper for manipulating GPIOs for muxers
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    MuxGpio_S0,
    MuxGpio_S1,
    MuxGpio_S2,
    MuxGpio_S3,
    MuxGpio_E1,
    MuxGpio_E2,
    MuxGpio_COM,
    MuxGpio_Count,
} MuxGpio_t;

/**
 * @brief Initialize MuxDriver module
 *
 */
int MuxDriver_Init(void);

/**
 * @brief Set specific pin using the HAL functions
 *
 * @param GpioPin Pin to set the state
 * @param enable true/false to set/reset pin
 * @return uint8_t Return 0 if success, error otherwise
 */
uint8_t MuxDriver_SetGpio(MuxGpio_t GpioPin, bool enable);

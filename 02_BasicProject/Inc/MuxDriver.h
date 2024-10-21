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
void MuxDriver_Init(void);

/**
 * @brief Set specific pin using the HAL functions
 *
 * @param GpioPin Pin to set the state
 * @param enable true/false to set/reset pin
 * @return uint8_t Return 0 if success, error otherwise
 */
uint8_t MuxDriver_SetGpio(MuxGpio_t GpioPin, bool enable);

/**
 * @brief Set S0 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_S0(bool enable);

/**
 * @brief Set S1 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_S1(bool enable);

/**
 * @brief Set S2 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_S2(bool enable);

/**
 * @brief Set S3 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_S3(bool enable);

/**
 * @brief Set E1 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_E1(bool enable);

/**
 * @brief Set E2 pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_E2(bool enable);

/**
 * @brief Set COM pin using the HAL functions
 *
 * @param enable true/false to set/reset pin
 */
void MuxDriver_COM(bool enable);

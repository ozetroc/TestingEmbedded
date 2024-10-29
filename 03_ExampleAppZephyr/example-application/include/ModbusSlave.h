/**
 * @file ModbusSlave.h
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Contains Modbus RTU slave implementation
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initialize Modbus RTU slave
 * 
 */
int ModbusSlave_Init(void);

/**
 * @file MuxDriver.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Contains simple HAL wrapper for manipulating GPIOs for muxers
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 *
 */

#include "MuxDriver.h"

#include "main.h"
#include "stdio.h"

void MuxDriver_Init(void) {
    printf("MuxDriver Initialized \r\n");
}

uint8_t MuxDriver_SetGpio(MuxGpio_t GpioPin, bool enable) {
    switch (GpioPin) {
        case MuxGpio_S0:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_S0_GPIO_Port, LCKR_CTRL_MUX_S0_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_S1:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_S1_GPIO_Port, LCKR_CTRL_MUX_S1_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_S2:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_S2_GPIO_Port, LCKR_CTRL_MUX_S2_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_S3:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_S3_GPIO_Port, LCKR_CTRL_MUX_S3_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_E1:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_E1_GPIO_Port, LCKR_CTRL_MUX_E1_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_E2:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_E2_GPIO_Port, LCKR_CTRL_MUX_E2_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case MuxGpio_COM:
            HAL_GPIO_WritePin(LCKR_CTRL_MUX_COM_GPIO_Port,
                              LCKR_CTRL_MUX_COM_Pin,
                              enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        default:
            return 1;
    }
    return 0;
}

void MuxDriver_S0(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_S0_GPIO_Port, LCKR_CTRL_MUX_S0_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver_S1(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_S1_GPIO_Port, LCKR_CTRL_MUX_S1_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver_S2(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_S2_GPIO_Port, LCKR_CTRL_MUX_S2_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver_S3(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_S3_GPIO_Port, LCKR_CTRL_MUX_S3_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver_E1(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_E1_GPIO_Port, LCKR_CTRL_MUX_E1_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver2_E2(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_E2_GPIO_Port, LCKR_CTRL_MUX_E2_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void MuxDriver_COM(bool enable) {
    HAL_GPIO_WritePin(LCKR_CTRL_MUX_COM_GPIO_Port, LCKR_CTRL_MUX_COM_Pin,
                      enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**
 * @file PowerManager.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module controlling management of the power
 *
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "PowerManager.h"

#include <stdio.h>

#include "UtilDriver.h"

bool isInitializedPM = false;

uint8_t PowerManager_Init(void) {
    if (isInitializedPM) {
        printf("PowerManager already Initialized \r\n");
        return _INIT_PM_FAIL;
    }

    printf("PowerManager Initialized \r\n");
    isInitializedPM = true;

    return _INIT_PM_OK;
}

uint8_t PowerManager_Enable12V(void) {
    UtilDriver_PWR(true);

    return 0;
}

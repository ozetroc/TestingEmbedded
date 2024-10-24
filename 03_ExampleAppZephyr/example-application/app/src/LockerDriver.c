/**
 * @file LockerDriver.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module controlling outputs for the lockers
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "LockerDriver.h"
#include "LockerStatusReader.h"
#include "main.h"

#include <stdio.h>
#include <zephyr/logging/log.h>

#include "MuxDriver.h"
#include "UtilDriver.h"

LOG_MODULE_REGISTER(lckr_drv, LOG_LEVEL_INF);

bool isInitialized = false;

/**
 * @brief Truth table for config of Mux GPIOs
 *
 * @details  * Truth table for controlling each of the outputs:
 * +========+=====+=====+====+====+====+====+
 * | Locker | \E1 | \E2 | S0 | S1 | S2 | S3 |
 * +========+=====+=====+====+====+====+====+
 * |   1    |  0  |  1  | 0  | 0  | 0  | 0  |
 * |   2    |  0  |  1  | 0  | 0  | 0  | 1  |
 * |   3    |  0  |  1  | 0  | 0  | 1  | 0  |
 * |   4    |  0  |  1  | 0  | 0  | 1  | 1  |
 * |   5    |  0  |  1  | 0  | 1  | 0  | 0  |
 * |   6    |  0  |  1  | 0  | 1  | 0  | 1  |
 * |   7    |  0  |  1  | 0  | 1  | 1  | 0  |
 * |   8    |  0  |  1  | 0  | 1  | 1  | 1  |
 * |   9    |  1  |  0  | 0  | 0  | 0  | 0  |
 * |   10   |  1  |  0  | 0  | 0  | 0  | 1  |
 * |   11   |  1  |  0  | 0  | 0  | 1  | 0  |
 * |   12   |  1  |  0  | 0  | 0  | 1  | 1  |
 * |   13   |  1  |  0  | 0  | 1  | 0  | 0  |
 * |   14   |  1  |  0  | 0  | 1  | 0  | 1  |
 * |   15   |  1  |  0  | 0  | 1  | 1  | 0  |
 * |   16   |  0  |  1  | 1  | 1  | 0  | 0  |
 * |   17   |  0  |  1  | 1  | 0  | 1  | 1  |
 * |   18   |  0  |  1  | 1  | 0  | 1  | 0  |
 * |   19   |  0  |  1  | 1  | 0  | 0  | 1  |
 * |   20   |  0  |  1  | 1  | 0  | 0  | 0  |
 * |   21   |  1  |  0  | 0  | 1  | 1  | 1  |
 * |   22   |  1  |  0  | 1  | 0  | 0  | 0  |
 * |   23   |  1  |  0  | 1  | 0  | 0  | 1  |
 * |   24   |  1  |  0  | 1  | 0  | 1  | 0  |
 * +--------+-----+-----+----+----+----+----+
 */

uint8_t LockerDriver_Init(void) {
    if (isInitialized) {
        printf("LockerDriver already Initialized! \r\n");
        return 1;
    }

    isInitialized = true;
    LOG_INF("LockerDriver Initialized");

    return 0;
}

/**
 * @brief Main control loop of the LockerDriver module
 * @details Should be executed periodically with 2-10Hz frequency
 *
 */
void LockerDriver_Loop(void) {
    if (isInitialized) {
    }
}

static void mainThreadLockerDriver(void){
    do {
        k_msleep(500);
    } while (!isInitialized);

    LOG_INF("mainThreadLockerDriver entered");

    while(1) {
        k_msleep(LCKR_DRIVER_PERIOD);
        LockerDriver_Loop();
    }
}

K_THREAD_DEFINE(lckrdriver_id, STACKSIZE, mainThreadLockerDriver, NULL, NULL, NULL,
		PRIORITY, 0, 0);

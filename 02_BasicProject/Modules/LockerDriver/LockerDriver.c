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

#include <stdio.h>

#include "MuxDriver.h"
#include "UtilDriver.h"

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

bool isInitializedLD = false;
bool isControlOngoing = false;
uint32_t controlStartTick = 0;

typedef struct {
    uint8_t s : 4;
    uint8_t bnk : 1;
} gpio_ctrl_cfg;

const gpio_ctrl_cfg ctrl_config[24] = {
    {0, 0},  {1, 0},  {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0},
    {0, 1},  {1, 1},  {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {12, 0},
    {11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 1}, {8, 1}, {9, 1}, {10, 1}};


static void resetMuxControl(void);

uint8_t LockerDriver_Init(void) {
    if (isInitializedLD) {
        printf("PowerManager already Initialized \r\n");
        return _INIT_LD_FAIL;
    }

    resetMuxControl();

    printf("LockerDriver Initialized \r\n");
    isInitializedLD = true;

    return _INIT_LD_OK;
}

uint8_t LockerDriver_DeInit(void) {
    resetMuxControl();
    isInitializedLD = false;
    isControlOngoing = false;
    return 0;
}

uint8_t LockerDriver_OpenLocker(uint8_t LockerNum) {

    gpio_ctrl_cfg locker_cfg = {0};

    if(!isInitializedLD || LockerNum > NUMBER_OF_LOCKERS || isControlOngoing)
        return _LD_ERROR;
    
    // 
    resetMuxControl();

    // Take data
    locker_cfg = ctrl_config[LockerNum - 1];

    // Control
    if(locker_cfg.s & 1)
        MuxDriver_SetGpio(MuxGpio_S0, true);
    if(locker_cfg.s & 2)
        MuxDriver_SetGpio(MuxGpio_S1, true);
    if(locker_cfg.s & 4)
        MuxDriver_SetGpio(MuxGpio_S2, true);
    if(locker_cfg.s & 8)
        MuxDriver_SetGpio(MuxGpio_S3, true);

    MuxDriver_SetGpio(MuxGpio_COM, true);

    if(locker_cfg.bnk)
        MuxDriver_SetGpio(MuxGpio_E2, false);
    else
        MuxDriver_SetGpio(MuxGpio_E1, false);

    controlStartTick = UtilDriver_GetTick();
    isControlOngoing = true;

    return 0;
}

void LockerDriver_Loop(void) {
    if(isInitializedLD) {
        if(isControlOngoing) {
            if(UtilDriver_GetTick() - controlStartTick > MAX_CONTROL_TIME) {
                resetMuxControl();
                isControlOngoing = false;
                controlStartTick = 0;
            }
        }
    }
}

static void resetMuxControl(void) {
    // Set neutral states
    MuxDriver_SetGpio(MuxGpio_COM, false);
    MuxDriver_SetGpio(MuxGpio_E1, true);
    MuxDriver_SetGpio(MuxGpio_E2, true);
    MuxDriver_SetGpio(MuxGpio_S0, false);
    MuxDriver_SetGpio(MuxGpio_S1, false);
    MuxDriver_SetGpio(MuxGpio_S2, false);
    MuxDriver_SetGpio(MuxGpio_S3, false);
}

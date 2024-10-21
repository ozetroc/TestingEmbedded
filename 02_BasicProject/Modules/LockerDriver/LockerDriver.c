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

uint8_t LockerDriver_Init(void) {
    printf("LockerDriver Initialized \r\n");
    return 0;
}

/**
 * @file LockerStatusReader.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Module status of the lockers
 *
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "LockerStatusReader.h"

#include <stdio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

#include "main.h"

LOG_MODULE_REGISTER(lckr_stat, LOG_LEVEL_INF);

#define BANK1_I2C_ADDR 0x20
#define BANK2_I2C_ADDR 0x23

uint8_t lockers_status_bank1[2];
uint8_t lockers_status_bank2[2];
const struct device *i2c_dev;

/**
 * @brief Struct holding configuration for single locker bnk (which bank to
 * use), s (which channel to select)
 *
 */
typedef struct {
    uint8_t pin : 3;
    uint8_t port : 1;
    uint8_t bnk : 1;
} locker_status_cfg;

const locker_status_cfg status_config[28] = {
    {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}, {5, 0, 0},
    {6, 0, 0}, {7, 0, 0}, {0, 0, 1}, {1, 0, 1}, {2, 0, 1}, {3, 0, 1},
    {4, 0, 1}, {5, 0, 1}, {6, 0, 1}, {0, 1, 0}, {1, 1, 0}, {2, 1, 0},
    {3, 1, 0}, {4, 1, 0}, {7, 0, 1}, {0, 1, 1}, {1, 1, 1}, {2, 1, 1},
    {3, 1, 1}, {5, 1, 0}, {6, 1, 0}, {7, 1, 1}};

bool isInitializedLsr = false;

static int readBank1(void) {
    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C: Device is not ready.\n");
        return -1;
    }

    uint8_t write_buf = 0x00;

    int res = i2c_write_read(i2c_dev, BANK1_I2C_ADDR, &write_buf, 1,
                             &lockers_status_bank1, 2);

    return res;
}

static int readBank2(void) {
    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C: Device is not ready.\n");
        return -1;
    }

    uint8_t write_buf = 0x00;

    int res = i2c_write_read(i2c_dev, BANK2_I2C_ADDR, &write_buf, 1,
                             &lockers_status_bank2, 2);

    return res;
}

uint8_t LockerStatusReader_Init(void) {
    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));

    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C: Device is not ready.");
        return 1;
    } else {
        LOG_INF("I2C: Device is ready.");
    }

    LOG_INF("LockerStatusReader initialized");
    isInitializedLsr = true;
    return 0;
};

int LockerStatusReader_GetLockerStatus(uint8_t locker) {
    if(!isInitializedLsr)
        return -1;

    uint8_t port = status_config[locker-1].bnk ? lockers_status_bank2[status_config[locker-1].port] : lockers_status_bank1[status_config[locker-1].port];
	bool pin_status = port & (1<<status_config[locker-1].pin);
	return pin_status;
}

static void loopLockerStatusReader(void) {
    do {
        k_msleep(500);
    } while (!isInitializedLsr);
    LOG_INF("loopLockerStatusReader entered");
    int ret;

    while (1) {
        k_msleep(LCKR_STATUS_RDR_PERIOD);
        ret = readBank1();
        if (ret)
            LOG_ERR("Error reading i2c");
        ret = readBank2();
        if (ret)
            LOG_ERR("Error reading i2c");
        LOG_DBG("%x - %x - %x - %x", lockers_status_bank1[0],
                lockers_status_bank1[1], lockers_status_bank2[0],
                lockers_status_bank2[1]);
    }
}

K_THREAD_DEFINE(lckrstatrdr_id, STACKSIZE, loopLockerStatusReader, NULL, NULL,
                NULL, PRIORITY, 0, 0);

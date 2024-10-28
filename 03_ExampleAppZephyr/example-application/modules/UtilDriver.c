/**
 * @file UtilDriver.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief GPIO driver for different functions
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "UtilDriver.h"

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(util_drv, LOG_LEVEL_INF);

/* The devicetree node identifier for the "pwrsw" alias. */
#define PWRSW_NODE DT_ALIAS(pwrsw)

static const struct gpio_dt_spec power_sw = GPIO_DT_SPEC_GET(PWRSW_NODE, gpios);

int UtilDriver_Init(void) {
    int ret;
    if (!gpio_is_ready_dt(&power_sw)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&power_sw, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 0;
    }
    LOG_INF("UtilDriver Initialized");

    UtilDriver_PWR(false);

    return 0;
}

void UtilDriver_PWR(bool enable) {
    gpio_pin_set_dt(&power_sw, enable);
}

void UtilDriver_Delay(uint32_t ms) {
    k_sleep(K_MSEC(ms));
}

uint32_t UtilDriver_GetTick(void) {
    return k_uptime_get_32();
}
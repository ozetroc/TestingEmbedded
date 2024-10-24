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

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "stdio.h"

LOG_MODULE_REGISTER(mux_drv, LOG_LEVEL_INF);

// Muxes pins
#define MUX_S0_NODE DT_ALIAS(ctrlmuxs1)
#define MUX_S1_NODE DT_ALIAS(ctrlmuxs2)
#define MUX_S2_NODE DT_ALIAS(ctrlmuxs3)
#define MUX_S3_NODE DT_ALIAS(ctrlmuxs4)
#define MUX_E1_NODE DT_ALIAS(ctrlmuxen1)
#define MUX_E2_NODE DT_ALIAS(ctrlmuxen2)
#define MUX_COM_NODE DT_ALIAS(ctrlmuxcom)

static const struct gpio_dt_spec mux_s0_pin =
    GPIO_DT_SPEC_GET(MUX_S0_NODE, gpios);
static const struct gpio_dt_spec mux_s1_pin =
    GPIO_DT_SPEC_GET(MUX_S1_NODE, gpios);
static const struct gpio_dt_spec mux_s2_pin =
    GPIO_DT_SPEC_GET(MUX_S2_NODE, gpios);
static const struct gpio_dt_spec mux_s3_pin =
    GPIO_DT_SPEC_GET(MUX_S3_NODE, gpios);
static const struct gpio_dt_spec mux_e1_pin =
    GPIO_DT_SPEC_GET(MUX_E1_NODE, gpios);
static const struct gpio_dt_spec mux_e2_pin =
    GPIO_DT_SPEC_GET(MUX_E2_NODE, gpios);
static const struct gpio_dt_spec mux_com_pin =
    GPIO_DT_SPEC_GET(MUX_COM_NODE, gpios);

int MuxDriver_Init(void) {
    int ret;
    if (!gpio_is_ready_dt(&mux_s0_pin) || !gpio_is_ready_dt(&mux_s1_pin) ||
        !gpio_is_ready_dt(&mux_s2_pin) || !gpio_is_ready_dt(&mux_s3_pin) ||
        !gpio_is_ready_dt(&mux_e1_pin) || !gpio_is_ready_dt(&mux_e2_pin) ||
        !gpio_is_ready_dt(&mux_com_pin)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&mux_s0_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_s1_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_s2_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_s3_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_e1_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_e2_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;
    ret = gpio_pin_configure_dt(&mux_com_pin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
        return 0;

    LOG_INF("MuxDriver initialized");

    return 0;
}

uint8_t MuxDriver_SetGpio(MuxGpio_t GpioPin, bool enable) {
    switch (GpioPin) {
        case MuxGpio_S0:
            LOG_DBG("Enable S0, %u", enable);
            gpio_pin_set_dt(&mux_s0_pin, enable);
            break;

        case MuxGpio_S1:
            LOG_DBG("Enable S1, %u", enable);
            gpio_pin_set_dt(&mux_s1_pin, enable);
            break;

        case MuxGpio_S2:
            LOG_DBG("Enable S2, %u", enable);
            gpio_pin_set_dt(&mux_s2_pin, enable);
            break;

        case MuxGpio_S3:
            LOG_DBG("Enable S3, %u", enable);
            gpio_pin_set_dt(&mux_s3_pin, enable);
            break;

        case MuxGpio_E1:
            LOG_DBG("Enable E1, %u", enable);
            gpio_pin_set_dt(&mux_e1_pin, enable);
            break;

        case MuxGpio_E2:
            LOG_DBG("Enable E2, %u", enable);
            gpio_pin_set_dt(&mux_e2_pin, enable);
            break;

        case MuxGpio_COM:
            LOG_DBG("Enable COM, %u", enable);
            gpio_pin_set_dt(&mux_com_pin, enable);
            break;

        default:
            return 1;
    }
    return 0;
}


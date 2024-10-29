/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <app/drivers/blink.h>

#include <app_version.h>

#include "MuxDriver.h"
#include "UtilDriver.h"
#include "LockerDriver.h"
#include "LockerStatusReader.h"
#include "ModbusSlave.h"

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U

int main(void)
{
	int ret;
	const struct device *sensor, *blink;

	printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

	sensor = DEVICE_DT_GET(DT_NODELABEL(example_sensor));
	if (!device_is_ready(sensor)) {
		LOG_ERR("Sensor not ready");
		return 0;
	}

	blink = DEVICE_DT_GET(DT_NODELABEL(blink_led));
	if (!device_is_ready(blink)) {
		LOG_ERR("Blink LED not ready");
		return 0;
	}

	ret = blink_off(blink);
	if (ret < 0) {
		LOG_ERR("Could not turn off LED (%d)", ret);
		return 0;
	}	
	// Sleep for 2s and wait for initialization of main loops of LockerDriver and LockerStatusReader
	k_sleep(K_MSEC(2000));

	printk("Use the sensor to change LED blinking period\n");

	ModbusSlave_Init();

	UtilDriver_Init();
	MuxDriver_Init();

	UtilDriver_PWR(true);

	// LockerStatusReader_Init();
	LockerDriver_Init();	

	// LockerDriver_OpenLockerBlocking(1);
	// LockerDriver_OpenLocker(6);

	LOG_INF("Hello World");

	blink_set_period_ms(blink, BLINK_PERIOD_MS_MAX);
	while (1) {

		k_sleep(K_MSEC(100));
	}

	return 0;
}


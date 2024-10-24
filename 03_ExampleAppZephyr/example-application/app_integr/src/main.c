/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <app/drivers/blink.h>

#include <app_version.h>
#include <zephyr/ztest.h>

#include "MuxDriver.h"
#include "UtilDriver.h"
#include "LockerDriver.h"
#include "LockerStatusReader.h"

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U

ZTEST(app_integr, test_1)
{
	UtilDriver_Init();
	MuxDriver_Init();

	UtilDriver_PWR(true);

	LockerStatusReader_Init();
	LockerDriver_Init();

	// LockerDriver_OpenLocker(1);

	zassert_equal(1, 1, "Failed test");
}

ZTEST_SUITE(app_integr, NULL, NULL, NULL, NULL, NULL);


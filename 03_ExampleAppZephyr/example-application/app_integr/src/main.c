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

bool testLockersOneToFive(void);

#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U

ZTEST(app_integr, test_1)
{
	UtilDriver_Init();
	MuxDriver_Init();

	UtilDriver_PWR(true);

	LockerStatusReader_Init();
	LockerDriver_Init();

	LOG_INF("Testing ...");

	// Sleep for 2s and wait for initialization of main loops of LockerDriver and LockerStatusReader
	k_sleep(K_MSEC(2000));

	// Integration test for functionality of lockers 1-5
	bool res = testLockersOneToFive();

	zassert_equal(true, res, "Failed test");
}

ZTEST_SUITE(app_integr, NULL, NULL, NULL, NULL, NULL);

bool testLockersOneToFive(void) {
	int res = 0;
	bool test_result = true;

	for (int i = 1 ; i <=5 ; i++) {
		LOG_INF("Testing locker %d", i);

		res = LockerStatusReader_GetLockerStatus(i);
		zassert_equal(true, res, "[1.1.%d] Failed initial reading of locker status.");

		res = LockerDriver_OpenLocker(i);
		zassert_equal(0, res, "[1.2.%d] Failed opening locker.");

		k_sleep(K_MSEC(500));

		res = LockerStatusReader_GetLockerStatus(i);
		zassert_equal(false, res, "[1.3.%d] Failed reading of locker status after activating output.");

		// Test harness constructed this way, that output should be deactivated after 2s.
		k_sleep(K_MSEC(2000));

		res = LockerStatusReader_GetLockerStatus(i);
		zassert_equal(true, res, "[1.4.%d] Failed reading of locker status after deactivating output.");
	}

	LOG_INF("Hello World");

	return test_result;

}


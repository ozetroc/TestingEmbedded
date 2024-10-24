#include <stdbool.h>
#include <stdlib.h>

#include "PowerManager.h"
#include "fff.h"
#include "unity.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(UtilDriver_PWR, bool);

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_PowerManagerInit(void) {
    // Execute init of LockerDriver module
    uint8_t ret = PowerManager_Init();

    // Check if returns _INIT_OK
    TEST_ASSERT_EQUAL_INT(_INIT_PM_OK, ret);

    // Call init functions second time
    ret = PowerManager_Init();

    // [Req 1.0] Check if returns _INIT_FAIL
    TEST_ASSERT_EQUAL_INT(_INIT_PM_FAIL, ret);
}

void test_PowerManagerEnable12V(void) {
    // Execute init of LockerDriver module
    PowerManager_Init();

    // Execute enable 12V power supply
    uint8_t ret = PowerManager_Enable12V();

    // [Req 1.1] Check thet main 12V power was enabled
    TEST_ASSERT_EQUAL_INT(1, UtilDriver_PWR_fake.call_count);
    TEST_ASSERT_TRUE(UtilDriver_PWR_fake.arg0_val);

    // Check if returns _INIT_OK
    TEST_ASSERT_EQUAL_INT(_INIT_PM_OK, ret);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_PowerManagerInit);
    RUN_TEST(test_PowerManagerEnable12V);
    return UNITY_END();
}

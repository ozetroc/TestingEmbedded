#include <stdbool.h>
#include <stdlib.h>

#include "LockerDriver.h"
#include "MuxDriver.h"
#include "fff.h"
#include "unity.h"

DEFINE_FFF_GLOBALS;

#define NUMBER_OF_PINS_TO_SET_DEFAULT 7

FAKE_VALUE_FUNC(uint8_t, MuxDriver_SetGpio, MuxGpio_t, bool);
FAKE_VALUE_FUNC(uint32_t, UtilDriver_GetTick);

static bool verifyMuxGpioInitialSettings(MuxGpio_t GpioPin, bool enable);

void setUp(void) {
    // set stuff up here
    RESET_FAKE(MuxDriver_SetGpio);
    RESET_FAKE(UtilDriver_GetTick);
}

void tearDown(void) {
    // clean stuff up here
    LockerDriver_DeInit();
}

void test_LockerDriverInit(void) {
    // Execute init of LockerDriver module
    uint8_t ret = LockerDriver_Init();

    // Check if returns _INIT_OK
    TEST_ASSERT_EQUAL_INT(_INIT_LD_OK, ret);

    // Check if executed 7 times
    TEST_ASSERT_EQUAL_INT(NUMBER_OF_PINS_TO_SET_DEFAULT,
                          MuxDriver_SetGpio_fake.call_count);

    // [Req 1.0] Check if GPIO were set with correct states
    for (int i = 0; i < MuxDriver_SetGpio_fake.call_count; i++) {
        TEST_ASSERT_TRUE(verifyMuxGpioInitialSettings(
            MuxDriver_SetGpio_fake.arg0_history[i],
            MuxDriver_SetGpio_fake.arg1_history[i]));
    }

    // Check if the all pins were setup TODO:

    // Call init functions second time
    ret = LockerDriver_Init();

    // [Req 1.1] Check if returns _INIT_FAIL
    TEST_ASSERT_EQUAL_INT(_INIT_LD_FAIL, ret);
}

void test_LockerDriverOpenLocker(void) {
    uint8_t ret = 0;

    ret = LockerDriver_OpenLocker(1);
    TEST_ASSERT_EQUAL_INT(_LD_ERROR, ret);

    // Execute init of LockerDriver module
    ret = LockerDriver_Init(); 
    TEST_ASSERT_EQUAL_INT(_INIT_LD_OK, ret);

    // Check if locker out of range
    ret = LockerDriver_OpenLocker(25);
    TEST_ASSERT_EQUAL_INT(_LD_ERROR, ret);

    RESET_FAKE(UtilDriver_GetTick);
    uint32_t returnTimeValues[3] = {0, 500, 2001};
    SET_RETURN_SEQ(UtilDriver_GetTick, returnTimeValues, 3);

    RESET_FAKE(MuxDriver_SetGpio);
    ret = LockerDriver_OpenLocker(1);
    // Check if executed 7 times
    TEST_ASSERT_EQUAL_INT(NUMBER_OF_PINS_TO_SET_DEFAULT + 2,
                          MuxDriver_SetGpio_fake.call_count);

    RESET_FAKE(MuxDriver_SetGpio);
    // Check @ time 500ms
    LockerDriver_Loop();
    TEST_ASSERT_EQUAL_INT(0,
                          MuxDriver_SetGpio_fake.call_count);

    // Check at time 2001ms
    LockerDriver_Loop();
    TEST_ASSERT_EQUAL_INT(NUMBER_OF_PINS_TO_SET_DEFAULT,
                          MuxDriver_SetGpio_fake.call_count);
    
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LockerDriverInit);
    RUN_TEST(test_LockerDriverOpenLocker);
    return UNITY_END();
}

static bool verifyMuxGpioInitialSettings(MuxGpio_t GpioPin, bool enable) {
    bool verdict = false;

    switch (GpioPin) {
        case MuxGpio_COM:  // intentional fallthrough
        case MuxGpio_S0:
        case MuxGpio_S1:
        case MuxGpio_S2:
        case MuxGpio_S3:
            if (enable == false)
                verdict = true;
            break;
        case MuxGpio_E1:
        case MuxGpio_E2:
            if (enable == true)
                verdict = true;
            break;

        default:
            break;
    }
    return verdict;
}

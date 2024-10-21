#include <stdbool.h>
#include <stdlib.h>

#include "LockerDriver.h"
#include "fff.h"
#include "unity.h"

DEFINE_FFF_GLOBALS;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_LockerDriverInit(void) {
    // Execute init of LockerDriver module
    LockerDriver_Init();

    TEST_ASSERT_EQUAL_INT(1, 1);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LockerDriverInit);
    return UNITY_END();
}


#ifndef MAIN_H
#define MAIN_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#endif
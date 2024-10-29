/**
 * @file ModbusSlave.c
 * @author Przemysław Gąsior (pgasior@sii.pl)
 * @brief Contains Modbus RTU slave implementation
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024 Przemysław Gąsior
 * @license The MIT License (MIT)
 */

#include "ModbusSlave.h"

#include <zephyr/logging/log.h>

#include "main.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/modbus/modbus.h>
#include "LockerDriver.h"

LOG_MODULE_REGISTER(mbs_slave, LOG_LEVEL_INF);

uint16_t holding_reg[8];

struct modbus_user_callbacks mbs_cbs = {
    .coil_rd = NULL,
    .coil_wr = NULL,
    .holding_reg_rd = NULL,
    .holding_reg_wr = NULL,
};

const struct modbus_iface_param server_param = {
    .mode = MODBUS_MODE_RTU,
    .server =
        {
            .user_cb = &mbs_cbs,
            .unit_id = 1,
        },
    .serial =
        {
            .baud = 115200,
            .parity = UART_CFG_PARITY_NONE,
        },
};

int callback_fcn(bool status) {
    LOG_INF("Callback fcn, %d", status);
    return 0;
}

#define MODBUS_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_modbus_serial)

static int coil_rd(uint16_t addr, bool *state);
static int coil_wr(uint16_t addr, bool state);
static int holding_reg_rd(uint16_t addr, uint16_t *reg);
static int holding_reg_wr(uint16_t addr, uint16_t reg);


int ModbusSlave_Init(void) {
    const char iface_name[] = {DEVICE_DT_NAME(MODBUS_NODE)};
    // const char iface_name[] = {DT_PROP(DT_INST(0, zephyr_modbus_serial), label)};
    int iface;

    mbs_cbs.coil_rd = coil_rd;
    mbs_cbs.coil_wr = coil_wr;
    mbs_cbs.holding_reg_rd = holding_reg_rd;
    mbs_cbs.holding_reg_wr = holding_reg_wr;

    iface = modbus_iface_get_by_name(iface_name);

    if (iface < 0) {
        LOG_ERR("Failed to get iface index for %s", iface_name);
        return iface;
    }

    int ret = modbus_init_server(iface, server_param);
    if (ret) {
        LOG_ERR("Modbus RTU server initialization failed");
    } else {
        LOG_INF("Modbus RTU server initialization successfull\n");
    }

    return ret;
}

static int coil_rd(uint16_t addr, bool *state)
{
	LOG_INF("Coil read, addr %u, %d", addr, (int)*state);

	return 0;
};

/**
 * @brief Write the coild
 * Address 1 to 24 - Open specific locker
 * Address 25 - Enable Aux output
 * 
 * @param addr 
 * @param reg 
 * @return int 
 */
static int coil_wr(uint16_t addr, bool state)
{
	// LOG_INF("Coil write, addr %u, %u", addr, state);

    if(state)
        LockerDriver_OpenLocker(addr);

	return 0;
};

/**
 * @brief Read the holding register
 * Address 0 bit 0 - All lockers closed
 * Address 0 bit 1 - AC power status
 * Address 0 bit 2 - Aux output status
 * Address 0 bit 3 - 12V power status
 * Address 1 - Status ready during and for update
 * 
 * @param addr 
 * @param reg 
 * @return int 
 */
int holding_reg_rd(uint16_t addr, uint16_t *reg)
{
	int ret = 0;

	LOG_INF("Holding register read, addr %u", addr);

	switch(addr)
	{
		case 0:
		ret = -ENOTSUP;
		break;

		case 1:
		ret = -ENOTSUP;
		break;

		default:
		ret = -ENOTSUP;
		break;
	}

	return ret;
};

/**
 * @brief Write the holding register
 * Address 1 bit 6 - Enable aux output
 * Address 1 bit 5 - Disable aux output
 * Address 1 bit 4 - Enable buzzer
 * Address 1 bit 3 - Disable buzzer
 * Address 2 - If true then start the update
 * Address 2 - If 0 then finilize the update
 * Address 3 - Add update image data to write
 * Address 4 - Request upgrade
 * Address 5 - Confirm image
 * Address 6 - System reset
 * 
 * @param addr 
 * @param reg 
 * @return int 
 */
int holding_reg_wr(uint16_t addr, uint16_t reg)
{
	int ret = 0;
	switch(addr)
	{
		case 1:
	        LOG_INF("Coil write, addr %u, %d", addr, reg);
			break;

		default:
		ret = -ENOTSUP;
		break;
	}

	return ret;
};

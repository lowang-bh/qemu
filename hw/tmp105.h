/*
 * Texas Instruments TMP105 Temperature Sensor
 *
 * Browse the data sheet:
 *
 *    http://www.ti.com/lit/gpn/tmp105
 *
 * Copyright (C) 2012 Alex Horn <alex.horn@cs.ox.ac.uk>
 * Copyright (C) 2008-2012 Andrzej Zaborowski <balrogg@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later. See the COPYING file in the top-level directory.
 */
#ifndef QEMU_TMP105_H
#define QEMU_TMP105_H

#include "i2c.h"
#include "tmp105_regs.h"

#define TYPE_TMP105 "tmp105"
#define TMP105(obj) OBJECT_CHECK(TMP105State, (obj), TYPE_TMP105)

/**
 * TMP105State:
 * @config: Bits 5 and 6 (value 32 and 64) determine the precision of the
 * temperature. See Table 8 in the data sheet.
 *
 * @see_also: http://www.ti.com/lit/gpn/tmp105
 */
typedef struct TMP105State {
    /*< private >*/
    I2CSlave i2c;
    /*< public >*/

    uint8_t len;
    uint8_t buf[2];
    qemu_irq pin;

    uint8_t pointer;
    uint8_t config;
    int16_t temperature;
    int16_t limit[2];
    int faults;
    uint8_t alarm;
} TMP105State;

/**
 * tmp105_set:
 * @i2c: dispatcher to TMP105 hardware model
 * @temp: temperature with 0.001 centigrades units in the range -40 C to +125 C
 *
 * Sets the temperature of the TMP105 hardware model.
 *
 * Bits 5 and 6 (value 32 and 64) in the register indexed by TMP105_REG_CONFIG
 * determine the precision of the temperature. See Table 8 in the data sheet.
 *
 * @see_also: I2C_SLAVE macro
 * @see_also: http://www.ti.com/lit/gpn/tmp105
 */
void tmp105_set(I2CSlave *i2c, int temp);

#endif

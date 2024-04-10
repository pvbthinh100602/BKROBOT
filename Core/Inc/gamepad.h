/*
 * gamepad.h
 *
 *  Created on: Apr 10, 2024
 *      Author: phamv
 */

#ifndef INC_GAMEPAD_H_
#define INC_GAMEPAD_H_

#include "i2c.h"
#include "gpio.h"

int gamepad_init();

void gamepad_update();

uint8_t gamepad_up();

uint8_t gamepad_down();

#endif /* INC_GAMEPAD_H_ */

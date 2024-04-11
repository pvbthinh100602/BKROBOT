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

int gamepad_calculate_leff_joystick();

void gamepad_run_tele();

#endif /* INC_GAMEPAD_H_ */

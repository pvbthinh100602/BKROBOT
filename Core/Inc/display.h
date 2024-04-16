/*
 * display.h
 *
 *  Created on: Apr 15, 2024
 *      Author: phamv
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "spi.h"
#include "gpio.h"

void display_init();

void display_run();

void display_7seg(int num);

#endif /* INC_DISPLAY_H_ */

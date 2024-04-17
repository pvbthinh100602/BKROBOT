/*
 * button.h
 *
 *  Created on: Apr 17, 2024
 *      Author: phamv
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "spi.h"
#include "gpio.h"

void button_init();
void button_scan();
int isButtonPressed(int index);

#endif /* INC_BUTTON_H_ */

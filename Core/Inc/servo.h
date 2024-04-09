/*
 * servo.h
 *
 *  Created on: Apr 9, 2024
 *      Author: phamv
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "tim.h"

#define SERVO1	0
#define SERVO2	1
#define SERVO3	2

void servo_init(int servo_id);

void servo_set_angle(int servo_id, int angle);

void testServo();
#endif /* INC_SERVO_H_ */

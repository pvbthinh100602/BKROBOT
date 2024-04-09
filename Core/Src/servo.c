/*
 * servo.c
 *
 *  Created on: Apr 9, 2024
 *      Author: phamv
 */

#include "servo.h"

uint32_t servo_channel[] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3};

void servo_init(int servo_id){
	HAL_TIM_PWM_Start(&htim4, servo_channel[servo_id]);
}

void servo_set_angle(int servo_id, int angle){
	if(angle < 0 || angle > 180) return;
	int duty = (angle*100)/180 + 25;
	__HAL_TIM_SET_COMPARE(&htim4, servo_channel[servo_id], duty);
}

int servo_count = 0;
int angle = 0;
void testServo(){
	servo_count++;
	if(servo_count == 500){
		servo_count = 0;
//		angle += 90;
		if(angle > 180) angle = 0;
		for(int i = 0; i < 3; i++){
			servo_set_angle(servo_channel[i],angle);
		}

	}
}

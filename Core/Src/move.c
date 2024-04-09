/*
 * move.c
 *
 *  Created on: Apr 10, 2024
 *      Author: HaHuyen
 */

#include "tim.h"
#include "main.h"

#define		UP			1
#define 	DOWN 		0
#define 	SPEED		60

uint8_t speed_duty_cycle = 0;

void setSpeed(uint8_t dc, uint8_t duty_cycle) {
	speed_duty_cycle = duty_cycle;
	switch (dc){
	case 1:
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, speed_duty_cycle);
		break;
	case 2:
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, speed_duty_cycle);
		break;
	case 3:
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, speed_duty_cycle);
		break;
	case 4:
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, speed_duty_cycle);
		break;
	}
}

void dc1Move(uint8_t duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, UP);
		setSpeed(1, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, DOWN);
		setSpeed(1, duty_cycle*-1);
	}
}

void dc2Move(uint8_t duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, UP);
		setSpeed(2, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, DOWN);
		setSpeed(2, duty_cycle*-1);
	}
}

void dc3Move(uint8_t duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, UP);
		setSpeed(3, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, DOWN);
		setSpeed(3, duty_cycle*-1);
	}
}

void dc4Move(uint8_t duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, UP);
		setSpeed(4, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, DOWN);
		setSpeed(4, duty_cycle*-1);
	}
}


void stop(){
	dc1Move(0);
	dc2Move(0);
	dc3Move(0);
	dc4Move(0);
}

void forward(){
	dc1Move(SPEED);
	dc2Move(SPEED);
	dc3Move(SPEED);
	dc4Move(SPEED);
}

void backwards(){
	dc1Move(-SPEED);
	dc2Move(-SPEED);
	dc3Move(-SPEED);
	dc4Move(-SPEED);
}

void frontLeft(){
	dc1Move(0); //stop
	dc2Move(SPEED);
	dc3Move(SPEED);
	dc4Move(0); //stop
}

void frontRight(){
	dc1Move(SPEED);
	dc2Move(0); //stop
	dc3Move(0); //stop
	dc4Move(SPEED);
}
void backRight(){
	dc1Move(0); //stop
	dc2Move(-SPEED);
	dc3Move(-SPEED);
	dc4Move(0); //stop
}

void backLeft(){
	dc1Move(-SPEED);
	dc2Move(0); //stop
	dc3Move(0); //stop
	dc4Move(-SPEED);

}

void right(){
	dc1Move(SPEED);
	dc2Move(-SPEED);
	dc3Move(-SPEED);
	dc4Move(SPEED);
}

void left(){
	dc1Move(-SPEED);
	dc2Move(SPEED);
	dc3Move(SPEED);
	dc4Move(-SPEED);
}

void rotateLeft(){
	dc1Move(-SPEED);
	dc2Move(-SPEED);
	dc3Move(SPEED);
	dc4Move(SPEED);
}

void rotateRight(){
	dc1Move(SPEED);
	dc2Move(SPEED);
	dc3Move(-SPEED);
	dc4Move(-SPEED);
}

uint8_t count_test = 10;
void testDc(){
	count_test--;
	if(count_test >= 7)
		forward();
	else if(count_test >= 5)
		backwards();
	else if(count_test >= 3)
		right();
	else if (count_test >=1)
		left();
	else
		count_test = 10;

}

/*
 * move.c
 *
 *  Created on: Apr 10, 2024
 *      Author: HaHuyen
 */

#include "move.h"
#include "tim.h"
#include "main.h"

#define		UP			1
#define 	DOWN 		0

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

void dc1Move(int duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, UP);
		setSpeed(1, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, DOWN);
		setSpeed(1, duty_cycle*-1);
	}
}

void dc2Move(int duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, UP);
		setSpeed(2, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, DOWN);
		setSpeed(2, duty_cycle*-1);
	}
}

void dc3Move(int duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, DOWN);
		setSpeed(3, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, UP);
		setSpeed(3, duty_cycle*-1);
	}
}

void dc4Move(int duty_cycle){
	if(duty_cycle >= 0){
		HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, DOWN);
		setSpeed(4, duty_cycle);
	}
	if(duty_cycle < 0){
		HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, UP);
		setSpeed(4, duty_cycle*-1);
	}
}


void stop(){
	dc1Move(0);
	dc2Move(0);
	dc3Move(0);
	dc4Move(0);
}

void forward(int speed){
	dc1Move(speed);
	dc2Move(speed);
	dc3Move(speed);
	dc4Move(speed);
}

void backwards(int speed){
	dc1Move(-speed);
	dc2Move(-speed);
	dc3Move(-speed);
	dc4Move(-speed);
}

void frontLeft(int speed){
	dc1Move(0); //stop
	dc2Move(speed);
	dc3Move(speed);
	dc4Move(0); //stop
}

void frontRight(int speed){
	dc1Move(speed);
	dc2Move(0); //stop
	dc3Move(0); //stop
	dc4Move(speed);
}
void backRight(int speed){
	dc1Move(0); //stop
	dc2Move(-speed);
	dc3Move(-speed);
	dc4Move(0); //stop
}

void backLeft(int speed){
	dc1Move(-speed);
	dc2Move(0); //stop
	dc3Move(0); //stop
	dc4Move(-speed);

}

void right(int speed){
	dc1Move(speed);
	dc2Move(-speed);
	dc3Move(-speed);
	dc4Move(speed);
}

void left(int speed){
	dc1Move(-speed);
	dc2Move(speed);
	dc3Move(speed);
	dc4Move(-speed);
}

void rotateLeft(int speed){
	dc1Move(-speed);
	dc2Move(-speed);
	dc3Move(speed);
	dc4Move(speed);
}

void rotateRight(int speed){
	dc1Move(speed);
	dc2Move(speed);
	dc3Move(-speed);
	dc4Move(-speed);
}

uint8_t count_test = 10;
void testDc(){
	count_test--;
	if(count_test >= 7)
		forward(MAX_SPEED);
	else if(count_test >= 5)
		backwards(MAX_SPEED);
	else if(count_test >= 3)
		right(MAX_SPEED);
	else if (count_test >=1)
		left(MAX_SPEED);
	else
		count_test = 10;

}

void runDir(int dir, int speed){
	switch (dir) {
		case ROBOT_DIR_FW:
			forward(speed);
			break;
		case ROBOT_DIR_SR:
			right(speed);
			break;
		case ROBOT_DIR_SL:
			left(speed);
			break;
		case ROBOT_DIR_L:
			rotateLeft(speed);
			break;
		case ROBOT_DIR_R:
			rotateRight(speed);
			break;
		case ROBOT_DIR_LB:
			backLeft(speed);
			break;
		case ROBOT_DIR_RB:
			backRight(speed);
			break;
		case ROBOT_DIR_LF:
			frontLeft(speed);
			break;
		case ROBOT_DIR_RF:
			frontRight(speed);
			break;
		case ROBOT_DIR_BW:
			backwards(speed);
			break;
		default:
			stop();
			break;
	}
}

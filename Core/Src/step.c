/*
 * step.c
 *
 *  Created on: Apr 10, 2024
 *      Author: HaHuyen
 */

#include "tim.h"
#include "main.h"

#define DUTY	50
#define SPR		200

int count_spr = 0;

void moveSM(int cycle){
	if(cycle >= 0){
		HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, GPIO_PIN_SET);
		count_spr = SPR * cycle;
	}
	if(cycle < 0){
		HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, GPIO_PIN_RESET);
		count_spr = SPR * cycle * -1;
	}
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, DUTY);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM3){
		count_spr--;
		if(count_spr <= 0)
			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
	}
}


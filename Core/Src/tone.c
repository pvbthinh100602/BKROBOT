/*
 * tone.c
 *
 *  Created on: Apr 16, 2024
 *      Author: phamv
 */

#include "tone.h"

void buzzer_start_freq(uint32_t frequency){
	if(frequency == 0) return;
	uint32_t timer_clock = 72000000;  // Example for APB1 timer
	uint32_t prescaler = 0;
	uint32_t period = (timer_clock / frequency) - 1;

	// Adjust prescaler if period is too large for 16-bit timer
	while (period > 65535) {
		prescaler++;
		period = (timer_clock / (prescaler + 1) / frequency) - 1;
	}

	__HAL_TIM_SET_PRESCALER(&htim5, prescaler);
	__HAL_TIM_SET_AUTORELOAD(&htim5, period);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1,period/2);

	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1); // Re-start PWM to apply changes
}

void buzzer_stop(){
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
}

//blocking function
void tone_play(int* note, int* dur, int len){
	for(int i = 0; i < len; i++){
		buzzer_start_freq(note[i]);
		HAL_Delay(dur[i]);
		buzzer_stop();
	}
}

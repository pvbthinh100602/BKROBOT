/*
 * tone.h
 *
 *  Created on: Apr 16, 2024
 *      Author: phamv
 */

#ifndef INC_TONE_H_
#define INC_TONE_H_

#include "tim.h"

#define NOTE_MUTE	0
#define NOTE_C5 523
#define NOTE_CS5	554
#define NOTE_D5	587
#define NOTE_DS5	622
#define NOTE_E5	659
#define NOTE_F5	698
#define NOTE_FS5	740
#define NOTE_G5	784
#define NOTE_GS5	831
#define NOTE_A5	880
#define NOTE_AS5	932
#define NOTE_B5	988

void buzzer_start_freq(uint32_t frequency);

void buzzer_stop();

#endif /* INC_TONE_H_ */

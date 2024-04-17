/*
 * sensor.c
 *
 *  Created on: Apr 17, 2024
 *      Author: phamv
 */

#include "sensor.h"

#define SENSOR_ERROR_RANGE	50

uint16_t sensor_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint16_t sensor_calib[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t line_status = 0;
uint8_t front_status = 0;


void SensorCalib(){
	HAL_ADC_Start_DMA(&hadc1, (void*)sensor_calib, 8);
}

void SensorScan(){
	HAL_ADC_Start_DMA(&hadc1, (void*)sensor_buffer, 8);
	uint8_t temp = 0;
	for(int i = 0; i < 8; i++){
		if(sensor_buffer[i] > sensor_calib[i] - 50 && sensor_buffer[i] < sensor_calib[i] + 50){
			temp = temp + 1;
		}
		temp = temp << 1;
	}
	switch (temp & 0b01111110) {
		case 0b00000000:
			line_status = LINE_END;
			break;
		case 0b01111110:
			line_status = LINE_CROSS;
			break;
		case 0b00011000:
			line_status = LINE_CENTER;
			break;
		case 0b00001100:
		case 0b00001000:
			line_status = LINE_RIGHT1;
			break;
		case 0b00000110:
		case 0b00000100:
			line_status = LINE_RIGHT2;
			break;
		case 0b00000011:
		case 0b00000010:
		case 0b00000001:
			line_status = LINE_RIGHT3;
			break;
		case 0b00110000:
		case 0b00010000:
			line_status = LINE_LEFT1;
			break;
		case 0b01100000:
		case 0b00100000:
			line_status = LINE_LEFT2;
			break;
		case 0b11000000:
		case 0b01000000:
		case 0b10000000:
			line_status = LINE_LEFT3;
			break;
		default:
			line_status = LINE_ERROR;
			break;
	}
}

uint8_t SensorGetLine(){
	return line_status;
}

/*
 * display.c
 *
 *  Created on: Apr 15, 2024
 *      Author: phamv
 */

#include "display.h"
#include "sensor.h"

uint8_t display_buffer[3] = {0, 0, 0};
uint8_t display_7seg_map[10] = { 0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41,
		0x1f, 0x01, 0x09 }; // 0->9
uint16_t display_index = 0;
uint8_t spi_buffer = 0xff;

void display_init() {
	HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);
}

void display_run() {

	spi_buffer = display_buffer[display_index];

	HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 0);
	HAL_SPI_Transmit(&hspi1, (void*) &spi_buffer, 1, 1);
	HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);

	switch (display_index) {
	case 0:
		HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 1);
		HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 0);
		HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 0);
		HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 1);
		HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 1);
		HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 1);
		HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 0);
		break;
	default:
		break;
	}
	display_index = (display_index + 1) % 3;
}

void display_7seg(int num){
	display_buffer[0] = display_7seg_map[num/10];
	display_buffer[1] = display_7seg_map[num%10];
}

void display_led(uint8_t data_byte){
	display_buffer[2] = data_byte;
}


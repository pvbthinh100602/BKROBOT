/*
 * sensor.h
 *
 *  Created on: Apr 17, 2024
 *      Author: phamv
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "dma.h"
#include "adc.h"

#define LINE_END	0
#define LINE_CROSS	1
#define LINE_LEFT1	2
#define LINE_RIGHT1	3
#define LINE_CENTER	4
#define LINE_LEFT2	5
#define LINE_RIGHT2	6
#define LINE_LEFT3	7
#define LINE_RIGHT3	8
#define LINE_ERROR	9

void SensorScan();
void SensorCalib();

uint8_t SensorGetLine();

#endif /* INC_SENSOR_H_ */

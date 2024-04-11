/*
 * gamepad.c
 *
 *  Created on: Apr 10, 2024
 *      Author: phamv
 */

#include "gamepad.h"
#include "math.h"
#include "move.h"
#include "servo.h"

#define _GAMEPAD_RECEIVER_ADDR 0x55<<1

#define _REG_SET_LED_COLOR 0x01
#define	_REG_SET_LED_PLAYER 0x02
#define _REG_SET_RUMBLE 0x03

#define _DPAD_UP 0
#define _DPAD_DOWN 1
#define _DPAD_RIGHT 2
#define _DPAD_LEFT 3

#define _BUTTON_A 0
#define _BUTTON_B 1
#define _BUTTON_X 2
#define _BUTTON_Y 3
#define _BUTTON_SHOULDER_L 4
#define _BUTTON_SHOULDER_R 5
#define _BUTTON_TRIGGER_L 6
#define _BUTTON_TRIGGER_R 7
#define _BUTTON_THUMB_L 8
#define _BUTTON_THUMB_R 9

#define _MISC_BUTTON_SYSTEM 0  // AKA: PS, Xbox, etc.
#define _MISC_BUTTON_M1 1      // AKA: Select, Share, -
#define _MISC_BUTTON_M2 2      // AKA: Start, Options, +

int is_receiver_connect = 0;
int is_gamepad_connect = 0;
uint8_t result[30];

int8_t dpad = 0;

// Joystick
int32_t aLX = 0;
int32_t aLY = 0;

int32_t aRX = 0;
int32_t aRY = 0;

// Buttons
int32_t al2 = 0;
int32_t ar2 = 0;

int16_t buttons = 0;
int16_t misc_buttons = 0;

uint8_t dpad_left = 0;
uint8_t dpad_up = 0;
uint8_t dpad_down = 0;
uint8_t dpad_right = 0;
uint8_t a = 0;
uint8_t b = 0;
uint8_t x = 0;
uint8_t y = 0;
uint8_t l1 = 0;
uint8_t r1 = 0;
uint8_t l2 = 0;
uint8_t r2 = 0;
uint8_t m1 = 0;
uint8_t m2 = 0;
uint8_t thumbl = 0;
uint8_t thumbr = 0;

int gamepad_init(){
	if(HAL_I2C_IsDeviceReady(&hi2c2, _GAMEPAD_RECEIVER_ADDR, 10, 100) != HAL_OK) return 0;
	is_receiver_connect = 1;
	HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, 1);
	return 1;
}

int16_t _read_16(uint8_t b1,uint8_t b2){
    // Read and return a 16-bit signed little endian value from 2 bytes
    int16_t raw = (b1 << 8) | b2;
    if (raw & (1 << 15)){
        return (raw - (1 << 16));
    	// sign bit is set
    } else{
    	return raw;
    }
}

int32_t _read_32(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4){
    // Read and return a 32-bit signed little endian value from 2 bytes
    int32_t raw = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
    if (raw & (1 << 31)){
        return (raw - (1 << 32));
    	// sign bit is set
    } else{
    	return raw;
    }
}

void _convert_data(){
	dpad_left = (dpad >> _DPAD_LEFT) & 1;
	dpad_up = (dpad >> _DPAD_UP) & 1;
	dpad_down = (dpad >> _DPAD_DOWN) & 1;
	dpad_right = (dpad >> _DPAD_RIGHT) & 1;
	thumbl = (buttons >> _BUTTON_THUMB_L) & 1;
	thumbr = (buttons >> _BUTTON_THUMB_R) & 1;
	a = (buttons >> _BUTTON_A) & 1;
	b = (buttons >> _BUTTON_B) & 1;
	x = (buttons >> _BUTTON_X) & 1;
	y = (buttons >> _BUTTON_Y) & 1;
	l1 = (buttons >> _BUTTON_SHOULDER_L) & 1;
	r1 = (buttons >> _BUTTON_SHOULDER_R) & 1;
	l2 = (buttons >> _BUTTON_TRIGGER_L) & 1;
	r2 = (buttons >> _BUTTON_TRIGGER_R) & 1;
	m1 = (buttons >> _MISC_BUTTON_M1) & 1;
	m2 = (buttons >> _MISC_BUTTON_M2) & 1;
}

void gamepad_update(){
	if(is_receiver_connect == 0) return;
	HAL_I2C_Master_Receive(&hi2c2, _GAMEPAD_RECEIVER_ADDR, result, 30, 50);
	if(result[0] == 1) is_gamepad_connect = 1;
	else is_gamepad_connect = 0;

	if(is_gamepad_connect == 1){
		dpad = result[1];
		aLX = _read_32(result[2], result[3], result[4], result[5]);
		aLY = _read_32(result[6], result[7], result[8], result[9]);
		aRX = _read_32(result[10], result[11], result[12], result[13]);
		aRY = _read_32(result[14], result[15], result[16], result[17]);
		al2 = _read_32(result[18], result[19], result[20], result[21]);
		ar2 = _read_32(result[22], result[23], result[24], result[25]);
		buttons = _read_16(result[26], result[27]);
		misc_buttons = _read_16(result[28], result[29]);
	}
	_convert_data();
}

int gamepad_calculate_leff_joystick(){
	if(is_gamepad_connect == 0) return -1;
    int dir = -1;

    int distance = (int)(sqrt(aLX*aLX + aLY*aLY));

    if (distance < 15){
        distance = 0;
        dir = -1;
        return dir;
    }else if (distance > 100){
    	distance = 100;
    }

    int angle = (int)(atan2(aLY, aLX) * 180 / 3.14);

    if (angle < 0) angle += 360;

    if ((0 <= angle && angle < 10) || angle >= 350)
        dir = ROBOT_DIR_R;
    else if (15 <= angle && angle < 75)
        dir = ROBOT_DIR_RF;
    else if (80 <= angle && angle < 110)
        dir = ROBOT_DIR_FW;
    else if (115 <= angle && angle < 165)
        dir = ROBOT_DIR_LF;
    else if (170 <= angle && angle < 190)
        dir = ROBOT_DIR_L;
    else if (195 <= angle && angle < 255)
        dir = ROBOT_DIR_LB;
    else if (260 <= angle && angle < 280)
        dir = ROBOT_DIR_BW;
    else if (285 <= angle && angle < 345)
        dir = ROBOT_DIR_RB;
    return dir;
}

int sm_pos = 1;
void gamepad_run_tele(){
	int my_dir = -1;
	my_dir = gamepad_calculate_leff_joystick();
	if(b) {
		servo_set_angle(SERVO1, 0);
	}
	if(x){
		servo_set_angle(SERVO1, 45);
	}
	if(a){
		if(sm_pos == 1){
			sm_pos = 0;
			moveSM(-4);
		}
	}
	if(y){
		if(sm_pos == 0){
			sm_pos = 1;
			moveSM(4);
		}
	}
	if(dpad_up){
		my_dir = ROBOT_DIR_FW;
	}
	if(dpad_down){
		my_dir = ROBOT_DIR_BW;
	}
	if(dpad_left){
		my_dir = ROBOT_DIR_L;
	}
	if(dpad_right){
		my_dir = ROBOT_DIR_R;
	}
	runDir(my_dir);
}

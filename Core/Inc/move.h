/*
 * move.h
 *
 *  Created on: Apr 10, 2024
 *      Author: HaHuyen
 */

#ifndef INC_MOVE_H_
#define INC_MOVE_H_

#include "stdint.h"

#define ROBOT_DIR_R		1
#define ROBOT_DIR_RF	2
#define ROBOT_DIR_FW	3
#define ROBOT_DIR_LF	4
#define ROBOT_DIR_LB	5
#define ROBOT_DIR_RB	6
#define ROBOT_DIR_SL	7
#define ROBOT_DIR_SR	8
#define ROBOT_DIR_BW	9
#define ROBOT_DIR_L		10

void dc1Move(int duty_cycle);
void dc2Move(int duty_cycle);
void dc3Move(int duty_cycle);
void dc4Move(int duty_cycle);

//                   forward
//           frontLeft   |  frontRight          ↺: rotateLeft
//         left		  ---+----     right		↻: rotateRight
//           backLeft    |  backRight
//                  backwards
//

void stop();
void forward();
void backwards();
void frontLeft();
void frontRight();
void backLeft();
void backRight();
void right();
void left();
void rotateLeft();
void rotateRight();
void testDc();
void runDir(int dir);

#endif /* INC_MOVE_H_ */

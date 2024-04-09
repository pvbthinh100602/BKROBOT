/*
 * move.h
 *
 *  Created on: Apr 10, 2024
 *      Author: HaHuyen
 */

#ifndef INC_MOVE_H_
#define INC_MOVE_H_
void dc1Move(uint8_t duty_cycle);
void dc2Move(uint8_t duty_cycle);
void dc3Move(uint8_t duty_cycle);
void dc4Move(uint8_t duty_cycle);

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


#endif /* INC_MOVE_H_ */

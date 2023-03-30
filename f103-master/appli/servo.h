/*
 * SERVO.h
 *
 *  Created on: 28 mars 2019
 *      Author: Clemence
 */


#ifndef SERVO_H_
#define SERVO_H_

#include "macro_types.h"
#include "stm32f1xx.h"

void SERVO_init(void);
void SERVO_set_position(uint16_t position);

#endif /* SERVO_H_ */

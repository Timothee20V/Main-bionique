/*
 * SERVO.h
 *
 *  Created on: 28 mars 2019
 *      Author: Nirgal
 */


#ifndef SERVO_H_
#define SERVO_H_

#include "macro_types.h"
#include "stm32f1xx.h"

void SERVO_init(void);
void SERVO_set_position(uint16_t position);
void SERVO_process_test(void);
uint16_t SERVO_get_position(void);

#endif /* SERVO_H_ */

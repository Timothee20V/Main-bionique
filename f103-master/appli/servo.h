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
#include "stm32f1_timer.h"

typedef struct {
    uint16_t current_position;
    uint32_t channel;
    timer_id_e timer;
} Servo;

typedef struct {
    uint32_t value;
    uint16_t max;
    uint16_t min;
    uint16_t position;
} Capteur;


void SERVO_init(void);
void SERVO_init2(Servo servo);
void SERVO_set_position(int16_t position, Servo servo);
void SERVO_process_test(void);
uint16_t SERVO_get_position(Servo servo);
uint16_t capteurDelta(Capteur capt);
void test(void);

#endif /* SERVO_H_ */

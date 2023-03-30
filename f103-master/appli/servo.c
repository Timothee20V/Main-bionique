/*
 * secretary.c
 *
 *  Created on: 28 mars 2019
 *      Author: Nirgal
 */
#include "servo.h"
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#define PERIOD_TIMER 10 //ms


void SERVO_init(void){
	//initialisation et lancement du timer1 à une periode de 10 ms
	TIMER_run_us(TIMER1_ID, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);
	//rapport cyclique regle pour une position servo de 50
	SERVO_set_position(50);

}


void SERVO_set_position(uint16_t position){


	TIMER_set_duty(TIMER1_ID,TIM_CHANNEL_1, position); //définit la position du servo

}




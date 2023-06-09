/*
 * servo.c
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


void SERVO_init2(Servo servo){
	//initialisation et lancement du timer1 � une periode de 10 ms
	TIMER_run_us(servo.timer, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
	TIMER_enable_PWM(servo.timer, servo.channel, 150, FALSE, FALSE);
	//rapport cyclique regle pour une position servo de 50
	SERVO_set_position(150, servo);

}



void SERVO_set_position(int16_t position, Servo servo){

	if(position > 0){
		if(position > 100){
			position = 100; //ecretage si l'utilisateur demande plus de 100
		}
		servo.current_position =position;

		TIMER_set_duty(servo.timer,servo.channel, position + 100); //définit la position du servo
	}
	else if(position < 0){
		if(position < -100){
			position = -100; //ecretage si l'utilisateur demande moins de -100
		}
		servo.current_position = position;

		TIMER_set_duty(servo.timer,servo.channel, position + 200); //définit la position du servo
	}
	else{
		TIMER_set_duty(servo.timer,servo.channel, position + 100);
	}
}


uint16_t SERVO_get_position(Servo servo){
	return servo.current_position;
}

uint16_t capteurDelta(Capteur capt){
	return capt.max - capt.min;
}

void SERVO_main(Capteur capt, Servo servo){

	if(capteurDelta(capt) != 0){
		capt.position = ((capt.value - capt.min) * 100) / capteurDelta(capt);

		if (capt.position > 75){
			SERVO_set_position(100, servo);
		}

		else if (capt.position < 25){
			SERVO_set_position(-100, servo);
		}

		else{
			SERVO_set_position(0, servo);
		}
	}
	HAL_Delay(100);
}

void SERVO_main_inverse(int16_t position, Servo servo){

	if (position > 900){
		SERVO_set_position(-100, servo);
	}
	else if (position < 900 && position>550){
		SERVO_set_position(50, servo);
	}

	else if (position<550){
		SERVO_set_position(100, servo);
	}
	HAL_Delay(100);
}

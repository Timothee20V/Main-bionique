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

Servo servo1 = {0, TIM_CHANNEL_1, TIMER1_ID};
Servo servo2 = {0, TIM_CHANNEL_2, TIMER1_ID};
Servo servo3 = {0, TIM_CHANNEL_3, TIMER1_ID};
Servo servo4 = {0, TIM_CHANNEL_4, TIMER1_ID};
Servo servo5 = {0, TIM_CHANNEL_1, TIMER4_ID};

void SERVO_init2(Servo servo){
	//initialisation et lancement du timer1 à une periode de 10 ms
	TIMER_run_us(servo.timer, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
	TIMER_enable_PWM(servo.timer, servo.channel, 150, FALSE, FALSE);
	//rapport cyclique regle pour une position servo de 50
	SERVO_set_position(50, servo);

}

void SERVO_init(){
	SERVO_init2(servo1);
	SERVO_init2(servo2);
	SERVO_init2(servo3);
	SERVO_init2(servo4);
	SERVO_init2(servo5);
}

void SERVO_set_position(int16_t position, Servo servo){
	if(position > 0){
		if(position > 100){
			position = 100; //ecretage si l'utilisateur demande plus de 100
		}
		servo.current_position = position;

		TIMER_set_duty(servo.timer,servo.channel, position + 100); //définit la position du servo
	}
	else if(position < 0){
		if(position < -100){
			position = -100; //ecretage si l'utilisateur demande moins de -100
		}
		servo.current_position = position;

		TIMER_set_duty(servo.timer,servo.channel, position + 200); //définit la position du servo
	}
}

uint16_t SERVO_get_position(Servo servo){
	return servo.current_position;
}

void SERVO_main(int16_t position){
	HAL_Delay(100);
	SERVO_set_position(position, servo1);
	SERVO_set_position((-position), servo2);
	SERVO_set_position((-position), servo3);
	SERVO_set_position(position, servo4);
	SERVO_set_position(position, servo5);
}


void test(void){
	SERVO_set_position(50, servo1);
	HAL_Delay(1000);
	SERVO_set_position(50, servo2);
	HAL_Delay(1000);
	SERVO_set_position(50, servo3);
	HAL_Delay(1000);
	SERVO_set_position(50, servo4);
	HAL_Delay(1000);
	SERVO_set_position(50, servo5);
}

//void SERVO_process_test(void){
//	static uint16_t position = 50;
//	static bool_e previous_button = FALSE;
//	bool_e current_button;
//	//lecture du bouton bleu
//	current_button = !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
//	if(current_button && !previous_button) //si appui bouton
//	{
//	position = (position > 99)?0:(position+5); //de 0 à 100, par pas de 5
//	SERVO_set_position(position);
//	}
//	previous_button = current_button; //sauvegarde pour le prochain passage
//	HAL_Delay(10); //anti-rebond de fortune en cadencant la lecture du bouton
//}



/*
 *******************************************************************************
 * @file    servo.c
 * @brief   Fonctions du servo-moteur.
 * @author  Clémence MAIGNAN - Timothée VIARD
 * @details Ce fichier contient les fonctions pour initialiser et contrôler un servo-moteur.
 * @date    15 mars 2023
 *******************************************************************************
 */
#include "servo.h"
#include "config.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"

#define PERIOD_TIMER 10 //ms

/**
  * @brief  Initialise un servo-moteur.
  * @param  servo : Structure représentant le servo-moteur à initialiser.
  * @retval None
  */
void SERVO_init(Servo servo){
	//initialisation et lancement du timer1 � une periode de 10 ms
	TIMER_run_us(servo.timer, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
	TIMER_enable_PWM(servo.timer, servo.channel, 150, FALSE, FALSE);
	//rapport cyclique regle pour une position servo de 50
	SERVO_set_position(100, servo);
}

/**
  * @brief  Définit la position du servo-moteur.
  * @param  position : Position du servo-moteur à définir.
  * @param  servo : Structure représentant le servo-moteur.
  * @retval None
  */
void SERVO_set_position(int16_t position, Servo servo){
	servo.current_position = position;
	TIMER_set_duty(servo.timer,servo.channel, servo.current_position);
}

/**
  * @brief  Obtient la position actuelle du servo-moteur.
  * @param  servo : Structure représentant le servo-moteur.
  * @retval Position actuelle du servo-moteur.
  */
uint16_t SERVO_get_position(Servo servo){
	return servo.current_position;
}

/**
  * @brief  Calcule la différence entre la valeur maximale et minimale d'un capteur.
  * @param  capt : Structure représentant le capteur.
  * @retval Différence entre la valeur maximale et minimale du capteur.
  */
uint16_t capteurDelta(Capteur capt){
	return capt.max - capt.min;
}

/**
  * @brief  Convertit la position du capteur en rapport cyclique du servo-moteur.
  * @param  servo : Structure représentant le servo-moteur.
  * @param  capt : Structure représentant le capteur.
  * @retval Rapport cyclique correspondant à la position du capteur.
  */
uint16_t SERVO_position_to_duty(Servo servo, Capteur capt){
	if(servo.sens){
		return servo.min - (servo.min - servo.max) * (100 - capt.position) / 100;
	}
	else{
		return servo.min + (servo.max - servo.min) * (100 - capt.position) / 100;
	}

}

/**
  * @brief  Fonction principale de contrôle du servo-moteur en fonction de la position du capteur.
  * @param  capt : Structure représentant le capteur.
  * @param  servo : Structure représentant le servo-moteur.
  * @retval None
  */
void SERVO_main(Capteur capt, Servo servo){
	if(capteurDelta(capt) != 0){
		capt.position = ((capt.value - capt.min) * 100) / capteurDelta(capt);
		uint16_t duty = SERVO_position_to_duty(servo, capt);

		SERVO_set_position(duty, servo);
	}
	HAL_Delay(100);
}

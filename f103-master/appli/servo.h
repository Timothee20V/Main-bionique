/*
 * SERVO.h
 *
 *  Created on: 28 mars 2019
 *      Author: Nirgal
 */


#ifndef SERVO_H_
#define SERVO_H_

#include "macro_types.h"
#include "stm32f103xb.h"
#include "stm32f1_timer.h"
#include "stdbool.h"


/**
 * \struct Servo
 * Structure représentant un servo-moteur.
 */
typedef struct {
    uint16_t current_position; /**< Position actuelle du servo-moteur */
    uint32_t channel; /**< Canal du timer utilisé pour le servo-moteur */
    timer_id_e timer; /**< Identifiant du timer utilisé pour le servo-moteur */
    bool sens; /**< Sens de rotation du servo-moteur */
    uint16_t max; /**< Position maximale du servo-moteur */
    uint16_t min; /**< Position minimale du servo-moteur */
} Servo;

/**
 * \struct Capteur
 * Structure représentant un capteur.
 */
typedef struct {
    uint32_t value; /**< Valeur du capteur */
    uint16_t max; /**< Valeur maximale du capteur */
    uint16_t min; /**< Valeur minimale du capteur */
    uint16_t position; /**< Position du capteur */
} Capteur;

/**
 * \brief Initialise un servo-moteur.
 * \param servo Le servo-moteur à initialiser.
 */
void SERVO_init(Servo servo);

/**
 * \brief Définit la position d'un servo-moteur.
 * \param position La position à définir.
 * \param servo Le servo-moteur concerné.
 */
void SERVO_set_position(int16_t position, Servo servo);

/**
 * \brief Fonction de test du module SERVO.
 */
void SERVO_process_test(void);

/**
 * \brief Obtient la position actuelle d'un servo-moteur.
 * \param servo Le servo-moteur concerné.
 * \return La position actuelle du servo-moteur.
 */
uint16_t SERVO_get_position(Servo servo);

/**
 * \brief Calcule la différence entre deux positions d'un capteur.
 * \param capt Le capteur contenant les positions.
 * \return La différence entre les positions du capteur.
 */
uint16_t capteurDelta(Capteur capt);

/**
 * \brief Fonction de test.
 */
void test(void);

/**
 * \brief Gère le servo-moteur en fonction d'un devoir (duty) donné.
 * \param duty Le devoir (duty) à appliquer.
 * \param servo Le servo-moteur à gérer.
 */
void SERVO_manager(float duty, ServoSpec * servo);

/**
 * \brief Convertit une position de servo-moteur en devoir (duty) correspondant en fonction d'un capteur.
 * \param servo Le servo-moteur concerné.
 * \param capt Le capteur utilisé pour la conversion.
 * \return Le devoir (duty) correspondant à la position du servo-moteur.
 */

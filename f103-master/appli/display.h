#ifndef DISPLAY_H
#define DISPLAY_H

#include "tft_ili9341/stm32f1_ili9341.h"
#include "stdbool.h"
#include "stm32f1xx_hal.h"

/**
 * \brief Initialise l'écran TFT.
 */
void TFT_Init(void);

/**
 * \brief Efface l'écran TFT.
 */
void TFT_Clear(void);

/**
 * \brief Affiche une chaîne de caractères sur l'écran TFT.
 * \param str La chaîne de caractères à afficher.
 * \param lineBreak Indique si un saut de ligne doit être effectué après l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print(char *str, bool lineBreak, uint16_t color);

/**
 * \brief Effectue un saut de ligne sur l'écran TFT.
 */
void TFT_LineBreak(void);

/**
 * \brief Efface la ligne courante sur l'écran TFT.
 */
void TFT_ClearLine(void);

/**
 * \brief Définit le nombre de lignes disponibles sur l'écran TFT.
 * \param nbLine Le nombre de lignes à définir.
 */
void TFT_DefineLine(uint16_t nbLine);

/**
 * \brief Affiche une chaîne de caractères alignée à droite sur l'écran TFT.
 * \param str La chaîne de caractères à afficher.
 * \param lineBreak Indique si un saut de ligne doit être effectué après l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print_RigthAligned(char *str, bool lineBreak, uint16_t color);

/**
 * \brief Affiche une chaîne de caractères centrée sur l'écran TFT.
 * \param str La chaîne de caractères à afficher.
 * \param lineBreak Indique si un saut de ligne doit être effectué après l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print_CenterAligned(char *str, bool lineBreak, uint16_t color);

#endif /* DISPLAY_H */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "tft_ili9341/stm32f1_ili9341.h"
#include "stdbool.h"
#include "stm32f1xx_hal.h"

/**
 * \brief Initialise l'�cran TFT.
 */
void TFT_Init(void);

/**
 * \brief Efface l'�cran TFT.
 */
void TFT_Clear(void);

/**
 * \brief Affiche une cha�ne de caract�res sur l'�cran TFT.
 * \param str La cha�ne de caract�res � afficher.
 * \param lineBreak Indique si un saut de ligne doit �tre effectu� apr�s l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print(char *str, bool lineBreak, uint16_t color);

/**
 * \brief Effectue un saut de ligne sur l'�cran TFT.
 */
void TFT_LineBreak(void);

/**
 * \brief Efface la ligne courante sur l'�cran TFT.
 */
void TFT_ClearLine(void);

/**
 * \brief D�finit le nombre de lignes disponibles sur l'�cran TFT.
 * \param nbLine Le nombre de lignes � d�finir.
 */
void TFT_DefineLine(uint16_t nbLine);

/**
 * \brief Affiche une cha�ne de caract�res align�e � droite sur l'�cran TFT.
 * \param str La cha�ne de caract�res � afficher.
 * \param lineBreak Indique si un saut de ligne doit �tre effectu� apr�s l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print_RigthAligned(char *str, bool lineBreak, uint16_t color);

/**
 * \brief Affiche une cha�ne de caract�res centr�e sur l'�cran TFT.
 * \param str La cha�ne de caract�res � afficher.
 * \param lineBreak Indique si un saut de ligne doit �tre effectu� apr�s l'affichage.
 * \param color La couleur du texte.
 */
void TFT_Print_CenterAligned(char *str, bool lineBreak, uint16_t color);

#endif /* DISPLAY_H */

/*
 *******************************************************************************
 * @file    display.c
 * @brief   Fonctions du display
 * @author  Cl�mence MAIGNAN - Timoth�e VIARD
 * @details Ce fichier contient les fonctions pour afficher des informations sur l'�cran TFT.
 * @date    17 mai 2023
 *******************************************************************************
 */
#include "display.h"

static int16_t line = 0;
static int16_t displayWidth = 240;

/**
  * @brief  Initialise l'�cran TFT.
  * @param  None
  * @retval None
  */
void TFT_Init(void)
{
	//Initialise l'�cran
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_WHITE);
}

/**
  * @brief  Efface l'�cran TFT.
  * @param  None
  * @retval None
  */
void TFT_Clear(void)
{
	//Efface l'�cran
	ILI9341_Fill(ILI9341_COLOR_WHITE);
}

/**
  * @brief  Affiche du texte sur l'�cran TFT.
  * @param  str : Cha�ne de caract�res � afficher.
  * @param  lineBreak : Indique s'il faut passer � la ligne apr�s l'affichage.
  * @param  color : Couleur du texte.
  * @retval None
  */
void TFT_Print(char *str, bool lineBreak, uint16_t color) {

    //Retourne � la ligne si lineBreak est true
	if (lineBreak) {
        TFT_LineBreak();
    }

    //Affiche le texte
    ILI9341_Puts(20, line, str, &Font_11x18, color, ILI9341_COLOR_WHITE);
}

/**
  * @brief  Passe � la ligne suivante sur l'�cran TFT.
  * @param  None
  * @retval None
  */
void TFT_LineBreak()
{
	line = line + 20;
	TFT_ClearLine();
}

/**
  * @brief  Efface la ligne actuelle sur l'�cran TFT.
  * @param  None
  * @retval None
  */
void TFT_ClearLine()
{
    ILI9341_DrawFilledRectangle(0, line, displayWidth, line + 20, ILI9341_COLOR_WHITE);
}

/**
  * @brief  D�finit la ligne � afficher sur l'�cran TFT.
  * @param  nbLine : Num�ro de la ligne � d�finir.
  * @retval None
  */
void TFT_DefineLine(uint16_t nbLine)
{
	line = 20 * nbLine;
}


/**
  * @brief  Affiche du texte align� � droite sur l'�cran TFT.
  * @param  str : Cha�ne de caract�res � afficher.
  * @param  lineBreak : Indique s'il faut passer � la ligne apr�s l'affichage.
  * @param  color : Couleur du texte.
  * @retval None
  */
void TFT_Print_RightAligned(char *str, bool lineBreak, uint16_t color) {
    uint16_t strWidth, strHeight;
    ILI9341_GetStringSize(str, &Font_11x18, &strWidth, &strHeight);
    int displayWidth = 240;
    int xPos = displayWidth - strWidth - 20;

    if (lineBreak) {
        line += 20;
        xPos = displayWidth - strWidth - 20; // R�initialise la position pour la nouvelle ligne
    }

    ILI9341_DrawFilledRectangle(160, line, displayWidth, line + 20, ILI9341_COLOR_WHITE);
    // Affiche le texte tout � droite
    ILI9341_Puts(xPos, line, str, &Font_11x18, color, ILI9341_COLOR_WHITE);
}


/**
  * @brief  Affiche du texte align� � droite sur l'�cran TFT.
  * @param  str : Cha�ne de caract�res � afficher.
  * @param  lineBreak : Indique s'il faut passer � la ligne apr�s l'affichage.
  * @param  color : Couleur du texte.
  * @retval None
  */
void TFT_Print_CenterAligned(char *str, bool lineBreak, uint16_t color) {
    // Retourne � la ligne si lineBreak est true
    if (lineBreak) {
        TFT_LineBreak();
    }

    uint16_t strWidth, strHeight;
    ILI9341_GetStringSize(str, &Font_11x18, &strWidth, &strHeight);
    int displayWidth = 240;

    // Centre le texte en calculant la position xPos
    int xPos = (displayWidth - strWidth) / 2;

    // Affiche le texte
    ILI9341_Puts(xPos, line, str, &Font_11x18, color, ILI9341_COLOR_WHITE);
}

#include "display.h"

static int16_t line = 0;
static int16_t displayWidth = 240;

void TFT_Init(void)
{
	//Initialise l'écran
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_WHITE);
}

void TFT_Clear(void)
{
	//Efface l'écran
	ILI9341_Fill(ILI9341_COLOR_WHITE);
}

void TFT_Print(char *str, bool lineBreak, uint16_t color) {

    //Retourne à la ligne si lineBreak est true
	if (lineBreak) {
        TFT_LineBreak();
    }

    //Affiche le texte
    ILI9341_Puts(20, line, str, &Font_11x18, color, ILI9341_COLOR_WHITE);
}

void TFT_LineBreak()
{
	line = line + 20;
	TFT_ClearLine();
}

void TFT_ClearLine()
{
    ILI9341_DrawFilledRectangle(0, line, displayWidth, line + 20, ILI9341_COLOR_WHITE);
}

void TFT_DefineLine(uint16_t nbLine)
{
	line = 20 * nbLine;
}

void TFT_Print_RightAligned(char *str, bool lineBreak, uint16_t color) {
    uint16_t strWidth, strHeight;
    ILI9341_GetStringSize(str, &Font_11x18, &strWidth, &strHeight);
    int displayWidth = 240;
    int xPos = displayWidth - strWidth - 20;

    if (lineBreak) {
        line += 20;
        xPos = displayWidth - strWidth - 20; // Réinitialise la position pour la nouvelle ligne
    }

    ILI9341_DrawFilledRectangle(160, line, displayWidth, line + 20, ILI9341_COLOR_WHITE);
    // Affiche le texte tout à droite
    ILI9341_Puts(xPos, line, str, &Font_11x18, color, ILI9341_COLOR_WHITE);
}

void TFT_Print_CenterAligned(char *str, bool lineBreak, uint16_t color) {
    // Retourne à la ligne si lineBreak est true
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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "tft_ili9341/stm32f1_ili9341.h"
#include "stdbool.h"
#include "stm32f1xx_hal.h"

void TFT_Init(void);
void TFT_Clear(void);
void TFT_Print(char *str, bool lineBreak, uint16_t color);
void TFT_LineBreak(void);
void TFT_ClearLine(void);
void TFT_DefineLine(uint16_t nbLine);
void TFT_Print_RigthAligned(char *str, bool lineBreak, uint16_t color);
void TFT_Print_CenterAligned(char *str, bool lineBreak, uint16_t color);

#endif /* DISPLAY_H */

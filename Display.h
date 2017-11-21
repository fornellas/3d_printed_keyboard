#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdint.h>

#define NO_LED_REPORT 0xFF

void Display_Init(void);
void Display_Update(void);
void Display_Set_LEDReport(uint8_t);
void Display_Set_Keypad(uint8_t);
void Display_Set_Fn(uint8_t);

#endif

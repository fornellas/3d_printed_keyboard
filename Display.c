#include "Display.h"
#include "Keymap.h"
#include <u8g.h>
#include <LUFA/Drivers/USB/USB.h>
#include <stdlib.h>
#include <util/delay.h>
#include "Bitmaps.h"
#include <avr/io.h>

u8g_t u8g;
uint8_t Display_LEDReport;
uint8_t Display_keypad_state;
uint8_t Display_Fn_state;

#define TIMER_COUNTER_CONTROL_REGISTER TCCR1B
#define TIMER_COUNTER_PRESCALE_SETTINGS ((1<<CS12) | (1<<CS10))
#define TIMER_COUNTER_PRESCALE 1024
#define TIMER_COUNTER TCNT1
#define LOGO_SECS 0.2

#define TOGGLE_WIDTH  24
#define TOGGLE_HEIGHT  22
#define TOGGLE_SPACING 2

void Display_Init(void)
{
  u8g_InitHWSPI(
      &u8g,
      &u8g_dev_sh1106_128x64_hw_spi,
      PN(1, 0), // CS
      PN(1, 4), // A0
      PN(0, 7) // RESET
  );

  u8g_FirstPage(&u8g);
  do {
    u8g_DrawBitmapP(
      &u8g,
      ((u8g_GetWidth(&u8g) - (BITMAP_LOGO_WIDTH * 8)) / 2),
      (u8g_GetHeight(&u8g) - BITMAP_LOGO_HEIGHT) / 2,
      BITMAP_LOGO_WIDTH, BITMAP_LOGO_HEIGHT,
      bitmap_logo
    );
  } while(u8g_NextPage(&u8g));
  TIMER_COUNTER_CONTROL_REGISTER |= TIMER_COUNTER_PRESCALE_SETTINGS;
  TIMER_COUNTER = 0;

  Display_LEDReport = NO_LED_REPORT;
  Display_keypad_state = 0;
  Display_Fn_state = 0;
}

void Display_Write_Box_CenteredP(
  int8_t x_start, int8_t y_start,
  u8g_uint_t x_end, u8g_uint_t y_end,
  u8g_pgm_uint8_t *strP
) {
  uint8_t lines;
  uint8_t line;

  lines = 1;
  for(uint8_t i=0 ; pgm_read_byte(strP + i) ; i++)
    if(pgm_read_byte(strP + i) == '\n')
      lines++;

  for(line=0 ; line < lines ; line++) {
    uint8_t draw_x;
    uint8_t draw_y;
    int8_t font_height;
    char *str;
    char *newline;
    size_t len;

    len = (strlen_P(strP) + 1) + sizeof(char);
    str = malloc(len);
    if(!str)
      continue;
    memcpy_P(str, strP, len);
    if(newline = strchr(str, '\n'))
      str[newline - str] = '\0';

    draw_x = x_start + x_end / 2 - u8g_GetStrWidth(&u8g, str) / 2;
    u8g_SetFontRefHeightText(&u8g);
    int8_t y = y_end / 2 + u8g_GetFontAscent(&u8g) / 2 + y_start;
    u8g_SetFontRefHeightAll(&u8g);
    font_height = u8g_GetFontLineSpacing(&u8g);
    int8_t line_y_start = - font_height / 2 * (lines-1);
    draw_y = y + line_y_start + font_height * line + 2 * line;

    u8g_DrawStr(&u8g, draw_x, draw_y, str);

    free(str);
    strP = strchr_P(strP, '\n') + 1;
  }
}

void Display_Write_CenteredP(u8g_pgm_uint8_t *strP)
{
  Display_Write_Box_CenteredP(
    0, 0,
    u8g_GetWidth(&u8g), u8g_GetHeight(&u8g),
    strP
  );
}

void Display_Draw_Toggle(
    uint8_t x, uint8_t y,
    uint8_t width, uint8_t height,
    u8g_pgm_uint8_t *strP,
    uint8_t state
)
{
  if(state){
    u8g_DrawFrame(&u8g, x, y, width, height);
    u8g_DrawBox(&u8g, x + 2,  y + 2, width - 4, height - 4);
    u8g_SetColorIndex(&u8g, 0);
  }else{
    u8g_DrawFrame(&u8g, x, y, width, height);
  }
  Display_Write_Box_CenteredP(x, y, width, height, strP);
  u8g_SetColorIndex(&u8g, 1);
}

/**< Internally implemented by the library. This state indicates
  *   that the device is not currently connected to a host.
  */
void Display_USB_Unattached(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB\ndisconnected"));
  } while(u8g_NextPage(&u8g));
}

/**< Internally implemented by the library. This state indicates
  *   that the device is connected to a host, but enumeration has not
  *   yet begun.
  */
void Display_USB_Powered(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB connected,\nwaiting for\nenumeration"));
  } while(u8g_NextPage(&u8g));
}

/**< Internally implemented by the library. This state indicates
  *   that the device's USB bus has been reset by the host and it is
  *   now waiting for the host to begin the enumeration process.
  */
void Display_USB_Default(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB bus reset,\nwaiting for\nenumeration"));
  } while(u8g_NextPage(&u8g));
}

/**< Internally implemented by the library. This state indicates
  *   that the device has been addressed by the USB Host, but is not
  *   yet configured.
  */
void Display_USB_Addressed(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB addressed,\nwaiting for\nconfiguration"));
  } while(u8g_NextPage(&u8g));
}

/**< May be implemented by the user project. This state indicates
  *   that the device has been enumerated by the host and is ready
  *   for USB communications to begin.
  */
void Display_USB_Configured(void)
{
  uint8_t y;
  uint8_t x_icon;
  uint8_t x_text;
  char str[20];

  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB14);

    // LED status
    if(Display_LEDReport != NO_LED_REPORT){
      Display_Draw_Toggle(
          0 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
          U8G_PSTR("1"), Display_LEDReport & HID_KEYBOARD_LED_NUMLOCK
      );
      Display_Draw_Toggle(
          1 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
          U8G_PSTR("A"), Display_LEDReport & HID_KEYBOARD_LED_CAPSLOCK
      );
      Display_Draw_Toggle(
          2 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
          U8G_PSTR("S"), Display_LEDReport & HID_KEYBOARD_LED_SCROLLLOCK
      );
    }
    Display_Draw_Toggle(
        3 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        U8G_PSTR("K"), Display_keypad_state
    );
    Display_Draw_Toggle(
        4 * (TOGGLE_WIDTH + TOGGLE_SPACING) - 8, 0, TOGGLE_WIDTH + 8, TOGGLE_HEIGHT,
        U8G_PSTR("Fn"), Display_Fn_state
    );

    // Layout
    u8g_SetFont(&u8g, u8g_font_helvB10);

    x_icon = 20;
    y = TOGGLE_HEIGHT + 3;
    u8g_DrawBitmapP(&u8g, x_icon, y, BITMAP_KEYBOARD_WIDTH, BITMAP_KEYBOARD_HEIGHT, bitmap_keyboard);
    x_text = x_icon + BITMAP_KEYBOARD_WIDTH * 8;
    Display_Write_Box_CenteredP(
      x_text, y, u8g_GetWidth(&u8g) - x_text - x_icon, BITMAP_KEYBOARD_HEIGHT,
      Keymap_Get_Layer_Keyboard_Name(LayerState_Get_Active_Layout())
    );

    y = y + BITMAP_COMPUTER_HEIGHT + 3;
    u8g_DrawBitmapP(&u8g, x_icon, y, BITMAP_COMPUTER_WIDTH, BITMAP_COMPUTER_HEIGHT, bitmap_computer);
    Display_Write_Box_CenteredP(
      x_text, y, u8g_GetWidth(&u8g) - x_text - x_icon, BITMAP_KEYBOARD_HEIGHT,
      Keymap_Get_Layer_Computer_Name(LayerState_Get_Active_Layout())
    );

    // Key press counter
    u8g_SetFont(&u8g, u8g_font_6x10);
    uint32_t kp = 2341241;
    ultoa(kp, str, 10);
    u8g_DrawStr(&u8g, u8g_GetWidth(&u8g) / 2 - u8g_GetStrWidth(&u8g, str) / 2, u8g_GetHeight(&u8g), str);
  } while(u8g_NextPage(&u8g));
}

/**< May be implemented by the user project. This state indicates
  *   that the USB bus has been suspended by the host, and the device
  *   should power down to a minimal power level until the bus is
  *   resumed.
  */
void Display_USB_Suspended(void)
{
  u8g_pgm_uint8_t * strP;

  if(USB_Device_RemoteWakeupEnabled)
    strP = U8G_PSTR("USB suspended:\npress any key to\nwake up");
  else
    strP = U8G_PSTR("USB\nsuspended");
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(strP);
  } while(u8g_NextPage(&u8g));
}

void Display_USB_Unknown(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB\nunknown\nstate"));
  } while(u8g_NextPage(&u8g));
}

void Display_Update(void)
{
  if(TIMER_COUNTER < 1.0 / ( (1.0 / LOGO_SECS) / F_CPU * TIMER_COUNTER_PRESCALE))
    return;
  else
    TIMER_COUNTER_CONTROL_REGISTER = 0;

  switch(USB_DeviceState){
    case DEVICE_STATE_Unattached:
      Display_USB_Unattached();
      break;
    case DEVICE_STATE_Powered:
      Display_USB_Powered();
      break;
    case DEVICE_STATE_Default:
      Display_USB_Default();
      break;
    case DEVICE_STATE_Addressed:
      Display_USB_Addressed();
      break;
    case DEVICE_STATE_Configured:
      Display_USB_Configured();
      break;
    case DEVICE_STATE_Suspended:
      Display_USB_Suspended();
      break;
    default:
      Display_USB_Unknown();
      break;
  }
}

void Display_Set_LEDReport(uint8_t ReportData)
{
  Display_LEDReport = ReportData;
}

void Display_Set_Keypad(uint8_t new_keypad_state)
{
  Display_keypad_state = new_keypad_state;
}

void Display_Set_Fn(uint8_t new_Fn_state)
{
  Display_Fn_state = new_Fn_state;
}

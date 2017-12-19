#include "Bitmaps.h"
#include "Counter.h"
#include "Display.h"
#include "Keymap.h"
#include "LayerState.h"
#include "ScanKeys.h"
#include <avr/io.h>
#include <LUFA/Drivers/Peripheral/SPI.h>
#include <LUFA/Drivers/USB/USB.h>
#include <stdlib.h>
#include <u8g.h>
#include <util/delay.h>

u8g_t u8g;
uint8_t Display_LEDReport;
uint8_t Display_keypad_state;
uint8_t Display_Fn_state;
uint32_t seconds;
uint8_t mode;
uint8_t last_USB_DeviceState;

uint8_t px;
uint8_t py;
uint8_t step;
uint8_t start;
uint32_t last_seconds;

#define SPLASH_MODE 0
#define STATUS_MODE 1
#define SCREENSAVER_MODE 2

#define SPLASH_TIMEOUT 2
#define SCREENSAVER_TIMEOUT 120

#define TOGGLE_WIDTH  24
#define TOGGLE_HEIGHT  22
#define TOGGLE_SPACING 2

ISR(TIMER1_COMPA_vect)
{
  seconds++;
}

void Display_Setup_Timer(void)
{
  cli();
  OCR1A = 1.0 / ( 1.0  / F_CPU * 1024);
  TCCR1B |= (1 << WGM12) |  (1<<CS12) | (1<<CS10);
  TIMSK1 |= (1 << OCIE1A);
  TCNT1 = 0;
  seconds = 0;
  sei();
}

void Display_Draw_Logo(void)
{
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
}

void Display_Screensaver_Init(void)
{
  px = (float)rand() / RAND_MAX * u8g_GetWidth(&u8g);
  py = (float)rand() / RAND_MAX * u8g_GetHeight(&u8g);
  step = (float)rand() / RAND_MAX * 12 + 4;
  start = (float)rand() / RAND_MAX * step;
  last_seconds = seconds;
}

void Display_Init(void)
{
  SPI_Init(SPI_MODE_MASTER);
  u8g_InitHWSPI(
      &u8g,
      &u8g_dev_sh1106_128x64_hw_spi,
      PN(1, 0), // CS
      PN(1, 4), // A0
      PN(0, 7) // RESET
  );
  u8g_SetContrast(&u8g, 96);

  Display_Draw_Logo();

  Display_Setup_Timer();

  Display_LEDReport = NO_LED_REPORT;
  Display_keypad_state = 0;
  Display_Fn_state = 0;

  last_USB_DeviceState = USB_DeviceState;

  mode = SPLASH_MODE;

  Display_Screensaver_Init();
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

    len = (strlen_P((const char *)strP) + 1) + sizeof(char);
    str = malloc(len);
    if(!str)
      continue;
    memcpy_P(str, strP, len);
    if((newline = strchr(str, '\n')))
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
    strP = (u8g_pgm_uint8_t *)strchr_P((const char *)strP, '\n') + 1;
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

void Display_Draw_LED_Status(void)
{
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
}

void Display_Draw_Layout_Status(void)
{
  uint8_t y;
  uint8_t x_icon;
  uint8_t x_text;

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
}

void Display_Draw_Keypress_Counter(void)
{
  char str[20];

  u8g_SetFont(&u8g, u8g_font_6x10);
  ultoa(Counter_Get(), str, 10);
  u8g_DrawStr(&u8g, u8g_GetWidth(&u8g) / 2 - u8g_GetStrWidth(&u8g, str) / 2, u8g_GetHeight(&u8g), str);
}

/**< May be implemented by the user project. This state indicates
  *   that the device has been enumerated by the host and is ready
  *   for USB communications to begin.
  */
void Display_USB_Configured(void)
{
  if(ScanKeys_Right_Side_Disconnected) {
    u8g_FirstPage(&u8g);
    do {
      u8g_SetFont(&u8g, u8g_font_helvB14);
      Display_Write_CenteredP(U8G_PSTR("Right Side\nDisconnected"));
    } while(u8g_NextPage(&u8g));
  } else {
    u8g_FirstPage(&u8g);
    do {
      u8g_SetFont(&u8g, u8g_font_helvB14);
      Display_Draw_LED_Status();
      Display_Draw_Layout_Status();
      Display_Draw_Keypress_Counter();
    } while(u8g_NextPage(&u8g));
  }
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

void Display_Status(void)
{
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

void Display_Screensaver(void)
{
  if(seconds < SPLASH_TIMEOUT){
    Display_Draw_Logo();
    return;
  }

  if(seconds - last_seconds > 3)
    Display_Screensaver_Init();

  u8g_FirstPage(&u8g);
  do {
    if(step%2) {
      for(uint8_t x=start; x < u8g_GetWidth(&u8g) ; x += step)
        u8g_DrawLine(&u8g, x, 0, px, py);
      for(uint8_t x=start; x < u8g_GetWidth(&u8g) ; x += step)
        u8g_DrawLine(&u8g, x, u8g_GetHeight(&u8g), px, py);
    }else{
      for(uint8_t y=start; y < u8g_GetHeight(&u8g) ; y += step)
        u8g_DrawLine(&u8g, 0, y, px, py);
      for(uint8_t y=start; y < u8g_GetHeight(&u8g) ; y += step)
        u8g_DrawLine(&u8g, u8g_GetWidth(&u8g), y, px, py);
    }

  } while(u8g_NextPage(&u8g));
}

void Display_Update(void)
{
  if(USB_DeviceState != last_USB_DeviceState) {
    Display_Tick();
    last_USB_DeviceState = USB_DeviceState;
  }

  switch(mode){
    case SPLASH_MODE:
      if(seconds > SPLASH_TIMEOUT){
        Display_Tick();
        mode = STATUS_MODE;
      }
      break;
    case STATUS_MODE:
      if(seconds > SCREENSAVER_TIMEOUT) {
        Display_Screensaver_Init();
        mode = SCREENSAVER_MODE;
      } else
        Display_Status();
      break;
    case SCREENSAVER_MODE:
      if(seconds > SCREENSAVER_TIMEOUT)
        Display_Screensaver();
      else
        mode = STATUS_MODE;
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

void Display_Tick(void)
{
  seconds = 0;
}

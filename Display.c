#include "Bitmaps.h"
#include "Counter.h"
#include "Display.h"
#include "Keymap.h"
#include "LayerState.h"
#include "ScanKeys.h"
#include "Timer.h"
#include <LUFA/Drivers/Peripheral/SPI.h>
#include <LUFA/Drivers/USB/USB.h>
#include <stdlib.h>
#include <u8g.h>

// Configuraiton
#define SPLASH_TIMEOUT 2
#define SCREENSAVER_TIMEOUT 180
#define CONTRAST 50

#define TOGGLE_WIDTH  24
#define TOGGLE_HEIGHT  22
#define TOGGLE_SPACING 2

// Modes
#define SPLASH_MODE 0
#define STATUS_MODE 1
#define SCREENSAVER_MODE 2

static u8g_t u8g;
static uint8_t Display_LEDReport;
static uint8_t Display_keypad_state;
static uint8_t Display_Fn_state;
static uint8_t last_USB_DeviceState;
static uint8_t mode;
static uint32_t last_tick;

/*
 * Initialization
 */

void Display_Init(void)
{
  SPI_Init(SPI_MODE_MASTER | SPI_SPEED_FCPU_DIV_2);
  u8g_InitHWSPI(
      &u8g,
      &u8g_dev_sh1106_128x64_hw_spi,
      PN(1, 0), // CS
      PN(1, 4), // A0
      PN(0, 7) // RESET
  );
  u8g_SetContrast(&u8g, CONTRAST);

  Display_LEDReport = NO_LED_REPORT;
  Display_keypad_state = 0;
  Display_Fn_state = 0;

  last_USB_DeviceState = USB_DeviceState;

  mode = SPLASH_MODE;
}

/*
 * Helpers
 */

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

/*
 * Modes
 */

void Display_Splash(void *context)
{
  u8g_DrawBitmapP(
    &u8g,
    ((u8g_GetWidth(&u8g) - (BITMAP_LOGO_WIDTH * 8)) / 2),
    (u8g_GetHeight(&u8g) - BITMAP_LOGO_HEIGHT) / 2,
    BITMAP_LOGO_WIDTH, BITMAP_LOGO_HEIGHT,
    bitmap_logo
  );
}

struct StatusContext
{
    uint8_t USB_DeviceState;
    bool USB_Device_RemoteWakeupEnabled;
    uint8_t Right_Side_Disconnected;
    uint8_t LEDReport;
    u8g_pgm_uint8_t *KeyboardLayerName;
    u8g_pgm_uint8_t *ComputerLayerName;
    uint32_t Counter;
};

void *Display_Status_Context(void)
{
  static struct StatusContext context;

  context.USB_DeviceState = USB_DeviceState;
  context.USB_Device_RemoteWakeupEnabled = USB_Device_RemoteWakeupEnabled;
  context.Right_Side_Disconnected = ScanKeys_Right_Side_Disconnected;
  context.LEDReport = Display_LEDReport;
  context.KeyboardLayerName = Keymap_Get_Layer_Keyboard_Name(LayerState_Get_Active_Layout());
  context.ComputerLayerName = Keymap_Get_Layer_Computer_Name(LayerState_Get_Active_Layout());
  context.Counter = Counter_Get();

  return (void *)&context;
}

void Display_Draw_LED_Status(uint8_t LEDReport)
{
  if(LEDReport != NO_LED_REPORT){
    Display_Draw_Toggle(
        0 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        U8G_PSTR("1"), LEDReport & HID_KEYBOARD_LED_NUMLOCK
    );
    Display_Draw_Toggle(
        1 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        U8G_PSTR("A"), LEDReport & HID_KEYBOARD_LED_CAPSLOCK
    );
    Display_Draw_Toggle(
        2 * (TOGGLE_WIDTH - 2 + TOGGLE_SPACING), 0, TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        U8G_PSTR("S"), LEDReport & HID_KEYBOARD_LED_SCROLLLOCK
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

void Display_Draw_Layout_Status(u8g_pgm_uint8_t *KeyboardLayerName, u8g_pgm_uint8_t *ComputerLayerName)
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
    KeyboardLayerName
  );

  y = y + BITMAP_COMPUTER_HEIGHT + 3;
  u8g_DrawBitmapP(&u8g, x_icon, y, BITMAP_COMPUTER_WIDTH, BITMAP_COMPUTER_HEIGHT, bitmap_computer);
  Display_Write_Box_CenteredP(
    x_text, y, u8g_GetWidth(&u8g) - x_text - x_icon, BITMAP_KEYBOARD_HEIGHT,
    ComputerLayerName
  );
}

void Display_Status(void *in_context)
{
  struct StatusContext *context;

  context = (struct StatusContext *)in_context;

  u8g_SetFont(&u8g, u8g_font_helvB10);

  switch(context->USB_DeviceState){
    /**< Internally implemented by the library. This state indicates
      *   that the device is not currently connected to a host.
      */
    case DEVICE_STATE_Unattached:
      Display_Write_CenteredP(U8G_PSTR("USB\ndisconnected"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device is connected to a host, but enumeration has not
      *   yet begun.
      */
    case DEVICE_STATE_Powered:
      Display_Write_CenteredP(U8G_PSTR("USB connected,\nwaiting for\nenumeration"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device's USB bus has been reset by the host and it is
      *   now waiting for the host to begin the enumeration process.
      */
    case DEVICE_STATE_Default:
      Display_Write_CenteredP(U8G_PSTR("USB bus reset,\nwaiting for\nenumeration"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device has been addressed by the USB Host, but is not
      *   yet configured.
      */
    case DEVICE_STATE_Addressed:
      Display_Write_CenteredP(U8G_PSTR("USB addressed,\nwaiting for\nconfiguration"));
      break;
    /**< May be implemented by the user project. This state indicates
      *   that the device has been enumerated by the host and is ready
      *   for USB communications to begin.
      */
    case DEVICE_STATE_Configured:
      if(context->Right_Side_Disconnected) {
        Display_Write_CenteredP(U8G_PSTR("Right Side\nDisconnected"));
      } else {
        char str[20];

        u8g_SetFont(&u8g, u8g_font_helvB14);
        Display_Draw_LED_Status(context->LEDReport);
        Display_Draw_Layout_Status(context->KeyboardLayerName, context->ComputerLayerName);

        u8g_SetFont(&u8g, u8g_font_6x10);
        ultoa(context->Counter, str, 10);
        u8g_DrawStr(&u8g, u8g_GetWidth(&u8g) / 2 - u8g_GetStrWidth(&u8g, str) / 2, u8g_GetHeight(&u8g), str);
      }
      break;
    /**< May be implemented by the user project. This state indicates
      *   that the USB bus has been suspended by the host, and the device
      *   should power down to a minimal power level until the bus is
      *   resumed.
      */
    case DEVICE_STATE_Suspended:
      if(USB_Device_RemoteWakeupEnabled)
        Display_Write_CenteredP(U8G_PSTR("USB suspended:\npress any key to\nwake up"));
      else
        Display_Write_CenteredP(U8G_PSTR("USB\nsuspended"));
      break;
    default:
      Display_Write_CenteredP(U8G_PSTR("USB\nunknown\nstate"));
      break;
  }
}

struct ScreensaverContext
{
  uint8_t px;
  uint8_t py;
  uint8_t step;
  uint8_t start;
  uint32_t last_display_init;
};

void *Display_Screensaver_Context(void)
{
  static struct ScreensaverContext context;
  static uint32_t last_context = 0;

  if(!last_context || Timer_Secs() - last_context > 3) {
    context.px = (float)rand() / RAND_MAX * u8g_GetWidth(&u8g);
    context.py = (float)rand() / RAND_MAX * u8g_GetHeight(&u8g);
    context.step = (float)rand() / RAND_MAX * 22 + 12;
    context.start = (float)rand() / RAND_MAX * context.step;
    context.last_display_init = Timer_Secs();
    last_context = Timer_Secs();
  }

  return (void *)&context;
}

void Display_Screensaver(void *in_context)
{
  struct ScreensaverContext *context;

  context = (struct ScreensaverContext *)in_context;

  if(context->step%2) {
    for(uint8_t x=context->start; x < u8g_GetWidth(&u8g) ; x += context->step)
      u8g_DrawLine(&u8g, x, 0, context->px, context->py);
    for(uint8_t x=context->start; x < u8g_GetWidth(&u8g) ; x += context->step)
      u8g_DrawLine(&u8g, x, u8g_GetHeight(&u8g), context->px, context->py);
  }else{
    for(uint8_t y=context->start; y < u8g_GetHeight(&u8g) ; y += context->step)
      u8g_DrawLine(&u8g, 0, y, context->px, context->py);
    for(uint8_t y=context->start; y < u8g_GetHeight(&u8g) ; y += context->step)
      u8g_DrawLine(&u8g, u8g_GetWidth(&u8g), y, context->px, context->py);
  }
}

/*
 * Update
 */

void Display_PrepareUpdate(void (**draw)(void *), void **context)
{
  switch(mode){
    case SPLASH_MODE:
      if(Timer_Secs() > SPLASH_TIMEOUT){
        Display_Tick();
        mode = STATUS_MODE;
      } else{
        *draw = &Display_Splash;
        *context = NULL;
        break;
      }
    case STATUS_MODE:
      if(Timer_Secs() - last_tick > SCREENSAVER_TIMEOUT) {
        mode = SCREENSAVER_MODE;
      } else {
        *draw = &Display_Status;
        *context = Display_Status_Context();
        break;
      }
    case SCREENSAVER_MODE:
      if(Timer_Secs() - last_tick > SCREENSAVER_TIMEOUT) {
        u8g_SetContrast(&u8g, 0);
        *draw = &Display_Screensaver;
        *context = Display_Screensaver_Context();
        break;
      } else {
        mode = STATUS_MODE;
        u8g_SetContrast(&u8g, CONTRAST);
      }
  }
}

void Display_Update(void)
{
  static uint8_t updating = 0;
  static void (*draw)(void *) = NULL;
  static void *context = NULL;

  if(USB_DeviceState != last_USB_DeviceState) {
    Display_Tick();
    last_USB_DeviceState = USB_DeviceState;
  }

  if(!updating) {
    Display_PrepareUpdate(&draw, &context);
    u8g_FirstPage(&u8g);
    draw(context);
    updating = 1;
  }else{
    if(u8g_NextPage(&u8g)){
      draw(context);
    }else{
      updating = 0;
    }
  }
}

/*
 * External input
 */

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
  last_tick = Timer_Secs();
}
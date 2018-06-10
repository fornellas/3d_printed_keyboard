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
#include <u8g2.h>
#include <u8x8_avr.h>

// Configuraiton
#define CONTRAST 80

#define SCREENSAVER_TIMEOUT 300
#define SCREENSAVER_CONTRAST (CONTRAST / 2)

// Modes
#define SPLASH_MODE 0
#define STATUS_MODE 1
#define SCREENSAVER_MODE 2

static u8g2_t u8g2;
static uint8_t Display_LEDReport;
static uint8_t mode;
static uint32_t last_tick;
static uint8_t last_USB_DeviceState;

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  // Re-use library for delays
  if(u8x8_avr_delay(u8x8, msg, arg_int, arg_ptr))
    return 1;

  switch(msg){
    case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8
      DDRB |= (1<<0); // CS
      DDRB |= (1<<4); // DC
      DDRA |= (1<<7); // RESET
      break;              // can be used to setup pins
    case U8X8_MSG_GPIO_CS:        // CS (chip select) pin: Output level in arg_int
      if(arg_int)
        PORTB |= (1<<0);
      else
        PORTB &= ~(1<<0);
      break;
    case U8X8_MSG_GPIO_DC:        // DC (data/cmd, A0, register select) pin: Output level in arg_int
      if(arg_int)
        PORTB |= (1<<4);
      else
        PORTB &= ~(1<<4);
      break;
    case U8X8_MSG_GPIO_RESET:     // Reset pin: Output level in arg_int
      if(arg_int)
        PORTA |= (1<<7);
      else
        PORTA &= ~(1<<7);
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);      // default return value
      break;
  }
  return 1;
}

/*
 * Initialization
 */

void Display_Init(void)
{
  // u8g2_Setup_sh1106_128x64_vcomh0_1(
  u8g2_Setup_sh1106_128x64_vcomh0_2(
  // u8g2_Setup_sh1106_128x64_vcomh0_f(
    &u8g2,
    U8G2_R0,
    u8x8_byte_avr_hw_spi,
    u8x8_gpio_and_delay
  );
  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);

  u8g2_SetContrast(&u8g2, CONTRAST);

  Display_LEDReport = NO_LED_REPORT;

  last_USB_DeviceState = USB_DeviceState;

  mode = SPLASH_MODE;
}

/*
 * Helpers
 */

void Display_Write_Box_CenteredP(
  int8_t x_start, int8_t y_start,
  u8g2_uint_t x_end, u8g2_uint_t y_end,
  const char *strP
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

    draw_x = x_start + x_end / 2 - u8g2_GetStrWidth(&u8g2, str) / 2 - 1;
    u8g2_SetFontRefHeightText(&u8g2);
    int8_t y = y_end / 2 + u8g2_GetFontAscent(&u8g2) / 2 + y_start;
    u8g2_SetFontRefHeightAll(&u8g2);
    font_height = u8g2_GetFontAscent(&u8g2) - u8g2_GetFontDescent(&u8g2);
    int8_t line_y_start = - font_height / 2 * (lines-1);
    draw_y = y + line_y_start + font_height * line + 2 * line;

    u8g2_DrawStr(&u8g2, draw_x, draw_y, str);

    free(str);
    strP = (const char *)strchr_P((const char *)strP, '\n') + 1;
  }
}

void Display_Write_CenteredP(const char *strP)
{
  Display_Write_Box_CenteredP(
    0, 0,
    u8g2_GetDisplayWidth(&u8g2), u8g2_GetDisplayHeight(&u8g2),
    strP
  );
}

void Display_Draw_Toggle(
    uint8_t x, uint8_t y,
    uint8_t width,
    uint8_t height,
    const char *strP,
    uint8_t state
)
{
  if(state){
    u8g2_DrawFrame(&u8g2, x, y, width, height);
    u8g2_DrawBox(&u8g2, x + 2,  y + 2, width - 4, height - 4);
    u8g2_SetDrawColor(&u8g2, 0);
  }else{
    u8g2_DrawFrame(&u8g2, x, y, width, height);
  }
  Display_Write_Box_CenteredP(x, y, width, height, strP);
  u8g2_SetDrawColor(&u8g2, 1);
}

#define TOGGLE_WIDTH  24
#define TOGGLE_HEIGHT  18

void Display_Draw_Toggle_Statuses(uint8_t LEDReport, bool Fn_state, bool Keypad_state, bool ShiftedNumber_state)
{
  uint8_t keypad_x;
  uint8_t keypad_y;
  u8g2_SetFont(&u8g2, u8g_font_helvB12);

  keypad_x = u8g2_GetDisplayWidth(&u8g2) - TOGGLE_WIDTH;
  keypad_y = 0;
  Display_Draw_Toggle(
      keypad_x, keypad_y,
      TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
      PSTR("K"), Keypad_state
  );

  if(LEDReport != NO_LED_REPORT){
    Display_Draw_Toggle(
        keypad_x - TOGGLE_WIDTH, 0,
        TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        PSTR("1"), LEDReport & HID_KEYBOARD_LED_NUMLOCK
    );
    Display_Draw_Toggle(
        u8g2_GetDisplayWidth(&u8g2) / 2 - TOGGLE_WIDTH / 2, 0,
        TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        PSTR("S"), LEDReport & HID_KEYBOARD_LED_SCROLLLOCK
    );
    Display_Draw_Toggle(
        keypad_x, u8g2_GetDisplayHeight(&u8g2) / 2 - TOGGLE_HEIGHT / 2,
        TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        PSTR("A"), LEDReport & HID_KEYBOARD_LED_CAPSLOCK
    );
    Display_Draw_Toggle(
        keypad_x, u8g2_GetDisplayHeight(&u8g2) - TOGGLE_HEIGHT,
        TOGGLE_WIDTH - 2, TOGGLE_HEIGHT,
        PSTR("N"), !ShiftedNumber_state
    );
  }
  Display_Draw_Toggle(
      0, u8g2_GetDisplayHeight(&u8g2) - TOGGLE_HEIGHT,
      TOGGLE_WIDTH, TOGGLE_HEIGHT,
      PSTR("Fn"), Fn_state
  );
}

void Display_Draw_Layout_Status(const char *KeyboardLayerName, const char *ComputerLayerName)
{
  uint8_t keyboard_x_start;
  uint8_t keyboard_y_start;
  uint8_t keyboard_x_end;
  uint8_t keyboard_y_end;

  u8g2_SetFont(&u8g2, u8g_font_helvB12);
  keyboard_x_start = 0;
  keyboard_y_start = TOGGLE_HEIGHT / 2;
  keyboard_x_end = u8g2_GetDisplayWidth(&u8g2);
  keyboard_y_end = TOGGLE_HEIGHT + u8g2_GetFontAscent(&u8g2) - u8g2_GetFontDescent(&u8g2);
  Display_Write_Box_CenteredP(
    keyboard_x_start, keyboard_y_start,
    keyboard_x_end, keyboard_y_end,
    KeyboardLayerName
  );

  u8g2_SetFont(&u8g2, u8g_font_helvB10);
  Display_Write_Box_CenteredP(
    keyboard_x_start, keyboard_y_end + 4,
    keyboard_x_end, 8,
    ComputerLayerName
  );
}

/*
 * Modes
 */

void Display_Splash(void *context)
{
  u8g2_DrawXBMP(
    &u8g2,
    ((u8g2_GetDisplayWidth(&u8g2) - (bitmap_logo_width)) / 2),
    (u8g2_GetDisplayHeight(&u8g2) - bitmap_logo_height) / 2,
    bitmap_logo_width, bitmap_logo_height,
    bitmap_logo_bits
  );
}

struct StatusContext
{
    uint8_t USB_DeviceState;
    bool USB_Device_RemoteWakeupEnabled;
    uint8_t Right_Side_Disconnected;
    uint8_t LEDReport;
    char * KeyboardLayerName;
    char * ComputerLayerName;
    uint32_t Counter;
    bool Fn_state;
    bool Keypad_state;
    bool ShiftedNumber_state;
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
  context.Fn_state = LayerState_Get(FN_LAYER);
  context.Keypad_state = LayerState_Get(KEYPAD_LAYER);
  context.ShiftedNumber_state = LayerState_Get(SHIFTED_NUMBER_LAYER);

  return (void *)&context;
}

void Display_Status(void *in_context)
{
  struct StatusContext *context;

  context = (struct StatusContext *)in_context;

  switch(context->USB_DeviceState){
    /**< Internally implemented by the library. This state indicates
      *   that the device is not currently connected to a host.
      */
    case DEVICE_STATE_Unattached:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      Display_Write_CenteredP(PSTR("USB\ndisconnected"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device is connected to a host, but enumeration has not
      *   yet begun.
      */
    case DEVICE_STATE_Powered:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      Display_Write_CenteredP(PSTR("USB connected,\nwaiting for\nenumeration"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device's USB bus has been reset by the host and it is
      *   now waiting for the host to begin the enumeration process.
      */
    case DEVICE_STATE_Default:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      Display_Write_CenteredP(PSTR("USB bus reset,\nwaiting for\nenumeration"));
      break;
    /**< Internally implemented by the library. This state indicates
      *   that the device has been addressed by the USB Host, but is not
      *   yet configured.
      */
    case DEVICE_STATE_Addressed:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      Display_Write_CenteredP(PSTR("USB addressed,\nwaiting for\nconfiguration"));
      break;
    /**< May be implemented by the user project. This state indicates
      *   that the device has been enumerated by the host and is ready
      *   for USB communications to begin.
      */

    case DEVICE_STATE_Configured:
      if(context->Right_Side_Disconnected) {
        u8g2_SetFont(&u8g2, u8g_font_helvB10);
        Display_Write_CenteredP(PSTR("Right Side\nDisconnected"));
      } else {
        char str[20];

        Display_Draw_Toggle_Statuses(context->LEDReport, context->Fn_state, context->Keypad_state, context->ShiftedNumber_state);
        Display_Draw_Layout_Status(context->KeyboardLayerName, context->ComputerLayerName);

        u8g2_SetFont(&u8g2, u8g_font_6x10);
        ultoa(context->Counter, str, 10);
        u8g2_DrawStr(&u8g2, u8g2_GetDisplayWidth(&u8g2) / 2 - u8g2_GetStrWidth(&u8g2, str) / 2, u8g2_GetDisplayHeight(&u8g2), str);
      }
      break;
    /**< May be implemented by the user project. This state indicates
      *   that the USB bus has been suspended by the host, and the device
      *   should power down to a minimal power level until the bus is
      *   resumed.
      */
    case DEVICE_STATE_Suspended:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      if(context->USB_Device_RemoteWakeupEnabled)
        Display_Write_CenteredP(PSTR("USB suspended:\npress any key to\nwake up"));
      else
        Display_Write_CenteredP(PSTR("USB\nsuspended"));
      break;
    default:
      u8g2_SetFont(&u8g2, u8g_font_helvB10);
      Display_Write_CenteredP(PSTR("USB\nunknown\nstate"));
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
    context.px = (float)rand() / RAND_MAX * u8g2_GetDisplayWidth(&u8g2);
    context.py = (float)rand() / RAND_MAX * u8g2_GetDisplayHeight(&u8g2);
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
    for(uint8_t x=context->start; x < u8g2_GetDisplayWidth(&u8g2) ; x += context->step)
      u8g2_DrawLine(&u8g2, x, 0, context->px, context->py);
    for(uint8_t x=context->start; x < u8g2_GetDisplayWidth(&u8g2) ; x += context->step)
      u8g2_DrawLine(&u8g2, x, u8g2_GetDisplayHeight(&u8g2), context->px, context->py);
  }else{
    for(uint8_t y=context->start; y < u8g2_GetDisplayHeight(&u8g2) ; y += context->step)
      u8g2_DrawLine(&u8g2, 0, y, context->px, context->py);
    for(uint8_t y=context->start; y < u8g2_GetDisplayHeight(&u8g2) ; y += context->step)
      u8g2_DrawLine(&u8g2, u8g2_GetDisplayWidth(&u8g2), y, context->px, context->py);
  }
}

/*
 * Update
 */

void Display_PrepareUpdate(void (**draw)(void *), void **context)
{
  uint8_t active_screensaver;

  active_screensaver = Timer_Secs() - last_tick > SCREENSAVER_TIMEOUT;

  if(active_screensaver)
    mode = SCREENSAVER_MODE;

  switch(mode){
    case SPLASH_MODE:
      if(USB_DeviceState == DEVICE_STATE_Configured){
        Display_Tick();
        mode = STATUS_MODE;
      } else{
        *draw = &Display_Splash;
        *context = NULL;
        break;
      }
    case STATUS_MODE:
      *draw = &Display_Status;
      *context = Display_Status_Context();
      break;
    case SCREENSAVER_MODE:
      if(active_screensaver) {
        u8g2_SetContrast(&u8g2, SCREENSAVER_CONTRAST);
        *draw = &Display_Screensaver;
        *context = Display_Screensaver_Context();
        break;
      }else{
        mode = STATUS_MODE;
        u8g2_SetContrast(&u8g2, CONTRAST);
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
    u8g2_FirstPage(&u8g2);
    draw(context);
    updating = 1;
  }else{
    if(u8g2_NextPage(&u8g2)){
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

void Display_Tick(void)
{
  last_tick = Timer_Secs();
}
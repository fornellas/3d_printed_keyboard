#include "Display.h"
#include <u8g.h>
#include <LUFA/Drivers/USB/USB.h>
#include <stdlib.h>

u8g_t u8g;

void Display_Init(void)
{
  u8g_InitHWSPI(
      &u8g,
      &u8g_dev_sh1106_128x64_hw_spi,
      PN(1, 0), // CS
      PN(1, 4), // A0
      PN(0, 7) // RESET
  );
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

    len = strlen_P(strP) + sizeof(char);
    str = malloc(sizeof(char) * len);
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
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB enumerated,\nready to\ncommunicate"));
  } while(u8g_NextPage(&u8g));
}

/**< May be implemented by the user project. This state indicates
  *   that the USB bus has been suspended by the host, and the device
  *   should power down to a minimal power level until the bus is
  *   resumed.
  */
void Display_USB_Suspended(void)
{
  u8g_FirstPage(&u8g);
  do {
    u8g_SetFont(&u8g, u8g_font_helvB10);
    Display_Write_CenteredP(U8G_PSTR("USB\nsuspended"));
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

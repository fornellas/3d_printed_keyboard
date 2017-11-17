#include "Display.h"
#include "ScanKeys.h" // FIXME
#include <u8g.h>
#include <stdarg.h>  // FIXME

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

void ScanKeys_Callback(struct Key key, void *data)
{
  struct Key *send_key;

  if(key.state) {
    send_key = (struct Key *)data;
    send_key->row = key.row;
    send_key->column = key.column;
    send_key->state = key.state;
    send_key->just_pressed = key.just_pressed;
    send_key->just_released = key.just_released;
  }
}

void Display_Write_Centered(int8_t x_offset, int8_t y_offset, ...){
  va_list ap, apl;
  uint8_t lines;
  u8g_pgm_uint8_t *str;
  va_start(ap, y_offset);
  // count lines
  va_copy(apl, ap);
  lines=0;
  while(va_arg(apl, u8g_pgm_uint8_t *)!=NULL)
    lines++;
  va_end(apl);
  // print lines
  int l=0;
  while((str=va_arg(ap, u8g_pgm_uint8_t *))!=NULL){
    int8_t x=u8g_GetWidth(&u8g)/2-u8g_GetStrWidth(&u8g, str)/2+x_offset;
    u8g_SetFontRefHeightText(&u8g);
    int8_t y=u8g_GetHeight(&u8g)/2+u8g_GetFontAscent(&u8g)/2+y_offset;
    u8g_SetFontRefHeightAll(&u8g);
    int8_t font_height=(u8g_GetFontLineSpacing(&u8g));
    int8_t line_y_offset=-font_height/2*(lines-1);
    u8g_DrawStr(&u8g, x, y+line_y_offset+font_height*l+2*l, (const char *)str);
    l++;
  }
  va_end(ap);
}

void Display_Update(void)
{
  char *str_row[11];
  char *str_column[11];
  struct Key key;

  key.state = 0;

  ScanKeys_Read(&ScanKeys_Callback, (void *)&key);

  u8g_FirstPage(&u8g);
  do {
    u8g_DrawFrame(&u8g, 0, 0, 128, 64);
    u8g_SetFont(&u8g, u8g_font_helvB10);
    if(key.state) {
      Display_Write_Centered(
        0, 0,
        utoa(key.row, str_row, 10),
        utoa(key.column, str_column, 10),
        NULL
      );
    }
  } while(u8g_NextPage(&u8g));
}

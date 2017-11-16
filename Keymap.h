#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include <LUFA/Drivers/USB/Class/Common/HIDClassCommon.h>
#include <avr/pgmspace.h>
#include "ScanKeys.h"

#define KEY(name)  (HID_KEYBOARD_SC_ ## name)
#define TODO 0

#define KEY_PLAY	232
#define KEY_MEDIA_PREVIOUS	234
#define KEY_MEDIA_NEXT	235
#define KEY_EJECT	236
#define KEY_BROWSER_BACK	241
#define KEY_BROWSER_FORWARD	242
#define KEY_SLEEP	248
#define KEY_CALC	251

const uint16_t PROGMEM qwerty[SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS]={
  // row 0
  {
    KEY(ESCAPE),
    KEY(F1),
    KEY(F2),
    KEY(F3),
    KEY(F4),
    KEY(F5),
    KEY(DELETE),
    KEY(DELETE),
    KEY(F6),
    KEY(F7),
    KEY(F8),
    KEY(F9),
    KEY(F10),
    KEY(F11),
    KEY(F12),
    TODO // Num lock
  },
  // row 1
  {
    TODO,
    KEY(1_AND_EXCLAMATION),
    KEY(2_AND_AT),
    KEY(3_AND_HASHMARK),
    KEY(4_AND_DOLLAR),
    KEY(5_AND_PERCENTAGE),
    KEY(BACKSPACE),
    KEY(BACKSPACE),
    KEY(6_AND_CARET),
    KEY(7_AND_AMPERSAND),
    KEY(8_AND_ASTERISK),
    KEY(9_AND_OPENING_PARENTHESIS),
    KEY(0_AND_CLOSING_PARENTHESIS),
    TODO,
    TODO,
    KEY_CALC,
  },
  // row 2
  {
    KEY(TAB),
    KEY(Q),
    KEY(W),
    KEY(E),
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
  },
  // row 3
  {
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
  },
  // row 4
  {
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
  },
  // row 5
  {
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
  },
  // row 6
  {
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
    TODO,
  },
};

#endif

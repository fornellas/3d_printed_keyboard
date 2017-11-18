#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include "ScanKeys.h"

#define GET_KEY_FN(k) ((0xFF00 & k) >> 8)

#define KEY_FN_REG 0
#define K(name)  (HID_KEYBOARD_SC_ ## name)
#define GET_KEY_CODE(k) (k & 0xFF)

#define KEY_FN_NONE 1
#define NONE (KEY_FN_NONE << 8)
#define TODO(_) NONE

#define KEY_FN_PASS 2
#define ____ (KEY_FN_PASS << 8)
#define _TBD ____

#define KEY_FN_MACRO 3
#define MACRO(m) ((KEY_FN_MACRO<<8) | m)
#define GET_MACRO(k) (k&0xFF)

#define KEY_FN_LAYOUT 4
#define LAYOUT(l) ((KEY_FN_LAYOUT<<8) | l)
#define GET_LAYOUT(k) (k&0xFF)

enum keymap_macros {
  MACRO_FN,
  MACRO_KEYPAD,
  MACRO_COUNT,
};

extern const void (*keymap_macros[MACRO_COUNT])(struct Key);

enum layer_enabled {
  KEYMAP_START_ENABLED,
  KEYMAP_START_DISABLED,
  KEYMAP_START_LOAD,
};

enum keymap_layers {
  FN_LAYER,
  KEYPAD_LAYER,
  QWERTY_LAYER,
  DVORAK_LAYER,
  COMMON_LAYER,
  LAYER_COUNT,
};

extern const uint8_t keymap_layout_layers[];

#define LAYOUT_LAYERS_COUNT 2

extern const uint8_t layer_initial_state[LAYER_COUNT];

extern const uint16_t keymaps[LAYER_COUNT][SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS];

void Keymap_Init(void);

#endif

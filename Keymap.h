#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include "ScanKeys.h"

#define GET_KEY_FN(k) ((0xFF00 & k) >> 8)

#define KEY_FN_REG 0
#define K(name)  (HID_KEYBOARD_SC_ ## name)
#define GET_KEY_CODE(k) (k & 0xFF)

#define KEY_FN_NONE 1
#define NONE (KEY_FN_NONE << 8)
#define TODO NONE

#define KEY_FN_PASS 2
#define ____ (KEY_FN_PASS << 8)

enum keymap_layers {
  QWERTY_LAYER,
  DVORAK_LAYER,
  COMMON_LAYER,
  LAYER_COUNT,
};

enum layer_enabled {
  KEYMAP_START_ENABLED,
  KEYMAP_START_DISABLED,
  KEYMAP_START_LOAD,
};

extern const uint8_t layer_initial_state[LAYER_COUNT];

extern const uint16_t keymaps[LAYER_COUNT][SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS];

#endif

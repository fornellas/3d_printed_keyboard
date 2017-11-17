#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>
#include "ScanKeys.h"

#define GET_KEY_FN(k) ((0xFF00 & k) >> 8)

#define KEY_FN_REG 0UL
#define K(name)  (HID_KEYBOARD_SC_ ## name)
#define GET_KEY_CODE(k) (k & 0xFF)

#define KEY_FN_NONE 1UL
#define NONE (KEY_FN_NONE << 8)
#define TODO NONE

#define KEY_FN_PASS 2UL
#define ____ (KEY_FN_PASS << 8)

#define KEYMAP( \
  /* Left */ \
  k0x0, k0x1, k0x2, k0x3, k0x4, k0x5, k0x6, \
  k1x0, k1x1, k1x2, k1x3, k1x4, k1x5, k1x6, \
  k2x0, k2x1, k2x2, k2x3, k2x4, k2x5, \
  k3x0, k3x1, k3x2, k3x3, k3x4, k3x5, k3x6, \
        k4x1, k4x2, k4x3, k4x4, k4x5, \
  k5x0, k5x1, k5x2, k5x3,       k5x5, \
  k6x0, k6x1,       k6x3, \
  /* Right */ \
  k0x7, k0x8, k0x9, k0x10, k0x11, k0x12, k0x13, k0x14, k0x15, \
  k1x7, k1x8, k1x9, k1x10, k1x11, k1x12, k1x13, k1x14, k1x15, \
        k2x8, k2x9, k2x10, k2x11, k2x12, k2x13, k2x14, k2x15, \
  k3x7, k3x8, k3x9, k3x10, k3x11, k3x12, k3x13, k3x14, k3x15, \
        k4x8, k4x9, k4x10, k4x11, k4x12, k4x13,        k4x15, \
        k5x8,       k5x10, k5x11, k5x12, k5x13, k5x14, k5x15, \
                    k6x10, k6x11, k6x12, k6x13,        k6x15 \
) { \
  {k0x0, k0x1, k0x2, k0x3, k0x4, k0x5, k0x6, k0x7, k0x8, k0x9, k0x10, k0x11, k0x12, k0x13, k0x14, k0x15}, \
  {k1x0, k1x1, k1x2, k1x3, k1x4, k1x5, k1x6, k1x7, k1x8, k1x9, k1x10, k1x11, k1x12, k1x13, k1x14, k1x15}, \
  {k2x0, k2x1, k2x2, k2x3, k2x4, k2x5, NONE, NONE, k2x8, k2x9, k2x10, k2x11, k2x12, k2x13, k2x14, k2x15}, \
  {k3x0, k3x1, k3x2, k3x3, k3x4, k3x5, k3x6, k3x7, k3x8, k3x9, k3x10, k3x11, k3x12, k3x13, k3x14, k3x15}, \
  {NONE, k4x1, k4x2, k4x3, k4x4, k4x5, NONE, NONE, k4x8, k4x9, k4x10, k4x11, k4x12, k4x13, NONE,  k4x15}, \
  {k5x0, k5x1, k5x2, k5x3, NONE, k5x5, NONE, NONE, k5x8, NONE, k5x10, k5x11, k5x12, k5x13, k5x14, k5x15}, \
  {k6x0, k6x1, NONE, k6x3, NONE, NONE, NONE, NONE, NONE, NONE, k6x10, k6x11, k6x12, k6x13, NONE,  k6x15}, \
}

enum keymap_layers {
  QWERTY_LAYER,
  DVORAK_LAYER,
  COMMON_LAYER,
  END_LAYER,
};

const uint16_t PROGMEM keymaps[][SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS] = {
  [QWERTY_LAYER] = KEYMAP(
    // Left
    ____,                      ____, ____, ____, ____, ____, ____,
    K(GRAVE_ACCENT_AND_TILDE), ____, ____, ____, ____, ____, ____,
    ____,                      K(Q), K(W), K(E), K(R), K(T),
    ____,                      K(A), K(S), K(D), K(F), K(G), ____,
                               K(Z), K(X), K(C), K(V), K(B),
    ____,                      ____, ____, ____,       ____,
    ____,                      ____,       ____,
    // Right
    ____, ____, ____, ____,                        ____,                         ____,                       ____,                                 ____,                                 ____,
    ____, ____, ____, ____,                        ____,                         ____,                       K(MINUS_AND_UNDERSCORE),              K(EQUAL_AND_PLUS),                    ____,
          K(Y), K(U), K(I),                        K(O),                         K(P),                       K(OPENING_BRACKET_AND_OPENING_BRACE), K(CLOSING_BRACKET_AND_CLOSING_BRACE), ____,
    ____, K(H), K(J), K(K),                        K(L),                         K(SEMICOLON_AND_COLON),     K(APOSTROPHE_AND_QUOTE),              ____,                                 ____,
          K(N), K(M), K(COMMA_AND_LESS_THAN_SIGN), K(DOT_AND_GREATER_THAN_SIGN), K(SLASH_AND_QUESTION_MARK), K(BACKSLASH_AND_PIPE),                                                      ____,
          ____,       ____,                        ____,                         ____,                       ____,                                 ____,                                 ____,
                      ____,                        ____,                         ____,                       ____,                                                                       ____
  ),
  [DVORAK_LAYER] = KEYMAP(
    // Left
    ____,                      ____,                   ____,                         ____,                         ____, ____, ____,
    K(GRAVE_ACCENT_AND_TILDE), ____, ____, ____, ____, ____,                         ____,
    ____,                      K(APOSTROPHE_AND_QUOTE), K(COMMA_AND_LESS_THAN_SIGN), K(DOT_AND_GREATER_THAN_SIGN), K(P), K(Y),
    ____,                      K(A),                    K(O),                        K(E),                         K(U), K(I), ____,
                               K(SEMICOLON_AND_COLON),  K(Q),                        K(J),                         K(K), K(X),
    ____,                      ____,                    ____,                        ____,                               ____,
    ____,                      ____,                                                 ____,
    // Right
    ____, ____, ____, ____, ____, ____, ____,                                 ____,                                 ____,
    ____, ____, ____, ____, ____, ____, K(OPENING_BRACKET_AND_OPENING_BRACE), K(CLOSING_BRACKET_AND_CLOSING_BRACE), ____,
          K(F), K(G), K(C), K(R), K(L), K(SLASH_AND_QUESTION_MARK),           K(EQUAL_AND_PLUS),                    ____,
    ____, K(D), K(H), K(T), K(N), K(S), K(MINUS_AND_UNDERSCORE),              ____,                                 ____,
          K(B), K(M), K(W), K(V), K(Z), K(BACKSLASH_AND_PIPE),                                                      ____,
          ____,       ____, ____, ____, ____,                                 ____,                                 ____,
                      ____, ____, ____, ____,                                                                       ____
  ),
  [COMMON_LAYER] = KEYMAP(
    // Left
    K(ESCAPE),       K(F1),                K(F2),          K(F3),             K(F4),           K(F5),               K(DELETE),
    ____,            K(1_AND_EXCLAMATION), K(2_AND_AT),    K(3_AND_HASHMARK), K(4_AND_DOLLAR), K(5_AND_PERCENTAGE), K(BACKSPACE),
    K(TAB),          ____,                 ____,           ____,              ____,            ____,
    K(LEFT_SHIFT),   ____,                 ____,           ____,              ____,            ____,                K(ENTER),
                     ____,                 ____,           ____,              ____,            ____,
    K(LEFT_CONTROL), K(MEDIA_PLAY),        K(APPLICATION), TODO,                               K(SPACE),
    TODO,            K(LEFT_GUI),                          K(LEFT_ALT),
    // Right
    K(DELETE),    K(F6),          K(F7),              K(F8),             K(F9),                        K(F10),                       K(F11),         K(F12),           TODO,
    K(BACKSPACE), K(6_AND_CARET), K(7_AND_AMPERSAND), K(8_AND_ASTERISK), K(9_AND_OPENING_PARENTHESIS), K(0_AND_CLOSING_PARENTHESIS), ____,           ____,             K(MEDIA_CALCULATOR),
                  ____,           ____,               ____,              ____,                         ____,                         ____,           ____,             TODO,
    K(ENTER),     ____,           ____,               ____,              ____,                         ____,                         ____,           K(RIGHT_SHIFT),   K(CAPS_LOCK),
                  ____,           ____,               ____,              ____,                         ____,                         ____,                             TODO,
                  K(SPACE),                           TODO,              K(HOME),                      K(UP_ARROW),                  K(END),         K(RIGHT_CONTROL), K(PAGE_UP),
                                                      K(RIGHT_ALT),      K(LEFT_ARROW),                K(DOWN_ARROW),                K(RIGHT_ARROW),                   K(PAGE_DOWN)
  ),
};



// const uint16_t PROGMEM keymap_template[SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS] = KEYMAP(
//   // Left
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//         NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE,       NONE,
//   NONE, NONE,       NONE,
//   // Right
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//         NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//   NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
//         NONE, NONE, NONE, NONE, NONE, NONE,       NONE,
//         NONE,       NONE, NONE, NONE, NONE, NONE, NONE,
//                     NONE, NONE, NONE, NONE,       NONE
// );

#endif

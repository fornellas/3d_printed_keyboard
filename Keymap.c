#include "Keymap.h"
#include "ScanKeys.h"
#include "LayerState.h"
#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>

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

const uint8_t layer_initial_state[LAYER_COUNT] = {
  [FN_LAYER] = KEYMAP_START_DISABLED,
  [KEYPAD_LAYER] = KEYMAP_START_DISABLED,
  [QWERTY_LAYER] = KEYMAP_START_LOAD,
  [DVORAK_LAYER] = KEYMAP_START_LOAD,
  [COMMON_LAYER] = KEYMAP_START_ENABLED,
};

const uint8_t keymap_layout_layers[LAYOUT_LAYERS_COUNT] = {
  QWERTY_LAYER,
  DVORAK_LAYER,
};

const uint16_t PROGMEM keymaps[LAYER_COUNT][SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS] = {
  [FN_LAYER] = KEYMAP(
    // Left
    ____, LAYOUT(QWERTY_LAYER), LAYOUT(DVORAK_LAYER), ____,          ____, ____, K(INSERT),
    ____, ____,                 ____,                 ____,          ____, ____, K(VOLUME_UP),
    ____, ____,                 ____,                 ____,          ____, ____,
    ____, ____,                 ____,                 ____,          ____, ____, K(VOLUME_DOWN),
          ____,                 ____,                 ____,          ____, ____,
    ____, TODO("cut"),          TODO("copy"),         TODO("paste"),       K(MUTE),
    NONE, ____,                                       ____,
    // Right
    K(INSERT), K(MEDIA_EJECT), K(POWER), K(MEDIA_SLEEP),          TODO("wake"), K(PRINT_SCREEN), K(SCROLL_LOCK), ____, K(NUM_LOCK),
    ____,      ____,           ____,     ____,                    ____,         ____,            ____,           ____, ____,
               ____,           ____,     ____,                    ____,         ____,            ____,           ____, ____,
    ____,      ____,           ____,     ____,                    ____,         ____,            ____,           ____, ____,
               ____,           ____,     ____,                    ____,         ____,            ____,                 ____,
               K(MUTE),                  K(MEDIA_PREVIOUS_TRACK), ____,         ____,            ____,           ____, K(MEDIA_BACKWARD),
                                         K(MEDIA_NEXT_TRACK),     ____,         ____,            ____,                 K(MEDIA_FORWARD)
  ),
  [KEYPAD_LAYER] = KEYMAP(
    // Left
    ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____,
          ____, ____, ____, ____, ____,
    ____, ____, ____, ____,       ____,
    ____, ____,       ____,
    // Right
    ____, ____,          ____,          ____,           ____,                       ____,                       ____,                        ____,            ____,
    ____, ____,          ____,          ____,           ____,                       ____,                       ____,                        ____,            ____,
          ____,          ____,          ____,           K(TAB),                     K(KEYPAD_SLASH),            K(KEYPAD_ASTERISK),          K(KEYPAD_MINUS), SEQ(SEQ_B_TAB),
    ____, K(HOME),       K(UP_ARROW),   K(END),         K(KEYPAD_7_AND_HOME),       K(KEYPAD_8_AND_UP_ARROW),   K(KEYPAD_9_AND_PAGE_UP),     K(KEYPAD_PLUS),  K(ERROR_ROLLOVER),
          K(LEFT_ARROW), K(DOWN_ARROW), K(RIGHT_ARROW), K(KEYPAD_4_AND_LEFT_ARROW), K(KEYPAD_5),                K(KEYPAD_6_AND_RIGHT_ARROW),                  K(KEYPAD_BACKSPACE),
          ____,                         ____,           K(KEYPAD_1_AND_END),        K(KEYPAD_2_AND_DOWN_ARROW), K(KEYPAD_3_AND_PAGE_DOWN),   K(KEYPAD_ENTER), ____,
                                        ____,           K(KEYPAD_0_AND_INSERT),     SEQ(SEQ_00),                K(KEYPAD_DOT_AND_DELETE),                     ____
  ),
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
    K(ESCAPE),                       K(F1),                K(F2),          K(F3),             K(F4),           K(F5),               K(DELETE),
    ____,                            K(1_AND_EXCLAMATION), K(2_AND_AT),    K(3_AND_HASHMARK), K(4_AND_DOLLAR), K(5_AND_PERCENTAGE), K(BACKSPACE),
    K(TAB),                          ____,                 ____,           ____,              ____,            ____,
    K(LEFT_SHIFT),                   ____,                 ____,           ____,              ____,            ____,                K(ENTER),
                                     ____,                 ____,           ____,              ____,            ____,
    K(LEFT_CONTROL),                 K(MEDIA_PLAY),        K(APPLICATION), SEQ(SEQ_SHUFFLE),                   K(SPACE),
    MACRO(MACRO_FN),                 K(LEFT_GUI),                          K(LEFT_ALT),
    // Right
    K(DELETE),    K(F6),          K(F7),              K(F8),             K(F9),                        K(F10),                       K(F11),         K(F12),           MACRO(MACRO_KEYPAD),
    K(BACKSPACE), K(6_AND_CARET), K(7_AND_AMPERSAND), K(8_AND_ASTERISK), K(9_AND_OPENING_PARENTHESIS), K(0_AND_CLOSING_PARENTHESIS), ____,           ____,             K(MEDIA_CALCULATOR),
                  ____,           ____,               ____,              ____,                         ____,                         ____,           ____,             TODO('mail'),
    K(ENTER),     ____,           ____,               ____,              ____,                         ____,                         ____,           K(RIGHT_SHIFT),   K(CAPS_LOCK),
                  ____,           ____,               ____,              ____,                         ____,                         ____,                             TODO('www'),
                  K(SPACE),                           SEQ(SEQ_DESKTOP),  K(HOME),                      K(UP_ARROW),                  K(END),         K(RIGHT_CONTROL), K(PAGE_UP),
                                                      K(RIGHT_ALT),      K(LEFT_ARROW),                K(DOWN_ARROW),                K(RIGHT_ARROW),                   K(PAGE_DOWN)
  ),
};

uint8_t keypad_state;

void Keymap_Init(void)
{
  keypad_state = 0;
}

void macro_fn(struct Key key)
{
  if(key.just_pressed) {
    LayerState_Set(FN_LAYER, 1);
    LayerState_Set(KEYPAD_LAYER, 1);
  }
  if(key.just_released) {
    LayerState_Set(FN_LAYER, 0);
    LayerState_Set(KEYPAD_LAYER, keypad_state);
  }
}

void macro_keypad(struct Key key)
{
  if(key.just_pressed) {
    keypad_state = !keypad_state;
    LayerState_Set(KEYPAD_LAYER, keypad_state);
  }
}

// FIXME warning: initialization from incompatible pointer type
const void (*keymap_macros[MACRO_COUNT])(struct Key) = {
  [MACRO_FN] = &macro_fn,
  [MACRO_KEYPAD] = &macro_keypad,
};

uint16_t seq_shuffle[] = {
  1,
  HID_KEYBOARD_SC_LEFT_ALT,
  2,
  HID_KEYBOARD_SC_LEFT_ALT,
  HID_KEYBOARD_SC_TAB,
  0,
};

uint16_t seq_00[] = {
  2,
  HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
  HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
  0,
};

uint16_t seq_b_tab[] = {
  1,
  HID_KEYBOARD_SC_LEFT_SHIFT,
  2,
  HID_KEYBOARD_SC_LEFT_SHIFT,
  HID_KEYBOARD_SC_TAB,
  0,
};

uint16_t seq_desktop[] = {
  2,
  HID_KEYBOARD_SC_LEFT_CONTROL,
  HID_KEYBOARD_SC_LEFT_ALT,
  2,
  HID_KEYBOARD_SC_LEFT_CONTROL,
  HID_KEYBOARD_SC_LEFT_ALT,
  HID_KEYBOARD_SC_D,
  0,
};

const uint16_t (*keymap_seqs[])[SEQ_COUNT] = {
  [SEQ_SHUFFLE] = seq_shuffle,
  [SEQ_00] = seq_00,
  [SEQ_B_TAB] = seq_b_tab,
  [SEQ_DESKTOP] = seq_desktop,
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

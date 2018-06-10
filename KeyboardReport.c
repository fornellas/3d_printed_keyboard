#include "LayerState.h"
#include "KeyboardReport.h"
#include "Keymap.h"
#include "Sequence.h"

void KeyboardReport_Add_KeyboardKeypad(USB_ExtendedKeyboardReport_Data_t* KeyboardReport, uint16_t KeyCode)
{
  switch(KeyCode){
    case HID_KEYBOARD_SC_LEFT_CONTROL:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_LEFTCTRL;
      break;
    case HID_KEYBOARD_SC_LEFT_SHIFT:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_LEFTSHIFT;
      break;
    case HID_KEYBOARD_SC_LEFT_ALT:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_LEFTALT;
      break;
    case HID_KEYBOARD_SC_LEFT_GUI:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_LEFTGUI;
      break;
    case HID_KEYBOARD_SC_RIGHT_CONTROL:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTCTRL;
      break;
    case HID_KEYBOARD_SC_RIGHT_SHIFT:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTSHIFT;
      break;
    case HID_KEYBOARD_SC_RIGHT_ALT:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTALT;
      break;
    case HID_KEYBOARD_SC_RIGHT_GUI:
      KeyboardReport->Modifier |= HID_KEYBOARD_MODIFIER_RIGHTGUI;
      break;
    default:
      for(uint8_t i=0 ; i < MAX_KEYS ; i++)
        if(KeyboardReport->KeyboardKeyPad[i] == KeyCode)
          goto end;
      for(uint8_t i=0 ; i < MAX_KEYS ; i++){
        if(KeyboardReport->KeyboardKeyPad[i] == 0){
          KeyboardReport->KeyboardKeyPad[i] = KeyCode;
          break;
        }
      }
      end:
      break;
  }
}

void KeyboardReport_Add_GenericDesktop(USB_ExtendedKeyboardReport_Data_t* KeyboardReport, uint16_t KeyCode)
{
  for(uint8_t i=0 ; i < MAX_KEYS ; i++)
    if(KeyboardReport->GenericDesktop[i] == KeyCode)
      return;
  for(uint8_t i=0 ; i < MAX_KEYS ; i++){
    if(KeyboardReport->GenericDesktop[i] == 0){
      KeyboardReport->GenericDesktop[i] = KeyCode;
      break;
    }
  }
}

void KeyboardReport_Add_Consumer(USB_ExtendedKeyboardReport_Data_t* KeyboardReport, uint16_t KeyCode)
{
  for(uint8_t i=0 ; i < MAX_KEYS ; i++)
    if(KeyboardReport->Consumer[i] == KeyCode)
      return;
  for(uint8_t i=0 ; i < MAX_KEYS ; i++){
    if(KeyboardReport->Consumer[i] == 0){
      KeyboardReport->Consumer[i] = KeyCode;
      break;
    }
  }
}

void KeyboardReport_ScanKeys_Callback(struct Key key, void *data)
{
  USB_ExtendedKeyboardReport_Data_t* KeyboardReport;
  uint16_t key_value;
  uint8_t layout;

  KeyboardReport = (USB_ExtendedKeyboardReport_Data_t*)data;

  for(uint8_t i=0 ; i < LAYER_COUNT ; i++) {
    if(!LayerState_Get(i))
      continue;

#ifdef SERIAL_DEBUG
    if(key.state||key.just_pressed||key.just_released){
      printf_P(PSTR("Key: %dx%d\n\r"), key.row, key.column);
      printf_P(PSTR("  state: %d\n\r"), key.state);
      printf_P(PSTR("  just_pressed: %d\n\r"), key.just_pressed);
      printf_P(PSTR("  just_released: %d\n\r"), key.just_released);
    }
#endif

    key_value = pgm_read_word(&(keymaps[i][key.row][key.column]));

    Keymap_ScannedKeyCallback(key, key_value);

    switch(GET_KEY_FN(key_value)){
      case KEY_FN_KEYBOARD_PAGE:
        if(key.state)
          KeyboardReport_Add_KeyboardKeypad(KeyboardReport, GET_KEY_VALUE(key_value));
        goto finish;
        break;
      case KEY_FN_GENERIC_DESKTOP_PAGE:
        if(key.state)
          KeyboardReport_Add_GenericDesktop(KeyboardReport, GET_KEY_VALUE(key_value));
        goto finish;
        break;
      case KEY_FN_CONSUMER_PAGE_PAGE:
        if(key.state)
          KeyboardReport_Add_Consumer(KeyboardReport, GET_KEY_VALUE(key_value));
        goto finish;
        break;
      case KEY_FN_NONE:
        goto finish;
        break;
      case KEY_FN_PASS:
        break;
      case KEY_FN_MACRO:
        keymap_macros[GET_KEY_VALUE(key_value)](key, KeyboardReport);
        goto finish;
        break;
      case KEY_FN_LAYOUT:
        layout = GET_KEY_VALUE(key_value);
        if(key.just_pressed)
          LayerState_SetLayout(layout);
        goto finish;
        break;
      case KEY_FN_SEQ:
        if(key.just_pressed)
          Sequence_Register((uint16_t *)keymap_seqs[GET_KEY_VALUE(key_value)]);
        goto finish;
        break;
    }
  }
  finish: ;
}

#include "GenerateKeyboardReport.h"
#include "Keymap.h"
#include "EEPROM_Addresses.h"

uint8_t layer_state[END_LAYER - 1];

void Add_KeyCode_to_USB_KeyboardReport_Data(USB_KeyboardReport_Data_t* KeyboardReport, uint16_t KeyCode)
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
      for(uint8_t i=0 ; i < 6 ; i++)
        if(KeyboardReport->KeyCode[i] == KeyCode)
          goto end;
      for(uint8_t i=0 ; i < 6 ; i++){
        if(KeyboardReport->KeyCode[i] == 0){
          KeyboardReport->KeyCode[i] = KeyCode;
          break;
        }
      }
      end:
      break;
  }
}

void GenerateKeyboardReport_Init()
{
  for(uint8_t i=0 ; i < END_LAYER ; i++) {
    switch(layer_initial_state[i]){
      case KEYMAP_START_ENABLED:
        layer_state[i] = 1;
        break;
      case KEYMAP_START_DISABLED:
        layer_state[i] = 0;
        break;
      case KEYMAP_START_LOAD:
        layer_state[i] = eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT_STATES+i);
        break;
    }
  }
}

void GenerateKeyboardReport(struct Key key, void *data)
{
  USB_KeyboardReport_Data_t* KeyboardReport;
  uint16_t key_value;

  KeyboardReport = (USB_KeyboardReport_Data_t*)data;

  for(uint8_t i=0 ; i < END_LAYER ; i++) {
    if(!layer_state[i])
      continue;

    key_value = pgm_read_word(&(keymaps[i][key.row][key.column]));

    switch(GET_KEY_FN(key_value)){
      case KEY_FN_REG:
        if(key.state) {
           Add_KeyCode_to_USB_KeyboardReport_Data(KeyboardReport, GET_KEY_CODE(key_value));
           goto finish;
        }
        break;
      case KEY_FN_NONE:
        goto finish;
        break;
      case KEY_FN_PASS:
        break;
    }
  }
  finish: ;
}
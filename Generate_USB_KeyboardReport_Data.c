#include "Generate_USB_KeyboardReport_Data.h"
#include "Keymap.h"

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

void Generate_USB_KeyboardReport_Data(struct Key key, void *data)
{
  USB_KeyboardReport_Data_t* KeyboardReport;
  uint16_t key_value;

  KeyboardReport = (USB_KeyboardReport_Data_t*)data;
  if(!key.state)
    return;
  key_value = pgm_read_byte_near(&(keymap_qwerty[key.row][key.column]));
  switch(GET_KEY_FN(key_value)){
    case KEY_FN_REG:
      if(key.state)
         Add_KeyCode_to_USB_KeyboardReport_Data(KeyboardReport, GET_KEY_CODE(key_value));
      break;
    case KEY_FN_NONE:
      break;
    case KEY_FN_PASS:
      break;
  }

}

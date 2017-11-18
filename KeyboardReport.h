#ifndef _KEYBOARD_REPORT_H_
#define _KEYBOARD_REPORT_H_

#include "ScanKeys.h"
#include <LUFA/Drivers/USB/USB.h>

void KeyboardReport_ScanKeys_Callback(struct Key key, void *data);
void KeyboardReport_Add_KeyCode(USB_KeyboardReport_Data_t* KeyboardReport, uint16_t KeyCode);

#endif

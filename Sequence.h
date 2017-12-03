#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "Keyboard.h"
#include <inttypes.h>
#include <LUFA/Drivers/USB/USB.h>

void Sequence_Init(void);
void Sequence_Register(uint16_t *seq);
void Sequence_Play(USB_ExtendedKeyboardReport_Data_t* KeyboardReport);

#endif

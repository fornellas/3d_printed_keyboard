#ifndef _LAYOUT_STATE_H_
#define _LAYOUT_STATE_H_

#include <inttypes.h>

void LayoutState_Init(void);
uint8_t LayoutState_Get(uint8_t id);
void LayoutState_Set(uint8_t id, uint8_t value);

#endif

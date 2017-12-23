#ifndef _LAYER_STATE_H_
#define _LAYER_STATE_H_

#include <inttypes.h>

extern uint8_t layout_changes;

void LayerState_Init(void);

uint8_t LayerState_Get(uint8_t id);

void LayerState_Set(uint8_t id, uint8_t value);

uint8_t LayerState_Get_Active_Layout(void);

void LayerState_SetLayout(uint8_t layout);

#endif

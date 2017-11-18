#ifndef _LAYER_STATE_H_
#define _LAYER_STATE_H_

#include <inttypes.h>

void LayerState_Init(void);
uint8_t LayerState_Get(uint8_t id);
void LayerState_Set(uint8_t id, uint8_t value);

#endif

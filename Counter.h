#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <inttypes.h>

void Counter_Init(void);

void Counter_Reset(void);

void Counter_Add(void);

uint32_t Counter_Get(void);

#endif

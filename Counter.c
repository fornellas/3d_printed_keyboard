#include "Counter.h"

uint32_t counter;

void Counter_Init(void)
{
  Counter_Reset();
}

void Counter_Reset(void)
{
  counter = 0;
}

void Counter_Add(void)
{
  counter++;
}

uint32_t Counter_Get(void)
{
  return counter;
}

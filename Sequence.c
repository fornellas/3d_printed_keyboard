#include "Sequence.h"
#include "KeyboardReport.h"
#include <stdlib.h>
#include <string.h>

uint16_t *sequence;

void Sequence_Init()
{
  sequence = NULL;
}

size_t Sequence_Len(uint16_t *seq)
{
  size_t len = 1;

  for(uint8_t i=0 ;  ; i++)
    if(seq[i])
      len++;
    else
      break;
  return len;
}

void Sequence_Register(uint16_t *seq)
{
  if(sequence == NULL) {
    size_t size = sizeof(uint16_t) * Sequence_Len(seq);
    sequence = (uint16_t *)malloc(size);
    memcpy((void *)sequence, (const void *)seq, (size_t)size);
  }
}

void Sequence_Play(USB_KeyboardReport_Data_t* KeyboardReport)
{
  uint8_t start;
  uint8_t key_start;
  uint8_t len;

  if(sequence == NULL)
    return;

  start = 0;
  while(sequence[start] == 0)
    start++;
  len = sequence[start];
  key_start = start + 1;

  for(uint8_t key=key_start ; key <= start + len ; key++)
    KeyboardReport_Add_KeyCode(KeyboardReport, sequence[key]);

  for(uint8_t i=start ; i <= start + len ; i++)
    sequence[i] = 0;

  if(sequence[start + len + 1] == 0){
    free(sequence);
    sequence = NULL;
  }
}

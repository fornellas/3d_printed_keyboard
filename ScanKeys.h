#ifndef _SCAN_KEYS_H_
#define _SCAN_KEYS_H_

#include <avr/io.h>

struct ScanKeys_Address {
  uint8_t row;
  uint8_t column;
};

void ScanKeys_Init(void);
void ScanKeys_Read(void (*scan_keys_callback)(struct ScanKeys_Address, void *data), void *data);


#endif

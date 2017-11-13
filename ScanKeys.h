#ifndef _SCAN_KEYS_H_
#define _SCAN_KEYS_H_

#include <avr/io.h>

void ScanKeys_Init(void);
void ScanKeys_Read(void (*key_read_callback)(uint8_t row, uint8_t column));

#endif

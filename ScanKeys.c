#include "ScanKeys.h"

#define SCAN_MATRIX_LEFT_COLUMNS 7

void ScanKeys_Init_Left(void)
{
  DDRA &= ~0b01111111; // Rows as input...
  PORTA |= 0b01111111; // ...with pull up.
  DDRC |= 0b01111111; // Columns as output...
  PORTC |= 0b01111111; // ...and high.
}

void ScanKeys_Init_Right(void)
{
  // TODO
}

void ScanKeys_Init(void)
{
  ScanKeys_Init_Left();
  ScanKeys_Init_Right();
}

void ScanKeys_Read_Left(void (*scan_keys_callback)(struct ScanKeys_Address, void *data), void *data)
{
  struct ScanKeys_Address address;

  for(uint8_t column=0;column<SCAN_MATRIX_LEFT_COLUMNS;column++) {
    PORTC &= ~(1<<column); // set column low
    for(uint8_t row=0;row<SCAN_MATRIX_ROWS;row++) {
      if(!(PINA&(1<<row))) {
        address.row = row;
        address.column = SCAN_MATRIX_LEFT_COLUMNS - column - 1;
        (*scan_keys_callback)(address, data);
      }
    }
    PORTC |= 1<<column; // set column high
  }
}

void ScanKeys_Read_Right(void (*scan_keys_callback)(struct ScanKeys_Address, void *data), void *data)
{
  // TODO
}

void ScanKeys_Read(void (*scan_keys_callback)(struct ScanKeys_Address, void *data), void *data)
{
  ScanKeys_Read_Left(scan_keys_callback, data);
  ScanKeys_Read_Right(scan_keys_callback, data);
}

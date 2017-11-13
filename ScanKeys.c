#include "ScanKeys.h"

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

void ScanKeys_Read_Left(void (*key_read_callback)(uint8_t row, uint8_t column))
{
  for(uint8_t column=0;column<7;column++) {
    PORTC &= ~(1<<column); // set column low
    for(uint8_t row=0;row<7;row++) {
      if(!(PINA&(1<<row))) {
        (*key_read_callback)(
          row + 1,
          column + 1
        );
      }
    }
    PORTC |= 1<<column; // set column high
  }
}

void ScanKeys_Read_Right(void (*key_read_callback)(uint8_t row, uint8_t column))
{
  // TODO
}

void ScanKeys_Read(void (*key_read_callback)(uint8_t row, uint8_t column))
{
  ScanKeys_Read_Left(key_read_callback);
  ScanKeys_Read_Right(key_read_callback);
}

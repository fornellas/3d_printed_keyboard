#include "ScanKeys.h"
#include "Counter.h"
#include <avr/io.h>

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

uint8_t previous_state[SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS] = {};

void ScanKeys_Init(void)
{
  ScanKeys_Init_Left();
  ScanKeys_Init_Right();
}

void ScanKeys_Read_Left(void (*scan_keys_callback)(struct Key, void *data), void *data)
{
  struct Key key;

  for(uint8_t column=0;column<SCAN_MATRIX_LEFT_COLUMNS;column++) {
    PORTC &= ~(1<<column); // set column low
    for(uint8_t row=0;row<SCAN_MATRIX_ROWS;row++) {
      key.row = row;
      key.column = SCAN_MATRIX_LEFT_COLUMNS - column - 1;
      if(!(PINA&(1<<row))) {
        key.state = 1;
        if(previous_state[row][column])
          key.just_pressed = 0;
        else {
          key.just_pressed = 1;
          Counter_Add();
        }
        key.just_released = 0;
      } else {
        key.state = 0;
        key.just_pressed = 0;
        if(previous_state[row][column])
          key.just_released = 1;
        else
          key.just_released = 0;
      }
      previous_state[row][column] = key.state;
      (*scan_keys_callback)(key, data);
    }
    PORTC |= 1<<column; // set column high
  }
}

void ScanKeys_Read_Right(void (*scan_keys_callback)(struct Key, void *data), void *data)
{
  // TODO
}

void ScanKeys_Read(void (*scan_keys_callback)(struct Key, void *data), void *data)
{
  ScanKeys_Read_Left(scan_keys_callback, data);
  ScanKeys_Read_Right(scan_keys_callback, data);
}

#include "Counter.h"
#include "Display.h"
#include "ScanKeys.h"
#include <avr/io.h>
#include <LUFA/Drivers/Peripheral/TWI.h>

#define SCAN_MATRIX_LEFT_COLUMNS 7
#define SCAN_MATRIX_RIGHT_COLUMNS 9

#define MCP23017_ADDRESS 0x40
#define MCP23017_BANK0_IOCON 0x0A

#define MCP23017_BANK1_IODIRA 0x00
#define MCP23017_BANK1_GPPUA 0x06
#define MCP23017_BANK1_GPIOA 0x09
#define MCP23017_BANK1_OLATA 0x0A
#define MCP23017_BANK1_IODIRB 0x10
#define MCP23017_BANK1_GPPUB 0x16
#define MCP23017_BANK1_GPIOB 0x19
#define MCP23017_BANK1_OLATB 0x1A

#define MCP23017_TIMEOUT_MS 1

uint8_t ScanKeys_Right_Side_Disconnected;
static uint8_t previous_state[SCAN_MATRIX_ROWS][SCAN_MATRIX_COLUMNS] = {};

static void ScanKeys_Init_Left(void)
{
  DDRA &= ~0b01111111; // Rows as input...
  PORTA |= 0b01111111; // ...with pull up.
  DDRC |= 0b01111111; // Columns as output...
  PORTC |= 0b01111111; // ...and high.
}

static uint8_t MCP23017_WriteByte(uint8_t InternalAddress, uint8_t Data)
{
  if (TWI_StartTransmission(MCP23017_ADDRESS | TWI_ADDRESS_WRITE, MCP23017_TIMEOUT_MS) == TWI_ERROR_NoError) {
      TWI_SendByte(InternalAddress);
      TWI_SendByte(Data);
      TWI_StopTransmission();
      return 1;
  }
  ScanKeys_Right_Side_Disconnected = 1;
  return 0;
}

static uint8_t MCP23017_ReadByte(uint8_t InternalAddress, uint8_t *Data)
{
  if (TWI_StartTransmission(MCP23017_ADDRESS | TWI_ADDRESS_WRITE, MCP23017_TIMEOUT_MS) == TWI_ERROR_NoError) {
      TWI_SendByte(InternalAddress);
      TWI_StopTransmission();
      if (TWI_StartTransmission(MCP23017_ADDRESS | TWI_ADDRESS_READ, MCP23017_TIMEOUT_MS) == TWI_ERROR_NoError) {
          TWI_ReceiveByte(Data, true);
          TWI_StopTransmission();
          return 1;
      }
  }
  ScanKeys_Right_Side_Disconnected = 1;
  return 0;
}

static uint8_t ScanKeys_SetUp_MCP23017(void)
{
  if(!ScanKeys_Right_Side_Disconnected)
    return 1;
  // Rows Input, Pull up
  // 	0	GPB0
  // 	1	GPB1
  // 	2	GPB2
  // 	3	GPB3
  // 	4	GPB4
  // 	5	GPB5
  // 	6	GPB6
  // Columns Output, High
  // 	 7	GPB7
  // 	 8	GPA7
  // 	 9	GPA6
  // 	10	GPA5
  //  11	GPA4
  // 	12	GPA3
  // 	13	GPA2
  // 	14	GPA1
  // 	15	GPA0

  // BANK=1, SEQOP=1
  if(!MCP23017_WriteByte(MCP23017_BANK0_IOCON, 0b10100000))
    return 0;
  // Rows as input, columns as output
  if(!MCP23017_WriteByte(MCP23017_BANK1_IODIRB, 0b01111111))
    return 0;
  if(!MCP23017_WriteByte(MCP23017_BANK1_IODIRA, 0b00000000))
    return 0;
  // Row input pull up
  if(!MCP23017_WriteByte(MCP23017_BANK1_GPPUB, 0b01111111))
    return 0;
  // Columns output high
  if(!MCP23017_WriteByte(MCP23017_BANK1_OLATB, 0b10000000))
    return 0;
  if(!MCP23017_WriteByte(MCP23017_BANK1_OLATA, 0b11111111))
    return 0;

  ScanKeys_Right_Side_Disconnected = 0;

  return 1;
}

static void ScanKeys_Init_Right(void)
{
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 400000));
  ScanKeys_Right_Side_Disconnected = 1;
  ScanKeys_SetUp_MCP23017();
}

void ScanKeys_Init(void)
{
  ScanKeys_Init_Left();
  ScanKeys_Init_Right();
}

uint8_t ScanKeys_SetColumnLow(uint8_t column)
{
  uint8_t Bit;
  static uint8_t anyLatchAdown = 0;
  static uint8_t anyLatchBdown = 0;

  if(column < SCAN_MATRIX_LEFT_COLUMNS) {
    Bit = SCAN_MATRIX_LEFT_COLUMNS - column - 1;
    PORTC = 0b11111111 & ~(1 << Bit);
  } else {
    uint8_t LatchAddress;

    if(!ScanKeys_SetUp_MCP23017())
      return 0;

    if(column == 7) {
      LatchAddress = MCP23017_BANK1_OLATB;
      Bit = 7;
    } else {
      LatchAddress = MCP23017_BANK1_OLATA;
      Bit = 15 - column;
    }

    if(!MCP23017_WriteByte(LatchAddress, 0b11111111 & ~(1 << Bit)))
      return 0;

    if(LatchAddress == MCP23017_BANK1_OLATA) {
      anyLatchAdown = 1;
      if(anyLatchBdown) {
        if(!MCP23017_WriteByte(MCP23017_BANK1_OLATB, 0b11111111))
          return 0;
        anyLatchBdown = 0;
      }
    }

    if(LatchAddress == MCP23017_BANK1_OLATB) {
      anyLatchBdown = 1;
      if(anyLatchAdown) {
        if(!MCP23017_WriteByte(MCP23017_BANK1_OLATA, 0b11111111))
          return 0;
        anyLatchAdown = 0;
      }
    }
  }
  return 1;
}

uint8_t ScanKeys_ReadRows(uint8_t column, uint8_t *state)
{
  if(column < SCAN_MATRIX_LEFT_COLUMNS) {
    *state = PINA;
  } else {
    if(!ScanKeys_SetUp_MCP23017())
      return 0;

    if(!MCP23017_ReadByte(MCP23017_BANK1_GPIOB, state))
      return 0;
  }
  return 1;
}

void ScanKeys_Read(void (*scan_keys_callback)(struct Key, void *data), void *data)
{
  struct Key key;

  for(uint8_t column=0 ; column < SCAN_MATRIX_LEFT_COLUMNS + SCAN_MATRIX_RIGHT_COLUMNS ; column++) {
    uint8_t rows_statuses;

    if(!ScanKeys_SetColumnLow(column))
      continue;

    if(!ScanKeys_ReadRows(column, &rows_statuses))
      continue;

    for(uint8_t row=0 ; row < SCAN_MATRIX_ROWS ; row++) {
      key.row = row;
      key.column = column;

      if(!(rows_statuses & (1 << row))) {
        key.state = 1;

        if(previous_state[row][column])
          key.just_pressed = 0;
        else {
          key.just_pressed = 1;
          Counter_Add();
          Display_Tick();
        }
        key.just_released = 0;
      } else {
        key.state = 0;
        key.just_pressed = 0;

        if(previous_state[row][column]) {
          key.just_released = 1;
          Display_Tick();
        } else
          key.just_released = 0;
      }

      previous_state[row][column] = key.state;
      (*scan_keys_callback)(key, data);
    }
  }
}

#include "LayoutState.h"
#include "Keymap.h"
#include "EEPROM_Addresses.h"
#include <avr/eeprom.h>

uint8_t layer_state[LAYER_COUNT];

void LayoutState_Init(void)
{
  for(uint8_t id=0 ; id < LAYER_COUNT ; id++) {
    switch(layer_initial_state[id]){
      case KEYMAP_START_ENABLED:
        layer_state[id] = 1;
        break;
      case KEYMAP_START_DISABLED:
        layer_state[id] = 0;
        break;
      case KEYMAP_START_LOAD:
        layer_state[id] = eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT_STATES+id);
        break;
    }
  }
}

uint8_t LayoutState_Get(uint8_t id)
{
  return layer_state[id];
}

void LayoutState_Set(uint8_t id, uint8_t value)
{
  layer_state[id] = value;
  if(layer_initial_state[id] == KEYMAP_START_LOAD)
    eeprom_write_byte((uint8_t *)EEPROM_LAYOUT_STATES+id, value);
}

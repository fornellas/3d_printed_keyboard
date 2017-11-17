#include "LayoutState.h"
#include "Keymap.h"
#include "EEPROM_Addresses.h"

uint8_t layer_state[LAYER_COUNT];

void LayoutState_Init(void)
{
  for(uint8_t i=0 ; i < LAYER_COUNT ; i++) {
    switch(layer_initial_state[i]){
      case KEYMAP_START_ENABLED:
        layer_state[i] = 1;
        break;
      case KEYMAP_START_DISABLED:
        layer_state[i] = 0;
        break;
      case KEYMAP_START_LOAD:
        layer_state[i] = eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT_STATES+i);
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
  eeprom_write_byte((const uint8_t *)EEPROM_LAYOUT_STATES+id, value);
}

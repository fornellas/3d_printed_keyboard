#include "LayerState.h"
#include "Keymap.h"
#include "EEPROM_Addresses.h"
#include <avr/eeprom.h>

uint8_t layer_state[LAYER_COUNT];
uint8_t layout_changes=0;

void LayerState_Init(void)
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

uint8_t LayerState_Get(uint8_t id)
{
  return layer_state[id];
}

void LayerState_Set(uint8_t id, uint8_t value)
{
  layer_state[id] = value;
  if(layer_initial_state[id] == KEYMAP_START_LOAD)
    eeprom_write_byte((uint8_t *)EEPROM_LAYOUT_STATES+id, value);
}

uint8_t LayerState_Get_Active_Layout()
{
  for(uint8_t l=0; l < LAYOUT_LAYERS_COUNT ; l++) {
    if(LayerState_Get(keymap_layout_layers[l]))
      return keymap_layout_layers[l];
  }
  return keymap_layout_layers[0];
}


void LayerState_SetLayout(uint8_t layout)
{
  layout_changes += 1;

  for(uint8_t l=0; l < LAYOUT_LAYERS_COUNT ; l++) {
    if(keymap_layout_layers[l] == layout)
      LayerState_Set(layout, 1);
    else
      LayerState_Set(keymap_layout_layers[l], 0);
  }
}
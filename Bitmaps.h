#ifndef _LOGO_H_
#define _LOGO_H_

#include <inttypes.h>

#define BITMAP_LOGO_WIDTH 16
#define BITMAP_LOGO_HEIGHT 44
const uint8_t bitmap_logo[] U8G_PROGMEM = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00001111, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b11111000, 0b00000000,
  0b00000000, 0b00011111, 0b11111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111111, 0b10011000, 0b00000000,
  0b00000000, 0b00011111, 0b11111111, 0b11100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b11110111, 0b10011000, 0b00000000,
  0b00000000, 0b00111111, 0b11111111, 0b10111111, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b11111101, 0b11100111, 0b10111100, 0b00000000,
  0b00000000, 0b00111111, 0b11111111, 0b00111101, 0b11111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111111, 0b10111000, 0b11111111, 0b11111100, 0b00000000,
  0b00000000, 0b00111111, 0b11111111, 0b11111100, 0b11110011, 0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b11001111, 0b00111101, 0b11111111, 0b10000100, 0b00000000,
  0b00000000, 0b01111111, 0b11111111, 0b11111101, 0b11100111, 0b10011111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11110011, 0b11001111, 0b00111111, 0b11110011, 0b10000010, 0b00000000,
  0b00000000, 0b01111111, 0b11111110, 0b00111111, 0b11111111, 0b10011110, 0b11111100, 0b00000000, 0b00000000, 0b00011110, 0b01111001, 0b11111111, 0b11111100, 0b00110001, 0b11000110, 0b00000000,
  0b00000000, 0b01111111, 0b11111110, 0b00010001, 0b11111111, 0b11111100, 0b01111111, 0b11100000, 0b00000111, 0b11111110, 0b01111111, 0b11111111, 0b10001100, 0b00110001, 0b11101111, 0b00000000,
  0b00000000, 0b11111111, 0b11111110, 0b00110000, 0b11000111, 0b00111111, 0b11110011, 0b11111110, 0b01111111, 0b10001111, 0b11111100, 0b11100001, 0b10000110, 0b00111001, 0b11100001, 0b00000000,
  0b00000000, 0b11111111, 0b11111111, 0b10110000, 0b10000010, 0b00011111, 0b11110011, 0b11111111, 0b11111111, 0b11001111, 0b11111000, 0b01100001, 0b10000111, 0b00111000, 0b11100001, 0b00000000,
  0b00000001, 0b11111111, 0b11111000, 0b11111101, 0b11000110, 0b00011000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b00011000, 0b01100001, 0b11000111, 0b00011000, 0b11100001, 0b10000000,
  0b00000001, 0b11111111, 0b11111000, 0b01100011, 0b10110111, 0b11010000, 0b01000111, 0b10111111, 0b01111011, 0b11100011, 0b00001100, 0b01110001, 0b11000011, 0b00001100, 0b01111111, 0b10000000,
  0b00000001, 0b11111111, 0b11111000, 0b01000011, 0b00001100, 0b01111000, 0b01000111, 0b10111110, 0b01111001, 0b11100011, 0b00001100, 0b00110000, 0b11000011, 0b00001110, 0b01111101, 0b11000000,
  0b00000011, 0b11111111, 0b11111110, 0b11000011, 0b00001000, 0b00111110, 0b11001011, 0b11111110, 0b01111111, 0b11100011, 0b10001110, 0b00010000, 0b11100011, 0b10001110, 0b00111001, 0b11000000,
  0b00000011, 0b11111111, 0b11110001, 0b11111011, 0b00001000, 0b00100001, 0b11111011, 0b11111110, 0b01111111, 0b11110001, 0b10000110, 0b00011000, 0b01110011, 0b10000110, 0b00111111, 0b11000000,
  0b00000011, 0b11111111, 0b11110000, 0b10001110, 0b01011111, 0b01100000, 0b10011110, 0b00111100, 0b00111100, 0b01111001, 0b10000111, 0b00011100, 0b01110001, 0b10000110, 0b00111111, 0b11100000,
  0b00000111, 0b11111111, 0b11100000, 0b10000110, 0b00011001, 0b01100001, 0b00010110, 0b01111100, 0b00111110, 0b01110000, 0b11000111, 0b00011100, 0b00110000, 0b11000111, 0b00011100, 0b00100000,
  0b00000111, 0b11111111, 0b11100001, 0b10000100, 0b00010000, 0b11111101, 0b00010100, 0b01111100, 0b00011110, 0b01111000, 0b11000011, 0b00001100, 0b00110000, 0b11100111, 0b00011100, 0b00100000,
  0b00001111, 0b11111111, 0b11000001, 0b11111110, 0b00110000, 0b11000111, 0b11111100, 0b11111000, 0b00011110, 0b01111100, 0b11100011, 0b00001100, 0b00111000, 0b11100011, 0b00011100, 0b00110000,
  0b00001111, 0b11111111, 0b11000011, 0b00011101, 0b10111110, 0b10000010, 0b00101111, 0b11111000, 0b00011111, 0b11111100, 0b01100001, 0b10001111, 0b00111000, 0b01100001, 0b10001111, 0b11110000,
  0b00001111, 0b11111111, 0b11000010, 0b00001000, 0b01100011, 0b11000010, 0b00111111, 0b11110000, 0b00001111, 0b11111100, 0b01100001, 0b10000110, 0b00011000, 0b01100011, 0b11111111, 0b00011000,
  0b00011111, 0b11111111, 0b11111110, 0b00011000, 0b01000001, 0b10110110, 0b01011000, 0b11110000, 0b00001111, 0b00011100, 0b01110001, 0b11000010, 0b00011100, 0b01111111, 0b11101111, 0b00011000,
  0b00011111, 0b11111111, 0b11111111, 0b11111000, 0b01000001, 0b00001111, 0b11010001, 0b01110000, 0b00000111, 0b10011110, 0b00110000, 0b11000011, 0b00011111, 0b11111101, 0b11000111, 0b11111000,
  0b00111111, 0b11111111, 0b10011110, 0b11111111, 0b11111011, 0b00001100, 0b11110001, 0b11100000, 0b00000111, 0b10001111, 0b00110000, 0b11100011, 0b11111111, 0b00111000, 0b11100111, 0b11111100,
  0b00111111, 0b11111111, 0b11111100, 0b11110011, 0b11111111, 0b00001000, 0b10110011, 0b11100000, 0b00000111, 0b11001110, 0b00011000, 0b11111111, 0b11001110, 0b00111101, 0b11100111, 0b10001100,
  0b00111111, 0b11111111, 0b11111111, 0b11110011, 0b11001110, 0b01111000, 0b10100011, 0b11000000, 0b00000011, 0b11001111, 0b00011100, 0b01110011, 0b11001111, 0b00111111, 0b11110011, 0b11001100,
  0b01111111, 0b11111111, 0b01111111, 0b11111111, 0b11011110, 0b00011111, 0b11100111, 0b11000000, 0b00000011, 0b11001111, 0b10011000, 0b00110011, 0b11001111, 0b11111110, 0b01110011, 0b11001110,
  0b01111111, 0b11111111, 0b00111011, 0b11111111, 0b11111100, 0b00000000, 0b01111111, 0b11000000, 0b00000011, 0b11111110, 0b00000000, 0b00111111, 0b11111111, 0b11011100, 0b01111011, 0b11111110,
  0b01111111, 0b11111111, 0b11111000, 0b00011111, 0b11111100, 0b00000000, 0b00000111, 0b10000000, 0b00000001, 0b11100000, 0b00000000, 0b00111111, 0b11110111, 0b10001110, 0b01111111, 0b11111110,
  0b01111111, 0b11111111, 0b11111111, 0b11111000, 0b00011111, 0b10000000, 0b00000011, 0b10000000, 0b00000001, 0b11100000, 0b00000000, 0b00111000, 0b11100011, 0b10011111, 0b11111111, 0b11111110,
  0b01111111, 0b11111111, 0b11111111, 0b11111100, 0b00111111, 0b11111100, 0b00000011, 0b10000000, 0b00000000, 0b11100000, 0b00000001, 0b11111100, 0b11110011, 0b11111111, 0b11111111, 0b11111110,
  0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11100011, 0b00000000, 0b00000000, 0b11100000, 0b01111111, 0b11111100, 0b11111111, 0b11111111, 0b11111111, 0b11111110,
  0b00000011, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11000000,
  0b00000000, 0b00011111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110, 0b00000000, 0b00000000, 0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111000, 0b00000000,
  0b00000000, 0b00000000, 0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110, 0b00000000, 0b00000000, 0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11111111, 0b11111111, 0b11111110, 0b00000000, 0b00000000, 0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b11111111, 0b11111111, 0b11111100, 0b00000000, 0b00000000, 0b00111111, 0b11111111, 0b11111111, 0b11111000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b11111111, 0b11111100, 0b00000000, 0b00000000, 0b00111111, 0b11111111, 0b11111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11111100, 0b00000000, 0b00000000, 0b00011111, 0b11111111, 0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b11111000, 0b00000000, 0b00000000, 0b00011111, 0b11111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111000, 0b00000000, 0b00000000, 0b00011110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
};

#define BITMAP_COMPUTER_WIDTH 2
#define BITMAP_COMPUTER_HEIGHT 13
const uint8_t bitmap_computer[] U8G_PROGMEM = {
  0b1111111, 0b11111111,
  0b1000000, 0b00000001,
  0b1011111, 0b11111001,
  0b1000000, 0b00000001,
  0b1011111, 0b11000001,
  0b1000000, 0b00000001,
  0b1011111, 0b11111101,
  0b1000000, 0b00000001,
  0b1111111, 0b11111111,
  0b0000001, 0b10000000,
  0b0000001, 0b10000000,
  0b0000011, 0b11000000,
  0b0001111, 0b11110000
};

#define BITMAP_KEYBOARD_WIDTH 2
#define BITMAP_KEYBOARD_HEIGHT 13
const uint8_t bitmap_keyboard[] U8G_PROGMEM = {
  0b0000000, 0b00001000,
  0b0000000, 0b00001000,
  0b0000000, 0b00001000,
  0b0000000, 0b11110000,
  0b0000001, 0b00000000,
  0b0000001, 0b00000000,
  0b1111111, 0b11111111,
  0b1000000, 0b00000001,
  0b1010101, 0b01010101,
  0b1000000, 0b00000001,
  0b1010101, 0b01010101,
  0b1000000, 0b00000001,
  0b1111111, 0b11111111
};

#endif
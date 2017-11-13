# 3d_printed_keyboard

A fully 3D printed computer keyboard.

## Hardware

- [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html) (AT90USB1286)
- 1.3'' SPI Serial 128X64 SH1106 OLED Display
- [M2X6L Screws](https://www.ebay.com/itm/12x-M2X6mm-M2X6L-PM2X6-0-Black-Machine-Screws-Laptop-Screw-m2x6-Scrauben-Vis/301430848847?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649)
- [TRRS 3.5mm Audio breakout](https://www.sparkfun.com/products/11570) (you can find "generic" ones cheaper on eBay / Amazon).
- [Cherry MX Brown Keyswitch - MX1A-G1NN](http://www.wasdkeyboards.com/index.php/cherry-mx-brown-keyswitch-mx1a-g1nn-tactile-bump.html)
- 1N4148 Diodes
- MCP23017 I/O Expander.

## Firmware

- Based on the [LUFA](http://www.fourwalledcubicle.com/LUFA.php) USB library.
- [u8glib](https://github.com/olikraus/u8glib) to drive the display.

## STL Files

The source for all 3D models used in this project can be fount at [OnShape](https://cad.onshape.com/documents/70ad0c4316c1f7791e16adf7/w/2614b0b88a96d33de0d37d52/e/1350c0cb06dbf70709189044). From there, STL files can be easily exported.

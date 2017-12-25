# Hardware

The brains of the keyboard is a [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html) (AT90USB1286). It might be an overkill for what is needed, but it does its job. It handles all USB communication, drives the key scan for the left side and the OLED display. The [I2C](https://en.wikipedia.org/wiki/I%C2%B2C) I/O expander handles the key scanning of the right side, so we need only 4 wires between both sides.

## Parts List

- [3D printed parts](design.md).
- [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html) (AT90USB1286)
- 1.3'' SPI Serial 128X64 SH1106 OLED Display
- [M2X6L Screws](https://www.ebay.com/itm/12x-M2X6mm-M2X6L-PM2X6-0-Black-Machine-Screws-Laptop-Screw-m2x6-Scrauben-Vis/301430848847?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649)
- [TRRS 3.5mm Audio breakout](https://www.sparkfun.com/products/11570) (you can find "generic" ones cheaper on eBay / Amazon).
- [TRRS 3.5mm Audio Cable](https://www.amazon.co.uk/gp/product/B01HPPO814/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1)
- [Cherry MX Brown Keyswitch - MX1A-G1NN](http://www.wasdkeyboards.com/index.php/cherry-mx-brown-keyswitch-mx1a-g1nn-tactile-bump.html)
- 1N4148 Diodes
- MCP23017 I/O Expander.

## Pictures

To avoid [ghosting](http://blog.komar.be/how-to-make-a-keyboard-the-matrix/), each Cherry MX key has its own diode:

![Diode](/{{ site.github.repository_name }}/pictures/Diode.jpg)

The switches are wired from below, using uninsulated wires and insulating with heat shring tube where needed:

![Wiring](/{{ site.github.repository_name }}/pictures/Wiring.jpg)

The Teensy is at the corner, exposing its USB connection. Here you can see all the wires attached to it, and the 2 pull-up resistors needed for I2C:

![Teensy](/{{ site.github.repository_name }}/pictures/Teensy.jpg)

And its reset button, accessible from the back:

![Reset](/{{ site.github.repository_name }}/pictures/Reset.jpg)

Below the Teensy, there's a 3D printed spacer and below it, the OLED screen:

![OLED](/{{ site.github.repository_name }}/pictures/OLED.jpg)

The right side houses a small PCB with the I/O expander chip (not visible in the picture):

![IOExpander](/{{ site.github.repository_name }}/pictures/IOExpander.jpg)

Here are the final assembled parts. The red PCB on the top is the female TRRS 3.5mm jack:

![InsideLeft](/{{ site.github.repository_name }}/pictures/InsideLeft.jpg)
![InsideRight](/{{ site.github.repository_name }}/pictures/InsideRight.jpg)

Some keys need [stabilization](https://deskthority.net/wiki/Stabiliser), which was crafted using regular paper clips and a plier:

![Stabilizer](/{{ site.github.repository_name }}/pictures/Stabilizer.jpg)

The plastic parts can be easily screwed in, to get to the final result:

![Top View](/{{ site.github.repository_name }}/pictures/Top.jpeg)

## Possible Improvements

Using a TRRS jack for connecting both sides was not the best option. When you connect the male jack, it shorts some paths inside the female jack for a brief period. This is far from optimal. As newer Ergodox keyboards are doing, it would be best to use something like a regular USB connector for safety.
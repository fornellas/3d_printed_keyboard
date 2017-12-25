![Top View](/{{ site.github.repository_name }}/pictures/Top.jpeg)

This is a fully 3D printed keyboard designed completely from the ground up.

# History

After working for almost a decade typing behind a keyboard, around 2011 I started feeling wrist pain. Having a whole carreer ahead of me, I decided I had to do something to avoid [RSI](https://en.wikipedia.org/wiki/Repetitive_strain_injury). By that time, I bought myself 2 (TypeMatrix)[http://typematrix.com/] keyboards and started the switch to [Dvorak](https://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard) layout. Six months in with this new setup, I was typing Dvorak 20% faster than when I used QWERTY.

During that time, I absolutely fell in love with TypeMatrix layout:

- Vertically aligned keys are a breeze to use: no more looking down to reach ANY key.
- Compact design allows to properly center it on the desk, while keeping the mouse at a comfortable distance.
- The hardware keypad means not loosing the keypad.
- Home / End and Page Up/Down close to the arows are very productive.
- Putting Delete, Backspace and Enter at the center means those frequent keys are pressed by the index finger from any hand, decreasing hand movement and load on the pinky finger.
- Vertically spread Shift keys are very convenient.
- Hardware implementation of Alt+Tab with a single key press is amazing.
- Hardware implementation of Ctrl+X/C/V means I didn't loose anything with Dvorak (which otherwise would require 2 hands).

This is all great, but obviously there were caveats:

- The hardware Dvorak translation works great, but you have to manually enable it at every boot.
- Although [its spec](http://typematrix.com/2030/tech-specs.php) states its actuation force is 55 g ± 10 g, my keyboards, after a few years of use, only actuate with ~74g on top of the keys. As a comparison, this is close to the heaviest Cherry MX out there (80cN).
- TypeMatrix provide [silicone skins](http://typematrix.com/skins.php), which sound great, but in significantly increase the actuation force needed, making the previous issue worse.
- It is a [membrane](https://en.wikipedia.org/wiki/Membrane_keyboard) keyboard. Although rated for [10 million strokes](http://typematrix.com/2030/tech-specs.php), I found both my keyboards failing some keys after just mere thousands of key presses. I had to replace both once, and disassembly, clean, close every now and them due to failing keys.
- The few LED status can be quite cryptic... certainly not showing everything that is there.
- No way to reprogram the layout. Living in Brazil, I'd like to add hardware Dvorak to an [ABNT2](https://en.wikipedia.org/wiki/Portuguese_keyboard_layout) layout.

## Hacking TypeMatrix keyboard

In 2012, I had a sky accident, that got me stuck to a wheel chair for a month and at home for 6 months. Having plenty of time available, I decided fix the firmware issues.
At that time, [Arduino Leonardo](https://www.arduino.cc/en/Main/arduinoBoardLeonardo) was introduced, supporting [emulating a keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/), so it was a perfect fit for doing this. I quickly assembled a prototype:

![TypeMatrix prototype](/{{ site.github.repository_name }}/pictures/TypeMatrix/Prototype.jpg)

That worked very well! Only problem: Arduino keyboard support was very limited. It wouldn't work at the BIOS and could not send any "special" keys like the usual multimedia keys. That was a deal breaker.

Going out of Arduino environment, we had the [V-USB](https://www.obdev.at/products/vusb/index.html) library, that should do the trick. Problem is, since it is a software solution, I found many reports of random incompatibilities with Linux or Mac. Not an option as well.

I finally found a library called MyUSB (renamed to [LUFA](http://www.fourwalledcubicle.com/LUFA.php)). This was the real deal. It had all the features needed.

Not being able to affordably buy a compatible FPC connector, I cannibalized TypeMatrix's PCB:

![Cannybalized PCB](/{{ site.github.repository_name }}/pictures/TypeMatrix/Cannibalyse.jpg)

...wired it to a [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html)...

![Wiring](/{{ site.github.repository_name }}/pictures/TypeMatrix/Wiring.jpg)

...wired all the electronics, including a shiny OLED screen...

![Electronics](/{{ site.github.repository_name }}/pictures/TypeMatrix/Electronics.jpg)

...wrote a (very shitty) [firmware](https://github.com/fornellas/TypeMatrix2030), and got to the final result:

![Top](/{{ site.github.repository_name }}/pictures/TypeMatrix/Top.jpg)
![Screen](/{{ site.github.repository_name }}/pictures/TypeMatrix/Screen.jpg)

## Going further

I kept using this hacked TypeMatrix for years, but I was always envy of things like [Ergodox](https://www.ergodox.io/) (or its [commercial version](https://www.ergodox.io/)) and [Truly Ergonomic](https://www.trulyergonomic.com/). All those guys keep the vertically aligned keys, but brings the angled split layout and curved keys at your fingers. Those things attracted me very much, but I was not willing to give up the TypeMatrix layout, that I grew so fond of over the years.

In 2016, myself and a friend (thanks Ronaldo!) sketched this design over beers:

![Draft](/{{ site.github.repository_name }}/pictures/Draft/Draft.jpg)

It pretty much keeps TypeMatrix spirit, but gives the two features I was missing.

It was pretty close, but printing a thing this wide would be a challenge (would have to break into 3 parts) and its mechanical strength would be questionable. Also, I reached the conclusion that fixing the angle between the parts would be a bad idea, since it would not be adjustable. On top of that, I sketched this on... [SketchUp](https://www.sketchup.com/). It is great for achitecture, but terrible for parts design (non parametric and very imprecise).

## Going 3D!

By 2017, 3D printers finally became accessible and could deliver decent quality. I also moved from Brazil to Ireland, meaning buying a printer would just be just expensive, instead of having to sell your liver for one. I got myself an [Original Prusa i3 MK2](https://www.prusa3d.com/), which is highly rated by pretty much everyone to deliver prints comparable to printers 3x more expensive. Finally, unblocked.

My original idea was to go for [Cherry ML](http://cherryamericas.com/product/ml-series/) switches, so I could keep a low profile, and avoid those high [Cherry MX](http://cherryamericas.com/product/mx-series-2/) keyboards.

After waiting for months for RS Online to get me Cherry ML switches, I gave up. Cherry ML are also not supposed to be used without a PCB, which is something I'd like to avoid doing (cost and effort), I was not even sure if I could fit them into 3D printed sockets. I decided to go for Cherry MX Brown (lightweight 45cN).

The CAD design of the keyboard took one order of magnitude more effort than what I was expecting, but the result was awesome:

![Top](/{{ site.github.repository_name }}/rendered/Top.png)
![Back](/{{ site.github.repository_name }}/rendered/Back.png)
![Inside](/{{ site.github.repository_name }}/rendered/Inside.png)

After many many hours of 3D printing the parts and soldering everything:

![Inside Left](/{{ site.github.repository_name }}/pictures/InsideLeft.jpg)
![Inside Right](/{{ site.github.repository_name }}/pictures/InsideRight.jpg)

Wrote a [decent firmware](https://github.com/fornellas/3d_printed_keyboard) (based on my previous attempt) and... the final result:

![Top View](/{{ site.github.repository_name }}/pictures/Top.jpeg)

# Hardware

- [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html) (AT90USB1286)
- 1.3'' SPI Serial 128X64 SH1106 OLED Display
- [M2X6L Screws](https://www.ebay.com/itm/12x-M2X6mm-M2X6L-PM2X6-0-Black-Machine-Screws-Laptop-Screw-m2x6-Scrauben-Vis/301430848847?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649)
- [TRRS 3.5mm Audio breakout](https://www.sparkfun.com/products/11570) (you can find "generic" ones cheaper on eBay / Amazon).
- [TRRS 3.5mm Audio Cable](https://www.amazon.co.uk/gp/product/B01HPPO814/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1)
- [Cherry MX Brown Keyswitch - MX1A-G1NN](http://www.wasdkeyboards.com/index.php/cherry-mx-brown-keyswitch-mx1a-g1nn-tactile-bump.html)
- 1N4148 Diodes
- MCP23017 I/O Expander.

# Firmware

- Based on the [LUFA](http://www.fourwalledcubicle.com/LUFA.php) USB library.
- [u8glib](https://github.com/olikraus/u8glib) to drive the display.
- Key press counter.
- USB Remote wake up support.
- Full featured display:
  - "LED" for Num Lock, Caps Lock and Scroll Lock.
  - Hardware Keypad.
  - Hardware Fn key.
  - Computer and Keyboard layout configuration (QWERTY, Dvorak).
  - Screensaver to avoid OLED burn out.
  - Boot up splash screen.
  - USB communication status.
- Hardware layout mapping:
  - Computer QWERTY, keyboard QWERTY.
  - Computer QWERTY, keyboard Dvoark.
  - Computer Dvoark, keyboard Dvoark.
  - Computer Dvoark, keyboard QWERTY.
  - For keyboard Dvorak layouts, Fn will temporarily switch back to QWERTY (easy access to usual keyboard shortcuts).
  - Hardware keypad.
- Key functions:
  - Regular key press.
    - Support for non standard USB HID use pages key codes (useful for shortcuts like "browser").
  - Sequence of key presses.
  - Ignore key.


# 3D Printable STL Files

The source for all 3D models used in this project can be fount at [OnShape](https://cad.onshape.com/documents/70ad0c4316c1f7791e16adf7/w/2614b0b88a96d33de0d37d52/e/1350c0cb06dbf70709189044). From there, STL files can be easily exported.

# Compiling

```
git clone https://github.com/fornellas/3d_printed_keyboard.git
cd 3d_printed_keyboard/
git submodule update --init --recursive
make # or SERIAL_DEBUG=1 make
```

# Loading Firmware

Press reset button on the Teensy 2.0++ board and:

```
make load
```

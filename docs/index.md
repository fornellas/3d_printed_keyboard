This is a fully 3D printed keyboard completely custom designed from the ground up by [Fabio Pugliese Ornellas](https://github.com/fornellas).

![Top View](/{{ site.github.repository_name }}/pictures/Top.jpeg)

# See it in Action

[![Display Demo](http://img.youtube.com/vi/9C59kK4L2dM/0.jpg)](http://www.youtube.com/watch?v=9C59kK4L2dM)

# Learn more

- [History](history.html)
- [3D Printable Parts](design.html)
- [Hardware](hardware.html)
- [Firmware](firmware.html)

# Features

- Proudly 100% Open Source :-D
- Design
  - Unique ergonomic design inspired by [TypeMatrix](http://typematrix.com/) and [Ergodox](https://www.ergodox.io/).
  - All 3D printable plastic parts.
  - 13 diffirent custom shaped keycaps.
  - Custom designed key stabilizers (for space, enter etc).
- Electronics
  - [Cherry MX switches](http://cherryamericas.com/product/mx-series-2/).
    - No key [ghosting](http://blog.komar.be/how-to-make-a-keyboard-the-matrix/): one diode per key.
  - 1.3" OLED screen for full-featured status report.
    - Num Lock, Caps Lock, and Scroll Lock.
    - Hardware Keypad.
    - Hardware Fn key.
    - Computer and Keyboard layout configuration (QWERTY, Dvorak).
    - Screensaver to avoid OLED burn out.
    - Boot up splash screen.
    - USB communication status.
    - Key press counter.
  - Based on [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html).
- Firmware
  - Based on the [LUFA](http://www.fourwalledcubicle.com/LUFA.php) USB library.
  - [u8glib](https://github.com/olikraus/u8glib) to drive the display.
  - USB Remote wake up support.
  - Independent keyboard and computer layout mapped by hardware:
    - Computer QWERTY, keyboard QWERTY.
    - Computer QWERTY, keyboard Dvorak.
    - Computer Dvorak, keyboard Dvorak.
    - Computer Dvorak, keyboard QWERTY.
    - For Dvorak keyboard layouts, Fn will temporarily switch back to QWERTY (easy access to usual keyboard shortcuts).
    - Hardware keypad.
  - Easy [mapping](https://github.com/fornellas/3d_printed_keyboard/blob/master/Keymap.c#L63) of key functions:
    - Regular key press.
      - Support for HID Keyboard/Keypad Page codes (eg: letters, numbers).
      - Support for HID Generic Desktop Page codes (eg: browser, shortcuts etc)
    - Sequence of key presses (eg: Alt+Tab).
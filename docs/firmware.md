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

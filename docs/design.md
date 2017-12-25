# 3D Printable Parts

## Design

Everything was designed with [OnShape](https://www.onshape.com/). It is free for OSS projects and works from the browser. I heard only good things about [Fusion 360](https://www.autodesk.com/products/fusion-360/), but no Linux support was a deal breaker.

You can browse the design [here](https://cad.onshape.com/documents/70ad0c4316c1f7791e16adf7/w/2614b0b88a96d33de0d37d52/e/1350c0cb06dbf70709189044). Some considerations:

- Given the geometry limitations of 3D printing, I broke down the frame in 2 parts, that could be easily printed upside down and then screwed in together.
- The Cherry MX frame is filled with reinforcements to keep it rigid.
- The Teensy and the OLED screen are very tightily packed, it was challenging to design, but it really payed off.
- Long keys need [stabilization](https://deskthority.net/wiki/Stabiliser). It took about a dozen prototypes to tune dimensions for the 3D printing process, but it worked very well in the end:
[![Cherry MX Stabilizer Prototype](http://img.youtube.com/vi/6WdsF6FLru8/0.jpg)](http://www.youtube.com/watch?v=6WdsF6FLru8)

Never under estimate the amount of design work! The amount of detail to things seemingly simple will surprise you often! 

## Screenshots

![Top](/{{ site.github.repository_name }}/rendered/Top.png)

![Back](/{{ site.github.repository_name }}/rendered/Back.png)

![Inside](/{{ site.github.repository_name }}/rendered/Inside.png)

## Printing the Parts

All parts were printed with a [Original Prusa i3 MK2S](https://www.prusa3d.com/) and PLA, sliced with [Slic3r Prusa Edition](https://github.com/prusa3d/Slic3r). Most parts were a breeze to print, but some gave me headaches.

First, there was a LOT of prototyping to find the precise dimensions for the keycaps connection to the Cherry MX switches. On top of finding the correct values, not precise enough first layer calibration let parts with [elephant foot](https://all3dp.com/1/common-3d-printing-problems-troubleshooting-3d-printer-issues/), which also made things harder. Second, the stabilizers (that need to grab on a paper clip). Tedious, but straightforward.

The real challenge came when printing the key caps. I probably printed around two dozen prototypes, playing with print settings, until I found the ones that got me good results:

- 0.1mm layer height and variable layer height to 0.05mm for the top part. Decent speed, decent quality.
- Moved seam to the rear, where it is not visible. Without it, seams are everywhere and look terrible on a piece so tiny.
- Played a lot with support settings, until I managed to squeeze them where they were needed (Slic3r supports are a gamble at best). I also tried building custom supports in the model itself, without luck.
- Tuned the Top/Bottom Fill Pattern to Rectilinear and changed the angle to 90. This gave the top surface a decent look.

Even though, I had a significant failure rate when printing the keycaps, due to adhesion issues. Thoroughly cleaning the print bed with isopropyl alcohol and only printing at the center part of the bed improved success rate a lot. I also set Slic3r to do sequential printing, so I would not loose a whole batch if there was a failure.

## Getting the STL Files for Printing

The source for all 3D models used in this project can be fount at [OnShape](https://cad.onshape.com/documents/70ad0c4316c1f7791e16adf7/w/2614b0b88a96d33de0d37d52/e/1350c0cb06dbf70709189044). From there, STL files can be [easily exported](https://cad.onshape.com/help/Content/exporting-files.htm).
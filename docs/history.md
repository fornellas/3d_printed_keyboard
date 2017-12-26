# History

After working for almost a decade typing behind a keyboard, around 2011 I started feeling wrist pain. Having a whole career ahead of me, I decided I had to do something to avoid [RSI](https://en.wikipedia.org/wiki/Repetitive_strain_injury). By that time, I bought myself 2 [TypeMatrix](http://typematrix.com/) keyboards and started the switch to [Dvorak](https://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard) layout. Six months in with this new setup, I was typing Dvorak 20% faster than QWERTY.

During those months, I absolutely fell in love with TypeMatrix layout:

- Vertically aligned keys are a breeze to use: no more looking down to reach ANY key.
- Compact design allows to properly center the keyboard on the desk while keeping the mouse at a comfortable distance.
- The hardware keypad means not losing the keypad.
- Home / End and Page Up/Down close to the arrow keys are very productive.
- Putting Delete, Backspace and Enter at the center means those frequent keys are pressed by the index finger from any hand, decreasing hand movement and load on the pinky finger.
- Vertically spread Shift keys are very convenient.
- Hardware implementation of Alt+Tab with a single key press is amazing.
- Hardware implementation of Ctrl+X/C/V means usual shortcuts are still at left hand with Dvorak.

This is all great, but obviously, there were caveats:

- The hardware Dvorak translation works great, but you have to manually enable it at __every__ boot.
- Although [its spec](http://typematrix.com/2030/tech-specs.php) states its actuation force is 55 g ± 10 g, my keyboards, after a few years of use, only actuate with ~74g on top of the keys. As a comparison, this is close to the heaviest Cherry MX out there (80cN).
- TypeMatrix provides [silicone skins](http://typematrix.com/skins.php), which sound great, but in significantly increase the actuation force needed, making the previous issue worse.
- It is a [membrane](https://en.wikipedia.org/wiki/Membrane_keyboard) keyboard. Although rated for [10 million strokes](http://typematrix.com/2030/tech-specs.php), I found my both keyboards failing some keys after mere thousands of key presses. I had to replace both once, and disassembly, clean, close every now and then to fix failing keys.
- The few LED status can be quite cryptic... certainly not showing everything that is there.
- No way to reprogram the layout. Living in Brazil, I'd like to add hardware Dvorak to an [ABNT2](https://en.wikipedia.org/wiki/Portuguese_keyboard_layout) layout.

## Hacking TypeMatrix keyboard

In 2012, I had a ski accident, that got me stuck in a wheelchair for a month and at home for 6 months. Having plenty of time available, I decided to fix the firmware issues. At that time, [Arduino Leonardo](https://www.arduino.cc/en/Main/arduinoBoardLeonardo) was introduced, supporting [emulating a keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/), so it was a perfect fit for doing this. I quickly assembled a prototype:

![TypeMatrix prototype](/{{ site.github.repository_name }}/pictures/TypeMatrix/Prototype.jpg)

That worked very well! Only problem: Arduino keyboard support was very limited. It wouldn't work at the BIOS and could not send any "special" keys like the usual multimedia keys. That was a deal breaker.

Going out of Arduino environment, we had the [V-USB](https://www.obdev.at/products/vusb/index.html) library, that should do the trick. Problem is, since it is a software solution, I found many reports of random incompatibilities with Linux or Mac. Not an option as well.

I finally found a library called MyUSB (renamed to [LUFA](http://www.fourwalledcubicle.com/LUFA.php) later on). This was the real deal. It had all the features needed.

Not being able to affordably buy a compatible FPC connector, I cannibalized TypeMatrix's PCB:

![Cannybalized PCB](/{{ site.github.repository_name }}/pictures/TypeMatrix/Cannibalyse.jpg)

...wired it to a [Teensy 2.0++](https://www.pjrc.com/store/teensypp.html)...

![Wiring](/{{ site.github.repository_name }}/pictures/TypeMatrix/Wiring.jpg)

...wired all the electronics, including a shiny OLED screen...

![Electronics](/{{ site.github.repository_name }}/pictures/TypeMatrix/Electronics.jpg)

...wrote a (very shitty) [firmware](https://github.com/fornellas/TypeMatrix2030) (that "just worked"), and got to the final result:

![Top](/{{ site.github.repository_name }}/pictures/TypeMatrix/Top.jpg)
![Screen](/{{ site.github.repository_name }}/pictures/TypeMatrix/Screen.jpg)

## Going further

I kept using this hacked TypeMatrix for years, but I was envy of things like [Ergodox](https://www.ergodox.io/) (or its [commercial version](https://www.ergodox.io/)) and [Truly Ergonomic](https://www.trulyergonomic.com/). All those guys keep the vertically aligned keys but bring the angled split layout and curved keys at your fingers. Those things attracted me very much, but I was not willing to give up the TypeMatrix layout, that I grew so fond of it over the years.

In 2016, myself and a friend (thanks, Ronaldo!) sketched this design over beers:

![Draft](/{{ site.github.repository_name }}/pictures/Draft/Draft.jpg)

It pretty much keeps TypeMatrix spirit but gives the two features I was missing.

It was pretty close, but printing a thing this wide would be a challenge. It is too big for a single print, meaning I'd have to print 3 separate parts and attach them together somehow. Its mechanical strength would be questionable. Also, I reached the conclusion that fixing the angle between the parts would be a bad idea since it would not be adjustable. On top of that, I sketched this on... [SketchUp](https://www.sketchup.com/). It is great for architecture, but terrible for parts design (non-parametric and very imprecise).

## Going 3D!

By 2017, 3D printers finally became accessible and could deliver decent quality. I also moved from Brazil to Ireland, meaning buying a printer would just be just expensive, instead of having to sell your liver for one. I got myself an [Original Prusa i3 MK2](https://www.prusa3d.com/), which is highly rated by pretty much everyone to deliver prints comparable to printers 3x more expensive. Finally, unblocked.

My original idea was to go for [Cherry ML](http://cherryamericas.com/product/ml-series/) switches, so I could keep a low profile, and avoid those high [Cherry MX](http://cherryamericas.com/product/mx-series-2/) keyboards. After waiting for months for RS Online to get me Cherry ML switches, I gave up. Cherry ML are also not supposed to be used without a PCB, which is something I'd like to avoid doing (cost and effort), I was not even sure if I could fit them into 3D printed sockets. I decided to go for Cherry MX Brown (lightweight 45cN).

The CAD design of the keyboard took one order of magnitude more effort than what I was expecting, but the result was awesome:

![Top](/{{ site.github.repository_name }}/rendered/Top.png)
![Back](/{{ site.github.repository_name }}/rendered/Back.png)
![Inside](/{{ site.github.repository_name }}/rendered/Inside.png)

After many many hours of 3D printing the parts and soldering everything:

![Inside Left](/{{ site.github.repository_name }}/pictures/InsideLeft.jpg)
![Inside Right](/{{ site.github.repository_name }}/pictures/InsideRight.jpg)

Finally I wrote a [decent firmware](https://github.com/fornellas/3d_printed_keyboard) (based on my previous attempt) and... the final result:

![Top View](/{{ site.github.repository_name }}/pictures/Top.jpeg)
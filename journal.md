# usbuddy

A cute usb device that plugs straight into your laptop and talks to the laptop via usb serial.
You can show any messages you want

_Total Hours: 3 + 4 + 7 = 14h_

# 27-08-2026 Night: Getting started

_Time: 3h_

## Schematic

I decided to use:

- CH552G for MCU
- Generic 0.91" OLED (SSD1305)
- A Worldsemi WS2812B-2020 Neopixel

Since the project is so simple, the schematic wasn't hard but I learnt that SCL/SDA on I2C for the
OLED requires Pull Ups, so I had added that but thanks to #electronics, I learnt that the module I
am using probably comes with the pull ups on the board, so thats nice.

Though the WS2812B-2020 has a internal filter cap, I dont exactly need a 100n cap next to it on the
VBUS line but having it is no harm so im keeping it there. I can always DNP it IRL.

## Routing

The shape was simple too, its just a long boi due to the screen, with an edge connector and on the
other side, a button and a neopixel. Also added a mounting hole to the assembly.

# 28-08-2026 Midnight: CAD and Art

_Time: 4h_

## CAD

I don't like cad, and cad doesn't like me. I tried to import the dxf from kicad but it was all in
vain. Well then I tried importing the STEP of the board into kicad and base my part after it, and it
worked!

The problem was realized a lot later when I went to remove the pcb from the part, i couldnt delete it
because my entire work was based on that... there was no way to isolate the body....

So then I did the most genius thing... I redid the CAD, this time using the same importing STEP trick
but I deleted the rest of the faces except the bottom face, and then based my 3d model based off it.

![cad model picture](./assets/cad_case.png)

## Artwork

I found some free doodles on Figma, and I combined a bunch of them into this cool mosiac thing.
I really love the sun!

![pcb art](./assets/artback.png)

Next, I imported these into KiCad using the inbuilt image converter and put it on the F.Mask layer!
Doing that allows me to expose the copper (W ENIG!) underneath and instead of white silkscreen we get
gold colored art!

![pcb art on pcb](./assets/pcb3d_B.png)

# 28-08-2026 Morning: CAD and Art

_Time: 7h_

I got an extension! yay!

## Bugs

I realised that I had wired the pins on the OLED wrong, so I just got myself a special symbol from the
internet for this) this gave me a nice footprint and symbol to work with instead of juggling conn pins on the
board. Also I modified the footprint to remove the courtyard so it wont complain in the PCB editor

For safety and reducing ringing I added a 470ohm resistor in series to the neopixel line (b/w gpio and DIN)

## Firmware

The CH552G has 1 kb of RAM, 148 bytes is used for the usb stack.

So to run a full buffered OLED, I need to have 128*32/8 = 512 bytes in memory, but I simply dont have enough
RAM on the chip. So, I am gonna use the oled in unbuffered mode, less capability but uses essentially zero bytes
of RAM. It just injects a u8x8 pixels straight into the oled.

## Finishing up

I made the cad assembly (just one part and the exported step from KiCad) and wrote a bit of journals and took a few
screenshots, DONE!

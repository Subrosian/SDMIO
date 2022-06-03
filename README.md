# Subrosian's Dance Machine IO board
Documentation and source files for a custom IO board for 4 panel dance machines. Unlike most projects in this space, this board will not integrate into existing wiring in a DDR machine. If you are building a machine from scratch or you have a machine that has been completely gutted, this project could be for you. This project involves using a Teensy 3.5 and a Pacdrive to handle button inputs and lighting outputs, with all lighting outputs being RGB light rings (WS2812) and being able to have animations instead of static info coming out of Stepmania.

## Current status

Board is delivered and populated. Next thing to do is test it in my machine.

## Hardware

* 1x Teensy 3.5 (Likely will work with newer Teensys)
* 1x Pacdrive (Screw terminals will need to be removed and pins added)
* 8x 24 LED WS2812 Light Rings (For Pad Lights)
* 4x 12 LED WS2812 Light Rings (For Spotlights)
* 6x Individual LED WS2812s (For buttons) - TODO: Find replacements as previously purchased ones don't work well.
* 2x LED WS2812 light strips (For Subs) - TODO: Find length and density I used

## Hardware Installation

See /documentation folder for hardware stuff

## Software Configuration

I'm currently using and testing against the newest version of Project Outfox but software configuration should be no different than the LumenAR boards for lighting.

In Preferences.ini, make the following changes:
* LightsDriver=PacDrive
* PacDriveLightOrdering=lumenar

## Videos

In progress video showing the new setup: https://www.youtube.com/watch?v=V2iUk6xl10c

# stepmania-teensy-v2
Documentation and Arduino code for my Stepmania Teensy project V2.

This project involves using a Teensy 3.5 and a Pacdrive to handle button inputs and lighting outputs, with all lighting outputs being RGB and being able to have animations instead of static info coming out of Stepmania. I am currently converting my system from using the SextetStream driver to using the Pacdrive driver. My goal is to have all of the lighting code being provided to the Teensy through the Pacdrive, and then all of the custom animations will be handled by the Teensy. All lighting in the cab/pads will be using individually controllable RGB LEDs.

Current status: 

-Waiting on "production" WS2812B RGB Rings and strips from AliExpress (30-45 days).

-Waiting on "test" WS2812B strip from Amazon (2 days)

-Completed testing of Pacdrive outputs to Teensy inputs and properly getting lighting code from Stepmania into the proper Arduino variables.

Next steps:

-When the "test" RGB strip comes in, I will be starting to test inputs and outputs on the teensy in the test setup.

-Rewire my DDR machine to accept the new teensy controller, removing all previous wiring harnesses due to being a completely different design.

DDR Machine pictures/video (V1 design):

Pictures: 

Album: https://imgur.com/a/bB0s9

Videos: 

Running the old V1 design: https://www.youtube.com/watch?v=dn3CJcW0r64

First Lighting Output on V2 design: https://www.youtube.com/watch?v=AclRpqruMmo
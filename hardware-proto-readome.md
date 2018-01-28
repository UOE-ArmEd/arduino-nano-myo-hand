Prototype board hardware description for reference.
================

## Power
Battery with XT60 connector attaches to the side. There is a LM317 (3 pin device with a heatsink tab) to regulate voltage down to 5V. *Do NOT play with the potentiometer - you risk frying the arduino* The 5V is distributed down the two power rails on the sides.

## Servos / PWMs
4 of the 6 PWM signals are broken out to the protoboard (pins 6, 9, 10, 11). Connect servos to the 2x6 connector. The 4 pin in the middle are the Grounds, the outside pins are the signals. Be careful how you connect the servos!

## Myo
The myo muscle sensor is attached to the breadboard, and will not be attached directly to skin. The electrodes should be connected by the black/blue/red cable to the audio jack. 

## Button
A button is connected to pin 2 which can be configured as an external interrupt. Could be useful?

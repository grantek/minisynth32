# MIDI UART USB converter

This is a cut-down version of https://github.com/gdsports/MIDIUARTUSB for the
Minisynth 32. It only supports MIDI Out from the Tx line of the Arduino to the
Minisynth 32.

Install MIDI Library and MIDIUSB libraries using the Arduino IDE library manager.

Install support for the Sparkfun Pro Micro board in the Arduino IDE by
following the instructions at
https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all

## Hardware

MIDIUARTUSB supports several boards based on the ATmega32U4, but the 3D models
for the Minisynth 32 have a spot for a Sparkfun Pro Micro board. I've tested
this with the 5v board only (clone boards are fine).

To interface with the MIDI In lines of the rear I/O PCB:

- Solder a 220 Ohm resistor to the TX0 pad and the VCC pad, each sticking
  straight up.
  - You don't need to leave any spacing between the resistors and the pads, but
    allowing enough to angle them helps with connecting the wires.
  - I haven't tested with a 3.3v Pro Micro board, but if you're using one of
    these, the MIDI specification suggests a 10 Ohm resistor on the TX0 pad,
    and a 33 Ohm resistor on the VCC pad.
- Solder a jumper wire (with a "DuPont" connector on the other end) to each of
  the resistors as per the instructions for connecting the DIN plug.
  - You can optionally add some heatshrink over the resistor-wire connection,
    but I found it wasn't needed.
- Connect the wire attached to the resistor on VCC to "Pin 4" on the rear I/O
  PCB, and the wire attached to the resistor on TX0 to "Pin 5".
- Fix the board to the base of the Minisynth 32 case with some double-sided
  tape.
- You can upload the sketch to the board before or after installing it into the
  Minisynth 32.

Once the sketch is uploaded, the board will show up as a "SparkFun Pro Micro"
when connected to USB, but this should show up as a standard MIDI device as
with any other type of cable.

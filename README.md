# Minisynth 32

A 3D-printable MIDI synthesiser inspired by the Roland MT-32 and
[clumsyMIDI](https://github.com/gmcn42/clumsyMIDI), and powered by the
[mt32-pi](https://github.com/dwhinham/mt32-pi/wiki) MT-32 emulator.

![Minisynth 32](images/ms32.jpg)

## Features

* 3D printable shell, 50% scale of the original MT-32
* GY-PCM5102 HiFi DAC board
* Front panel PCB with 2x tactile buttons and 0.91" OLED Display
* Rear I/O breakout PCB with 5.5mm power jack and pushbutton power switch
* Rotary encoder volume dial (generic 12mm shaft with no carrier board)
* MIDI Input only (due to space limitations)
* Mostly through-hole soldering, except for the two tactile buttons
* Works with the Raspberry Pi "A" or "B" variants

## Warnings

**NO WARRANTY is provided, and no guarantee that all or any of the parts will
fit together. 3D printing is time-consuming and an art at the best of times.**

However, if you're stuck or have a question, feel free to open an issue on
GitHub, and the worst you'll get is sympathy.

## News

The model pictured has 2 large, easy to print buttons. Current work in the
"10but" branch is a front face and new PCB that has 10 smaller clickable
buttons in the same physical layout as the MT-32, for a more authentic look.

Only two of the buttons are functional with mt32-pi (a new PCB will be
required if a 10-button interface for mt32-pi is developed), the remaining
buttons have tactile switches behind them that aren't wired to anything.

I haven't completely assembled one of these due to shipping delays getting a
batch of prototype PCBs, and the 3D models are still undergoing development -
the 10but branch should be considered experimental and the pieces may not
all fit together at any one commit.

## Assembly Notes

Check the [project wiki](https://github.com/grantek/minisynth32/wiki) for the
build guide with pictures, a [text-only copy](build-guide.md) is included in this repository.



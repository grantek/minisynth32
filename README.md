# Minisynth 32

**THIS PROJECT IS IN ALPHA STATE** 

I'm currently fine-tuning things, there is no guarantee that everything will
work when put together.

A 3D-printable MIDI synthesiser inspired by the Roland MT-32 and clumsyMIDI,
and powered by the mt32-pi MT-32 emulator.

## Features

* 3D printable shell, 50% scale of the original MT-32
* GY-PCM5102 HiFi DAC board
* Front panel PCB with 2x tactile buttons and 0.91" OLED Display
* Rear I/O breakout PCB with 5.5mm power jack and pushbutton power switch
* Rotary encoder volume dial (generic 12mm shaft with no carrier board)
* MIDI Input only (due to space requirements)
* Mostly through-hole soldering, except for the two tactile buttons
* Works with the Raspberry Pi "A" or "B" variants

## Assembly Notes

### The PCBs

There are 2 PCBs required, the Raspberry Pi hat that the rear connectors are
mounted onto, and a mounting board for the front panel.

The KiCad project is based on a combined board with both PCBs joined by mouse-
bites, so they can be ordered as a single panel. There are also files for the
individual front and rear boards, because it was cheaper for me to order them
this way from the PCB manufacturer I used (there was an extra fee for
"panelised" boards that was more than double the base cost of a single small
board).

Don't be scared of the SMD switches, they're huge compared to most surface
mount devices. If you're coming from clumsyMIDI and have never hand-soldered
these, the trick is to solder one leg and position the switch while the solder
is molten. Ideally use flux paste/gel, position the switch, and hold it while
adding a blob of solder.

### 3D Printing the shell

I'm using a standard hobbyist FFF printer with black PLA filament. The
face plate is kind of terrible for this kind of printing process due to the
different angles involved, but I was successful in printing it upright at a
0.2mm layer height, with the visible layer lines horizontal in the finished
part.

Specifically, use "tree" support, which builds a tower of support starting on
the build plate and reaching across to the overhanging parts. I also prefer to
increase the vertical distance between the support and the printed part to make
it easier to remove.

The shell was modeled in FreeCAD using the Part workbench, which uses simple
geometric shapes added and subtracted from each other. If you want to modify
the "MS-32" text on the face plate to something more authentic, select the
Model window, press Ctrl-F to search the tree of objects, and search for
ShapeString (the default name for a text object). In the Data window for the
selected object you should be able to change the "MS-32" to something else. The
object remains greyed-out and hidden, but the change should propagate through
to the final part.

### Assembling the rotary encoder

The rotary encoder used is a "12mm" generic device available online.
Specifically, this is **NOT** a preassembled board with 5-pin header, there's
not enough room for these, so you need to wire directly to it.

The pinout from the rear I/O board is labelled GND SW B A

* Take a 4-wire cable with DuPont female connectors, cut the connectors off one
  end, strip and tin the cut end of the wires.
* When soldering the cut ends to the rotary encoder, you can optionally use
  heatshrink to prevent the exposed legs from touching each other.
* Solder the GND wire to the middle pin of the 3-pin side, and from there
  (using another short piece of wire if necessary) connect it to one of the
  pins on the 2-pin side.
* Solder the SW wire to the other pin on the 2-pin side.
* Solder the B wire to the pin on the left of the GND pin.
* Solder the A wire to the pin on the right of the GND pin.

The 3D-printed knob for the rotary encoder can be hard to to attach firmly. I
found printing the knob in PET-G was best to get a firm fit, but PLA was
tougher, With PLA, I was able to use a hot soldering iron pressed against the
rotary encoder's shaft to soften the knob in a similar way to the knurled
screw inserts.

Make sure you have a good fit for the knob before assembling the face plate,
but leave it off when inserting the rotary encoder.

Insert the rotary encoder into the printed backplate (direction doesn't
matter), and fasten the nut that comes with the encoder onto the front of the
backplate. This is optional if the rotary encoder screws tightly into the
backplate.

### Assembling the MIDI port

This is similar to the rotary encoder, but it just requires 2 wires (with
female DuPont connectors) soldered onto the panel-mount DIN5 jack. Looking at
the face of the jack with the pins facing upwards, pin 4 is immediately to the
left of the middle pin and pin 5 is on the right.

### Assembling the shell

The 3D-printed shell is assembled using M3 screws, bolts, and nuts. The bolt
lengths don't matter, 15mm is good. The M3 screws are the short ones used in
[PC cases](https://en.wikipedia.org/wiki/Computer_case_screws#M3_screw), about
3mm in length.

* The mounting holes for the Pi, the rotary encoder, the front panel PCB, and
  the top shell use 3mm M3 knurled threaded inserts. These are pushed into the
  (slightly narrower) mounting holes of the plastic case with a hot soldering
  iron to melt them into the hole (use a similar temperature as your 3D printer
  extruder, eg. 220-250 Celsius for PLA)
  *  Be careful you don't let the soldering iron touch the other 3D-printed
     parts!
  *  It's easy with a wide conical soldering tip to push the tip of the iron
     into the insert, and hold the insert down with tweezers while you remove
     the iron tip. There is one mounting hole at the edge of the faceplate
     where that's impossible, so you need to press the edge of the iron tip
     onto the top of the insert.

### Assembling the face

* The printed face plate is assembled with the assembled front panel PCB, two
  printed buttons, the assembled rotary encoder (with printed backplate), and
  a printed knob.
* Drop the printed buttons into the button holes, then fit the front panel PCB
  so that the tactile switches fit against the buttons, and the OLED display
  is aligned with the window. Attach the PCB with an M3 screw.
* Insert the rotary encoder assembly with the longer side of the backplate to
  the right (covering the front panel PCB). Attach the backplate with M3
  screws, and fit the knob.
* Insert the face plate's tabs into the base, insert a bolt from the bottom of
  the base through each tab in the face plate and fasten with an M3 nut.

### Assembling the base

* Format and prepare your Micro SD card for mt32-pi, and insert it into the
  Raspberry Pi.
* Attach the assembled Rear I/O PCB onto the Pi's 40-pin GPIO port, facing
  outwards.
* Line up the Pi on the base with the rear panel, and screw the Pi down with M3
  "PC" screws. You can still access the SD card when the Pi is installed, but
   it's easier to do it beforehand.
* Place the wired MIDI DIN jack on the inside of the base's rear plate, and
  attach with 2 M3 bolts from the outside (M3 nuts on the inside). The DIN5
  jack is traditionally mounted with the pins facing down, and the alignment
  notch facing up. DIN5 cables have an an arrow at the alignment notch for easy
  attachment.
* Connect the DIN jack to the labelled pins on the rear PCB.
* Connect the wired rotary encoder to the `ROT_HDR` header.
* Use a row of 6 female-female jumper wires to connect the front panel's
  `R_BREAKOUT` header to the rear breakout board's `F_PANEL` header.
* Fit the top shell and fasten with an M3 screw.

  

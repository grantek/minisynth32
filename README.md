# Minisynth 32

A 3D-printable MIDI synthesiser inspired by the Roland MT-32 and
[clumsyMIDI](https://github.com/gmcn42/clumsyMIDI), and powered by the
[mt32-pi](https://github.com/dwhinham/mt32-pi/wiki) MT-32 emulator.

![Minisynth 32](images/ms32.jpg)

## Features

* 3D printable shell, 50% scale of the original MT-32
* GY-PCM5102 HiFi DAC board
* Front panel PCB with 2 functional tactile buttons and 0.91" OLED Display
* Optional 10-button fully clickable front panel (extra buttons are currently
  non-functional)
* Rear I/O breakout PCB with 5.5mm power jack and pushbutton power switch
* Rotary encoder volume dial (generic 12mm shaft with no carrier board)
* MIDI Input only (due to space limitations)
* Completly through-hole soldering, no surface mount components
* Works with the Raspberry Pi "A" or "B" variants

## Warnings

**NO WARRANTY is provided, and no guarantee that all or any of the parts will
fit together. 3D printing is time-consuming and an art at the best of times.**

However, if you're stuck or have a question, feel free to open an issue on
GitHub, and the worst you'll get is sympathy.

## Assembly Notes

Check the [project wiki](https://github.com/grantek/minisynth32/wiki) for the
build guide with pictures, a text-only copy is included below:

### MT32-pi configuration

A sample `mt32-pi.cfg` is included in this repository, the options that are
different from the default settings are:

```
# [midi]
# Disable USB input for faster boot time
usb = off

# [audio]
# Output audio to the GY-PCM5102 i2s board
output_device = i2s

# Initialise the GY-PCM5102 DAC on boot
i2c_dac_init = pcm51xx

# [control]
# Use the rotary encoder + 2 buttons control scheme
scheme = simple_encoder

# [lcd]
# Use the ssd1306 driver for the i2c OLED display
type = ssd1306_i2c

# invert the display since it's mounted upside-down in the Minisynth 32
rotation = inverted
```

* The generic 0.91" SSD1306 OLED also works with `height = 64`, and gives
  a sharper but smaller text display. The default `height = 32` is stretched
  but easier to read.
* The generic rotary encoder I used works fine with the `encoder_type = full`
  setting.
* Be sure to check the mt32-pi documentation for setting up the required MT-32
  ROMs and/or GM soundfonts, and other options you may be interested in.

### The PCBs

There are 2 PCBs required, the Raspberry Pi hat that the rear connectors are
mounted onto (the "rear I/O breakout board"), and a mounting board for the
front panel. The "front" of the rear board faces downwards, so the components
hang upside down to fit in the tight clearance of the case. The MIDI port is
panel-mounted to the case for the same reason.

The KiCad project is based on a combined board with both PCBs joined by mouse-
bites, so they can be ordered as a single panel. There are also files for the
individual front and rear boards, because it was cheaper for me to order them
this way from the PCB manufacturer I used (there was an extra fee for
"panelised" boards that was more than double the base cost of a single small
board).

PCB notes for manufacturers:

* Rear PCB only (v1.1): 31.7mm * 96mm
* Front PCB only (v2.0): 17mm * 96.2mm
* Panelised front+rear PCB: 51.3mm * 96.2mm
* Minimum hole size: 0.5mm (the standard "0.3mm" is fine to select)
* Minimum track spacing: 0.2mm (the standard "6 mils" is fine to select)
* Layers: 2
* Thickness: must be 1.6mm

The main soldering advice is to solder the DAC and OLED boards first if
possible (see below), then the generic "lowest-height components first". Make
sure to trim all legs on the underside of the rear breakout PCB, as this faces
upwards and there isn't much room to the printed case.

### Soldering the OLED board with 3D-printed shim

The OLED boards have the glass screen bonded to the PCB, sometimes with no
visible clearance and sometimes with a padded adhesive tape that makes the
module a little thicker. The front PCB sits at a fixed distance from the front
face, so the OLED board needs to be soldered with some clearance from the front
PCB. To help with this, there is a 3D-printed shim that clips on the front PCB
and helps align the OLED board.

There are 2 STL files for the shim, a thicker one for low-clearance boards and a
thinner one for boards with some padding underneath the glass screen. Ideally,
do a test fit with the OLED board by sticking it to the shim with double-sided
tape, clipping the shim onto the front PCB, and fitting the front PCB to the
3D-printed faceplate. If you need to adjust the thickness, open shim.FCStd in
FreeCAD, open the spreadsheet named "Spreadsheet", and edit the value of "shim
thickness", then export the shim model as an STL.

Once you have everything aligned, you can solder the pins into the front panel
PCB.

### Soldering the DAC module

**IMPORTANT:** As per the clumsyMIDI documentation, make sure that all 4 solder
pad "jumpers" on the GY-PCM5102 board are set BEFORE soldering it to the board.
To solder the GY-PCM5102 DAC board:

- Check the soldered pad headers on the rear of the GY-PCM5102 a final time.
- Solder the board flat to the rear breakout board in the same way as the OLED
board. Alignment is less critical here, I used a 2-layer paper shim to help.
- Solder the 6 pins on the short edge of the board. You don't need to solder
anything to the row of 9 pins on the long edge, there is no connection to
anything on the rear breakout board.

### Soldering the rear panel pin headers

There are 3 pin headers on the rear breakout board that require a 90-degree
angled pin header:

- `F_PANEL`: connects to the front panel PCB, 6 pins.
- `ROT_HDR`: connects to the rotary encoder, 4 pins.
- `MIDI_IN:`: connects to the panel-mount DIN5 jack for MIDI input.

Check the clearance of your pin headers against the Raspberry Pi - if you have
tall pin headers, push them down through the plastic collar so that they just
have room for the jumper wires to connect.

### 3D Printing the shell

I'm using a standard hobbyist FFF printer with black PLA filament. The
face plate is kind of terrible for this kind of printing process due to the
different angles involved, but I was successful in printing it upright at a
0.2mm layer height, with the visible layer lines horizontal in the finished
part.

Specifically, use "tree" support for the face, which builds a tower of support
starting on the build plate and reaching across to the overhanging parts. I also
prefer to increase the vertical distance between the support and the printed
part to make it easier to remove (0.4mm gap for a 0.2mm layer height). The
supported parts of the model may end up messy on their bottom layer, but this
is okay for the inside of the faceplate.

The shell was modeled in FreeCAD using the Part workbench, which uses simple
geometric shapes added and subtracted from each other. If you want to modify
the "MS-32" text on the face plate to something more authentic, select the
Model window, press Ctrl-F to search the tree of objects, and search for
ShapeString (the default name for a text object). In the Data window for the
selected object you should be able to change the "MS-32" to something else, and
press Enter. The object remains greyed-out and hidden, but the change should
propagate through to the final part.

### Assembling the rotary encoder

The rotary encoder used is a "12mm" generic device available online.
Specifically, this is **NOT** a preassembled board with 5-pin header, there's
not enough room for these, so you need to wire directly to the bare legs.

First, bend the mounting tabs on the encoder in against its base.

The pinout from the rear I/O board is labelled `GND` `SW` `B` `A`

* Take a 4-wire jumper cable (ie. with "DuPont" 2.54mm pitch female
  connectors), cut the connectors off one end, strip and tin the cut end of the
  wires.
* When soldering the cut ends to the rotary encoder, you can optionally use
  heatshrink to prevent the exposed legs from touching each other.
* Solder the `GND` wire to the middle pin of the 3-pin side, and from there
  (using another short piece of wire) connect it to one of the
  pins on the 2-pin side.
* Solder the `SW` wire to the other pin on the 2-pin side.
* Solder the `B` wire to the pin on the left of the GND pin.
* Solder the `A` wire to the pin on the right of the GND pin.
* If you get the `B` and `A` pins wrong, you can swap the jumper wires on the
  pin header of the rear breakout board.

The 3D-printed knob for the rotary encoder can be hard to to attach firmly. I
found printing the knob in PET-G was best to get a firm fit, but PLA was
less flexible, If the knob won't attach, you can carefully use a clean hot
soldering iron pressed against the rotary encoder's shaft to soften the plastic
in a similar way to the knurled screw inserts. If it's too loose, use some putty
adhesive to hold it in place (this is much easier). There are a few STLs of
different shaft widths, but the FreeCAD model is also easy to modify.

Make sure you have a good fit for the knob before assembling the face plate,
but leave it off when inserting the rotary encoder.

Put the hexagonal nut from the rotary encoder into the hexagonal relief in the
front of the faceplate, then screw the encoder shaft in throught the nut.
There's a cutout in the faceplate to allow the encoder to spin, but pliers are
helpful to rotate it carefully.

### Assembling the MIDI port

This is similar to the rotary encoder, but it just requires 2 jumper wires
soldered onto the panel-mount DIN5 jack. Looking at the face of the jack with
the pins facing upwards, pin 4 is immediately to the left of the middle pin and
pin 5 is on the right. Heatshrink isn't needed for insulation because the pins
are so far apart, but I used heatshrink to add some mechanical stability to the
connection.

### Assembling the shell

The Raspberry Pi is mounted using M2.5 bolts and nuts. M3 bolts _may_ work
(older versions of the base used M3 screws into threaded inserts), but require
widening the hole slightly, which carries some risk of damaging the Pi.

The faceplate and MIDI port are attached using M3 bolts and nuts. The bolt
lengths don't matter too much, 8-15mm is good. 8mm M2.5 bolts and nuts will also
work here if you're purchasing one type of bolt.

The front PCB, rotary encoder, and top shell are attached using M3\*4mm screws.
M3 PC Case Screws may work here, but if they're any longer than 4mm, it's
possible to push into the plastic resulting in a bulge on the front.

The mounting holes for the front panel PCB, and the top shell use 3mm M3
knurled threaded inserts. These are pushed into the (slightly narrower)
mounting holes of the plastic case with a hot soldering iron to melt them into
the hole (use a similar temperature as your 3D printer extruder, eg. 220-250
Celsius for PLA).

  *  Be careful you don't let the soldering iron touch the other 3D-printed
     parts!
  *  It's easy with a wide conical soldering tip to push the tip of the iron
     into the insert, and hold the insert down with tweezers while you remove
     the iron tip.

### Assembling the face

* Melt the first threaded insert into the faceplate as described above.
* Melt the other threaded insert into the mounting hole on the top shell while
  you're at it.
* The printed face plate is assembled with the assembled front panel PCB, two
  printed buttons, and the printed knob on the rotary encoder.
* Drop the printed buttons into the button holes, then fit the front panel PCB
  so that the tactile switches fit against the buttons, and the OLED display
  is aligned with the window. Attach the PCB with an M3 screw.

### Assembling the base and top

* Format and prepare your Micro SD card for mt32-pi, and insert it into the
  Raspberry Pi. You can still access the SD card when the Pi is installed, but
  it's easier to do it beforehand.
* Attach the assembled Rear I/O PCB onto the Pi's 40-pin GPIO port, facing
  outwards.
* Line up the Pi on the base with the rear panel, and insert 4 M2.5 bolts
  through the base and mounting holes on the Pi. Secure with 4 M2.5 nuts, but
  do not over-tighten these as excess pressure can damage the Pi.
* Place the wired MIDI DIN jack on the **inside** of the base's rear plate, and
  attach with 2 M3 bolts from the outside (M3 nuts on the inside). The DIN5
  jack is traditionally mounted with the pins facing down, and the alignment
  notch facing up. DIN5 cables have an an arrow at the alignment notch for easy
  attachment.
* Connect the DIN jack to the labelled pins on the rear PCB `MIDI_IN` header.
  With the half-circle of DIN pins facing downwards, Pin 4 is left of the
  centre solder tab, and when connected to the rear PCB, the jumper wires
  won't cross.
* Connect the wired rotary encoder to the `ROT_HDR` header.
* Use a row of 6 female-female jumper wires to connect the front panel's
  `R_BREAKOUT` header to the rear breakout board's `F_PANEL` header.
* Insert the face plate's tabs into the base, insert a bolt from the bottom of
  the base through each tab in the face plate and fasten with an M3 nut.
* Fit the top shell and fasten with an M3 screw.
* Stick 4 rubber feet (or felt pads, etc.) to the base to give clearance for the
  bolt heads.


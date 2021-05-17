# Minisynth 32

A 3D-printable MIDI synthesiser inspired by the Roland MT-32 and
[clumsyMIDI](https://github.com/gmcn42/clumsyMIDI), and powered by the
[mt32-pi](https://github.com/dwhinham/mt32-pi/wiki) MT-32 emulator.

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

## Assembly Notes

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

* Rear PCB only: 31.7mm * 96mm
* Front PCB only: 15.2mm * 89.9mm
* Panelised front+rear PCB: 49.5mm * 96mm
* Minimum hole size: 0.5mm (the standard "0.3mm" is fine to select)
* Minimum track spacing: 0.2mm (the standard "6 mils" is fine to select)
* Layers: 2
* Thickness: must be 1.6mm

Don't be scared of the SMD switches, they're huge compared to most surface
mount devices. If you're coming from clumsyMIDI and have never hand-soldered
these, the trick is to solder one leg and position the switch while the solder
is molten. Ideally use flux paste/gel, position the switch, and hold it while
adding a blob of solder.

Apart from that, the main soldering advice is the generic "lowest-height
components first". Make sure to trim all legs on the underside of the rear
breakout PCB, as this faces upwards and there isn't much room to the printed
case.

### Soldering the OLED and GY-PCM5102 board

**IMPORTANT:** As per the clumsyMIDI documentation, make sure that all 4 solder
pad "jumpers" on the GY-PCM5102 board are set BEFORE soldering it to the board.

**IMPORTANT:** The OLED board MUST be soldered _flat_ against the front panel
PCB. There is no clearance for the plastic collar of a pin header.

To solder the OLED board to the front panel:

- Take a 4-pin header, and solder it "normally" on the rear side of the board
(ie. plastic collar on the rear of the board, short ends of the pins in the
OLED board's holes.
- Trim the soldered ends of the pins off with sidecutters if they stick up far
enough to do so. Alternatively, don't insert the pins that far in before
soldering.
- Slide the black plastic collar off the pin header, using pliers or by
levering something underneath it. If necessary, you can crush the collar with
pliers and remove the pieces.
- Insert the long ends of the pins without the collar through the Minisynth 32
front panel PCB, so that the OLED board is sitting on its silk-screened
footprint. The OLED board sits partially on the front panel PCB, but is both
longer and wider at one edge that the front panel PCB.
- The OLED board will rock on the largest of its SMD components pressing
against the front panel board. Take a piece of printer paper, fold it in half
twice (so you have 4 layers), and use that as a shim between the two boards to
stabilise the OLED board horizontal to the front panel PCB.
- Once stabilised, solder the pins in place on the front panel PCB, and trim
the ends.

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
part to make it easier to remove (0.4mm gap for a 0.2mm layer height).

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
not enough room for these, so you need to wire directly to the bare legs.

The pinout from the rear I/O board is labelled `GND` `SW` `B` `A`

* Take a 4-wire jumper cable (ie. with "DuPont" 2.54mm pitch female
  connectors), cut the connectors off one end, strip and tin the cut end of the
  wires.
* When soldering the cut ends to the rotary encoder, you can optionally use
  heatshrink to prevent the exposed legs from touching each other.
* Solder the `GND` wire to the middle pin of the 3-pin side, and from there
  (using another short piece of wire if necessary) connect it to one of the
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

Insert the rotary encoder into the printed backplate (direction doesn't
matter), and fasten the nut that comes with the encoder onto the front of the
backplate. This is optional if the rotary encoder screws tightly into the
backplate.

### Assembling the MIDI port

This is similar to the rotary encoder, but it just requires 2 jumper wires
soldered onto the panel-mount DIN5 jack. Looking at the face of the jack with
the pins facing upwards, pin 4 is immediately to the left of the middle pin and
pin 5 is on the right.

### Assembling the shell

The 3D-printed shell is assembled using M3 screws, bolts, and nuts. The bolt
lengths don't matter, 15mm is good. The M3 screws are the short ones used in
[PC cases](https://en.wikipedia.org/wiki/Computer_case_screws#M3_screw), about
3-4mm in length.

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

* Melt the 3 threaded inserts into the faceplate as described above.
* The printed face plate is assembled with the assembled front panel PCB, two
  printed buttons, the assembled rotary encoder (with printed backplate), and
  a printed knob.
* Drop the printed buttons into the button holes, then fit the front panel PCB
  so that the tactile switches fit against the buttons, and the OLED display
  is aligned with the window. Attach the PCB with an M3 screw.
* Insert the rotary encoder assembly with the longer side of the backplate to
  the right (covering the front panel PCB). Attach the backplate with M3
  screws, and fit the knob.

### Assembling the base and top

* Melt the 4 threaded inserts into the base, and 1 into the top shell, as
  described above.
* Format and prepare your Micro SD card for mt32-pi, and insert it into the
  Raspberry Pi.
* Attach the assembled Rear I/O PCB onto the Pi's 40-pin GPIO port, facing
  outwards.
* Line up the Pi on the base with the rear panel, and screw the Pi down with M3
  "PC" screws. You can still access the SD card when the Pi is installed, but
  it's easier to do it beforehand.
* Place the wired MIDI DIN jack on the **inside** of the base's rear plate, and
  attach with 2 M3 bolts from the outside (M3 nuts on the inside). The DIN5
  jack is traditionally mounted with the pins facing down, and the alignment
  notch facing up. DIN5 cables have an an arrow at the alignment notch for easy
  attachment.
* Connect the DIN jack to the labelled pins on the rear PCB `MIDI_IN` header.
* Connect the wired rotary encoder to the `ROT_HDR` header.
* Use a row of 6 female-female jumper wires to connect the front panel's
  `R_BREAKOUT` header to the rear breakout board's `F_PANEL` header.
* Insert the face plate's tabs into the base, insert a bolt from the bottom of
  the base through each tab in the face plate and fasten with an M3 nut.
* Fit the top shell and fasten with an M3 screw.
* Stick 4 rubber feet to the base to give clearance for the bolt heads



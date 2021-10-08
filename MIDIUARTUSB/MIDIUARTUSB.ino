/*
  MIT License

  Copyright (c) 2018 gdsports625@gmail.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
   MIDIUARTUSB converter for 32u4 such as Leonardo, Pro Micro, Itsy Bitsy.

   Original sketch: https://github.com/gdsports/MIDIUARTUSB

   Modified for Minisynth32 to only include "MIDI out" functionality to the
   synth unit.

   Intended for Ardiono Pro Micro, but see the main project for notes on other
   boards this may work with.
*/

#include <MIDI.h>
#include <MIDIUSB.h>

// 1 turns on debug, 0 off
#define DBGSERIAL if (0) SERIAL_PORT_MONITOR
#ifdef USBCON
#define MIDI_SERIAL_PORT Serial1
#else
#define MIDI_SERIAL_PORT Serial
#endif

struct MySettings : public midi::DefaultSettings
{
  static const bool Use1ByteParsing = false;
  static const unsigned SysExMaxSize = 1026; // Accept SysEx messages up to 1024 bytes long.
  static const long BaudRate = 31250;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, MIDI_SERIAL_PORT, MIDIUART, MySettings);

inline uint8_t writeUARTwait(uint8_t *p, uint16_t size)
{
  // Apparently, not needed. write blocks, if needed
  //  while (MIDI_SERIAL_PORT.availableForWrite() < size) {
  //    delay(1);
  //  }
  return MIDI_SERIAL_PORT.write(p, size);
}

uint16_t sysexSize = 0;

void sysex_end(uint8_t i)
{
  sysexSize += i;
  sysexSize = 0;
}

const uint8_t MIDI_passthru_pin=2;
bool MIDI_passthru;

void setup() {
  // Turn off built-in RED LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  DBGSERIAL.begin(115200);

  // Pin 0 LOW selects MIDI pass through on
  pinMode(MIDI_passthru_pin, INPUT_PULLUP);
  MIDI_passthru = (digitalRead(MIDI_passthru_pin) == LOW);

  MIDIUART.begin(MIDI_CHANNEL_OMNI);
  if (MIDI_passthru) {
    DBGSERIAL.println("MIDI thru on");
  }
  else {
    DBGSERIAL.println("MIDI thru off");
    MIDIUART.turnThruOff();
  }
}

void loop()
{
  /* MIDI USB -> MIDI UART */
  midiEventPacket_t rx = MidiUSB.read();
  if (rx.header != 0) {
    switch (rx.header & 0x0F) {
      case 0x00:  // Misc. Reserved for future extensions.
        break;
      case 0x01:  // Cable events. Reserved for future expansion.
        break;
      case 0x02:  // Two-byte System Common messages
      case 0x0C:  // Program Change
      case 0x0D:  // Channel Pressure
        writeUARTwait(&rx.byte1, 2);
        break;
      case 0x03:  // Three-byte System Common messages
      case 0x08:  // Note-off
      case 0x09:  // Note-on
      case 0x0A:  // Poly-KeyPress
      case 0x0B:  // Control Change
      case 0x0E:  // PitchBend Change
        writeUARTwait(&rx.byte1, 3);
        break;
      case 0x04:  // SysEx starts or continues
        sysexSize += 3;
        writeUARTwait(&rx.byte1, 3);
        break;
      case 0x05:  // Single-byte System Common Message or SysEx ends with the following single byte
        sysex_end(1);
        writeUARTwait(&rx.byte1, 1);
        break;
      case 0x06:  // SysEx ends with the following two bytes
        sysex_end(2);
        writeUARTwait(&rx.byte1, 2);
        break;
      case 0x07:  // SysEx ends with the following three bytes
        sysex_end(3);
        writeUARTwait(&rx.byte1, 3);
        break;
      case 0x0F:  // Single Byte, TuneRequest, Clock, Start, Continue, Stop, etc.
        writeUARTwait(&rx.byte1, 1);
        break;
    }
  }
}

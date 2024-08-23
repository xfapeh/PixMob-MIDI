# PixMob-MIDI
Controlling PixMob wristbands with MIDI via Arduino

Parts used: 
- PixMob Wristband (Aurora v1.7) or anything similar
- KY-005 IR LED (Arduino)
- MIDI Keyboard/Controller

HowTo:
- Connect the IR LED to 5V power and an output PIN on any Arduino board
- compile and upload the sketch
- send MIDI data to the serial port of the Arduino
  (this depends on your OS. On linux I use ttymidi (https://github.com/cjbarnes18/ttymidi/tree/master/src)
   ttymidi -s /dev/ttyACM0 -n ArduinoUno -b 115200
   and then send MIDI data via jack (or ALSAmidi) to the port "ArduinoUno", you can use Catia or qjackctl for routing.
   On Windows there exists something similar called "Hairless MIDI Bridge", but I don´t use it)
- future plan: integrate physical MIDI jack via Arduino

dependencies:
- IRremote Arduino library
- MIDI.h Arduino library

Big Thanks to:
https://github.com/danielweidman/pixmob-ir-reverse-engineering
https://github.com/danielweidman/flipper-pixmob-ir-codes

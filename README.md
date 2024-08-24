# PixMob-MIDI
Controlling PixMob wristbands with MIDI via Arduino

It´s really fun playing piano while your hands light up ...

![PixMob-Keyboard](https://github.com/user-attachments/assets/09833d44-2c98-42af-97e0-446be543f324)

![PixMob MIDI Piano Test](https://www.youtube.com/watch?v=xtadfFcEgX8)

[![PixMob MIDI Piano Test](https://img.youtube.com/vi/xtadfFcEgX8)/0.jpg)](https://www.youtube.com/watch?v=xtadfFcEgX8))


Parts used: 
- PixMob Wristband (Aurora v1.7) or anything similar
- Arduino Uno (or any compatible)
- KY-005 IR LED (Arduino)
- MIDI Keyboard/Controller

HowTo:
- connect the IR LED to 5V power and an output PIN on any Arduino board
- compile and upload the sketch
- send MIDI data to the serial port of the Arduino
  (this depends on your OS. On linux I use ttymidi (https://github.com/cjbarnes18/ttymidi/tree/master/src)
  
   ttymidi -s /dev/ttyACM0 -n ArduinoUno -b 115200
  
   and then send MIDI data via jack (or ALSAmidi) to the port "ArduinoUno", you can use Catia or qjackctl for routing.
  
   On Windows there exists something similar called "Hairless MIDI Bridge", but I don´t use it)
- future plans: integrate physical MIDI jack via Arduino

![PixMob-Arduino-Demo](https://github.com/user-attachments/assets/6965f6d1-291c-4fae-aff2-c56a81fe60cd)
![PixMob-Catia](https://github.com/user-attachments/assets/b028e0e0-2baf-41ba-899d-388ce65e7c49)

dependencies:
- IRremote Arduino library
- MIDI.h Arduino library

Big Thanks to:

https://github.com/danielweidman/pixmob-ir-reverse-engineering

https://github.com/danielweidman/flipper-pixmob-ir-codes

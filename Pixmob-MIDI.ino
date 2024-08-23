#include <Arduino.h>
#include <IRremote.hpp>
#include <MIDI.h>

const int IRLedPin  = 5;  // led GPIO pin
bool      sustain   = 0;
bool      note[127] = {};
uint8_t   hue       = 0;

uint16_t RED[21] = {1400, 1400, 700, 700, 700, 1400, 700, 2800, 700, 2100, 1400, 700, 700, 700, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t GRN[21] = {1400, 1400, 700, 700, 700, 700, 1400, 2800, 700, 1400, 700, 1400, 700, 1400, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t LIGHT_GRN[25] = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 1400, 700, 1400, 700, 1400, 700, 700, 700, 1400, 700, 2100, 700, 1400, 700, 1400, 700};
uint16_t YELGRN[23] = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 2100, 700, 700, 700, 1400, 700, 1400, 700, 700, 700, 2100, 1400, 2800, 700};
uint16_t BLUE[27] = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 1400, 1400, 700, 700, 1400, 700, 700, 700, 700, 700, 700, 700, 2100, 700};
uint16_t LIGHT_BLUE[27] = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 1400, 700, 700, 700, 700, 700, 700, 700, 700, 1400, 1400, 700, 2100, 700};
uint16_t MAG[23] = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 2100, 1400, 2100, 700, 700, 700, 700, 1400, 2100, 700, 700, 700, 2100, 700};
uint16_t YEL[21] = {1400, 1400, 700, 700, 700, 700, 1400, 2800, 700, 2100, 700, 700, 700, 1400, 700, 1400, 1400, 2800, 1400, 2800, 700};
uint16_t PINK[23] = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 2100, 700, 700, 700, 2100, 700};
uint16_t YELOR_1[23] = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 1400, 700, 700, 700, 2100, 700, 700, 700, 700, 1400, 2100, 1400, 2800, 700};
uint16_t WHITISH[23] = {700, 700, 700, 2100, 1400, 700, 700, 2800, 700, 1400, 700, 700, 700, 2800, 1400, 1400, 700, 2100, 700, 1400, 700, 1400, 700};
uint16_t TURQ[23] = {700, 700, 700, 700, 1400, 1400, 1400, 2800, 700, 1400, 700, 700, 1400, 1400, 700, 1400, 1400, 2800, 700, 700, 700, 2100, 700};

uint16_t* colors[] = {RED, GRN, LIGHT_GRN, YELGRN, BLUE, LIGHT_BLUE, MAG, YEL, PINK, YELOR_1, WHITISH, TURQ }; 

int colorLengths[] = {21, 21, 25, 23, 27, 27, 23, 21, 23, 23, 23, 23 };

int currentColorIndex = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.setHandleNoteOn(handleNoteOn16);
  MIDI.setHandleNoteOff(handleNoteOff16);
  MIDI.setHandleControlChange(handleControlChange16);
  MIDI.begin(0);
  
  IrSender.begin(IRLedPin);
  IrSender.enableIROut(38); // 38 kHz

}

void loop() {
  MIDI.read();
  turnLEDon();
  
}

void turnLEDon() {
      if(note[hue]==true){
        currentColorIndex=hue%12;
        IrSender.sendRaw(colors[currentColorIndex], colorLengths[currentColorIndex], 38);
        delay(5);
      }
}


void handleNoteOn16(byte channel, byte pitch, byte velocity)
{
      hue=pitch;
      note[pitch]=true;
}

void handleNoteOff16(byte channel, byte pitch, byte velocity)
{
      hue=pitch;
      //currentColorIndex=pitch%12;
      if(sustain==0) {
        // switch everything off, despite pressed keys ... todo
      }  
      note[pitch]=false;
}


void handleControlChange16(byte channel, byte number, byte value)
{
  if(number==64 && value==127) {
      // if notes are still playing, but no longer pressed, keep them on ? ... todo
      sustain=1;
  }
  if(number==64 && value==0) {
      for(int i=21; i<=108; i++) {    
        if(note[i]==false){
          // switch all notes, which are no longer pressed, off, when sustain pedal is released ... todo
        }
      }
    sustain=0;
  }
}

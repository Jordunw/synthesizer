#pragma once

#include "midi.h"

#define MAX_DEBOUNCE 3

class Pad{
public:
  Pad(uint8_t row, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) :
      row{row}, column{c1, c2, c3, c4}{}  

  private:
    unsigned int row;
    unsigned int column[4];
    int debounceCount[4] = {0};
    unsigned int current = 0;
    byte note[4];

  public:
    void init(){
      for(int i = 0; i < 4; i++){
        pinMode(column[i], OUTPUT);
        digitalWrite(column[i], HIGH);
      }
      pinMode(row, INPUT_PULLUP);
    }

    void scan(bool chord){
      digitalWrite(column[current], LOW);
 
      uint8_t val = digitalRead(row);
      if(val == LOW){
        if (debounceCount[current] < MAX_DEBOUNCE)
        {
          debounceCount[current]++;
          if (debounceCount[current] == MAX_DEBOUNCE)
          {
              sendMidiMessage(midi::command::note_on + 1, note[current], VELOCITY);
              if(chord){
                sendMidiMessage(midi::command::note_on + 1, note[current] + 4, VELOCITY);
                sendMidiMessage(midi::command::note_on + 1, note[current] + 7, VELOCITY);
              }
          }
        }
      }else{
        if(debounceCount[current] > 0){
          debounceCount[current]--;
          if(debounceCount[current] == 0){
            sendMidiMessage(midi::command::note_on + 1, note[current], 0);
            if(chord){
                sendMidiMessage(midi::command::note_on + 1, note[current] + 4, 0);
                sendMidiMessage(midi::command::note_on + 1, note[current] + 7, 0);
              }
          }
        }
      }
      delay(1);
      digitalWrite(column[current], HIGH);
     
      if(++current > 3){
        current = 0;
      }
    }

    void setNotes(byte n1, byte n2, byte n3, byte n4){note[0] = n1; note[1] = n2; note[2] = n3; note[3] = n4;}
};

class Pot{
  public:
    Pot(unsigned int pin, byte message) : pin{pin}, message{message}{}
 
  private:
    uint8_t pin, lastVal = 0;
    byte message;

  public:
    void scan(){
      uint8_t val = floor(analogRead(pin) >> 3); // convert the 0-1023 value to a number between 0-127

      if(val != lastVal){
        sendMidiMessage(midi::command::cc, message, val);
      }
      lastVal = val;
    }

    void changeMessage(byte message) {this->message = message;}
};

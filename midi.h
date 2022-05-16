#pragma once

#include "scales.h"

#define VELOCITY 100

void sendMidiMessage(byte command, byte data) {
  Serial.write(command);
  Serial.write(data);
}

void sendMidiMessage(byte command, byte data1, byte data2){
    Serial.write(command);
    Serial.write(data1);
    Serial.write(data2);
}

// for sending cc
void sendMidiMessage(byte command, byte msg, byte data, byte channel){
  Serial.write(command);
  Serial.write(msg);
  Serial.write(data);
  Serial.write(channel);
}

namespace midi
{
    enum command : byte
    {
        // can also use vel = 0 for note off
        note_off = 128,
        note_on = 144,
        aftertouch = 160,
        cc = 176,
        patch_change = 192,
        channel_pressure = 208,
        pitch_bend = 224,
        non_musical = 240
    }command;

    namespace data 
    {
      // doesnt even matter because sonic pi doesnt actually read any of the cc data, i have to manually manage it
        enum cc : byte 
        {
            bank = 0,
            modWheel = 1,
            footPedal = 4,
            dataEntry = 6,
            volume = 7,
            panPos = 10,
            expression = 11,
            sustainPedal = 64, 
            resonance = 71,
            freqCutoff = 74,
            reverb = 91,
            tremolo = 92,
            chorus = 93,
            detune = 94,
            phaser = 95
        }cc;
    }

class Message {
public:
    Message(byte command, byte* data1) : command{command}, data1{data1}, data2{new byte}{}
    ~Message(){
        if(data1 != nullptr)
            delete data1; 
        if(data2 != nullptr)
            delete data2;
        }
private:
    byte command;
    byte* data1;
    byte* data2;

public:
};

} // namespace midi

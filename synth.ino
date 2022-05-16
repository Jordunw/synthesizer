#include "components.h"
#include <stdarg.h>

typedef va_list __gnuc_va_list;

Pad pads[] = {{13, 8, 6, 9, 5}, {7, 12, 3, 4, 2}};
Pot pots[] = {{A0, 0}, {A1, 1}, {A2, 2}, {A3, 3}, {A4, 4}, {A5, 5}}; // cc messages dont matter unless im using something other than sonic pi
// ADD PWM POTS

scales::Scale* currentScale = &scales::C_maj;

void setScale(byte octave)
{
  byte notes[8];
  for (int i = 0; i < 8; i++) {
    notes[i] = scales::toOctave(*(currentScale->getNotes() + i), octave);
  }
  pads[0].setNotes(notes[0], notes[1], notes[4], notes[5]);
  pads[1].setNotes(notes[2], notes[3], notes[6], notes[7]);
}

bool compScale(String compStr, ...) {
  va_list list;
  va_start(list, compStr);
  while (true) {
    String arg = va_arg(list, char*);
    if (arg == "end") break;
    if (compStr == arg) {
      va_end(list);
      Serial.println("argument matched " + arg);
      return true;
    }
  }
  va_end(list);
  return false;
}

bool setScaleFromString(String scale, byte octave) {
#define comp(...) if(compScale(scale, __VA_ARGS__))
  scale.toLowerCase();
  Serial.println("Scale: " + scale);

  comp("c_maj", "c_major", "end")
  currentScale = &scales::C_maj;
  else comp("g_maj", "g_major", "end")
    currentScale = &scales::G_maj;
  else comp("d_maj", "d_major", "end")
    currentScale = &scales::D_maj;
  else comp("a_maj", "a_major", "end")
    currentScale = &scales::A_maj;
  else comp("e_maj", "e_major", "end")
    currentScale = &scales::E_maj;
  else comp("b_maj", "b_major",
              "cb_maj", "cb_major", "end")
    currentScale = &scales::B_maj;
  else comp("fs_maj", "fs_major", "f#_maj", "f#_major",
              "gb_maj", "gb_major", "end")
    currentScale = &scales::Fs_maj;
  else comp("cs_maj", "cs_major", "c#_maj", "c#_major",
              "db_maj", "db_major", "end")
    currentScale = &scales::Cs_maj;
  else comp("f_maj", "f_major", "end")
    currentScale = &scales::F_maj;
  else comp("bb_maj", "bb_major", "end")
    currentScale = &scales::Bb_maj;
  else comp("eb_maj", "eb_major", "end")
    currentScale = &scales::Eb_maj;
  else comp("ab_maj", "ab_major", "end")
    currentScale = &scales::Ab_maj;

  else comp("a_min", "a_minor", "end")
    currentScale = &scales::A_min;
  else comp("e_min", "e_minor", "end")
    currentScale = &scales::E_min;
  else comp("b_min", "b_minor", "end")
    currentScale = &scales::B_min;
  else comp("fs_min", "fs_minor", "f#_min", "f#_minor", "end")
    currentScale = &scales::Fs_min;
  else comp("cs_min", "cs_minor", "c#_min", "c#_minor", "end")
    currentScale = &scales::Cs_min;
  else comp("gs_min", "gs_minor", "g#_min", "g#_minor",
              "ab_min", "ab_minor", "end")
    currentScale = &scales::Gs_min;
  else comp("ds_min", "ds_minor", "d#_min", "d#_minor",
              "eb_min", "eb_minor", "end")
    currentScale = &scales::Ds_min;
  else comp("as_min", "as_minor", "a#_min", "a#_minor",
              "bb_min", "bb_minor", "end")
    currentScale = &scales::As_min;
  else comp("f_min", "f minor")
    currentScale = &scales::F_min;
  else comp("c_min", "c_minor", "end")
    currentScale = &scales::C_min;
  else comp("g_min", "g_minor", "end")
    currentScale = &scales::G_min;
  else comp("d_min", "d_minor", "end")
    currentScale = &scales::D_min;
  else {
    Serial.println("That is not a valid scale!");
    return false;
  }

  setScale(octave);
  return true;
}

bool setScaleFromMidiByte(byte scale, byte octave) {
  switch (scale) {
    case 0:
      currentScale = &scales::C_maj;
      break;
    case 1:
      currentScale = &scales::G_maj;
      break;
    case 2:
      currentScale = &scales::D_maj;
      break;
    case 3:
      currentScale = &scales::A_maj;
      break;
    case 4:
      currentScale = &scales::E_maj;
      break;
    case 5:
      currentScale = &scales::B_maj;
      break;
    case 6:
      currentScale = &scales::Fs_maj;
      break;
    case 7:
      currentScale = &scales::Cs_maj;
      break;
    case 8:
      currentScale = &scales::F_maj;
      break;
    case 9:
      currentScale = &scales::Bb_maj;
      break;
    case 10:
      currentScale = &scales::Eb_maj;
      break;
    case 11:
      currentScale = &scales::Ab_maj;
      break;
    case 12:
      currentScale = &scales::A_min;
      break;
    case 13:
      currentScale = &scales::E_min;
      break;
    case 14:
      currentScale = &scales::B_min;
      break;
    case 15:
      currentScale = &scales::Fs_min;
      break;
    case 16:
      currentScale = &scales::Cs_min;
      break;
    case 17:
      currentScale = &scales::Gs_min;
      break;
    case 18:
      currentScale = &scales::Ds_min;
      break;
    case 19:
      currentScale = &scales::As_min;
      break;
    case 20:
      currentScale = &scales::F_min;
      break;
    case 21:
      currentScale = &scales::C_min;
      break;
    case 22:
      currentScale = &scales::G_min;
      break;
    case 23:
      currentScale = &scales::D_min;
      break;
    default:
      return false;
      break;
  }

  setScale(octave);
  return true;
}

void setupPads(scales::Scale* scale, byte octave)
{
  pads[0].init();
  pads[1].init();
  currentScale = scale;
  setScale(octave);
}
void setup()
{
  Serial.begin(115200);
  setupPads(new scales::CUSTOM_SCALE(scales::F, scales::G, scales::A+12, scales::B+12, scales::C+12, scales::D+12, scales::E+12, scales::F+12), 1);
}

void loop()
{
  while (Serial.available() > 0) {
    int bytes[3]; // all messages will have minimum 3 bytes, others can have more (see setScale for example)
    for (int i = 0; i < 3; i++)
      bytes[i] = Serial.read();
    // non-musical byte, will use this to change values
    if (bytes[0] >> 4 == 15) { // bitshift 4 to move first 4 bits to last so i can check their value (15 == 00001111, which is non-musical byte)
      switch (bytes[1]) {
        case 0: // set scale
          byte octave = Serial.read();
          setScaleFromMidiByte(bytes[2], octave);
          break;
        case 1:
          break;
      }
      Serial.read(); // all system messages end with an extra 0x7f, this clears it so program can continue
    }
    //String str = Serial.readString();
    //parseString(str);
  }
  pads[0].scan(false);
  pads[1].scan(false);
  for(int i = 0; i < 6; i++){
    pots[i].scan();
  }
}

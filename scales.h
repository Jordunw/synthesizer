#pragma once

namespace scales 
{  
    enum notes : byte {
        A = 21,
        As = 22,
        B = 23,
        C = 24,
        Cs = 25,
        D = 26,
        Ds = 27,
        E = 28,
        F = 29,
        Fs = 30,
        G = 31,
        Gs = 32
    };

    // octave cannot be >9 and really shouldnt ever go above 7 (highest octave on an 88 key piano)
    byte toOctave(byte note, byte octave){
        return note + 12 * octave;
    }

    // INCLUDING NEXT OCTAVE OF BASS NOTE CUZ I HAVE 8 PADS

    struct Scale{
      virtual byte* getNotes(){}
    };

    struct CUSTOM_SCALE : public Scale{
        CUSTOM_SCALE(byte note1, byte note2, byte note3, byte note4, byte note5, byte note6, byte note7, byte note8) :
            notes{note1, note2, note3, note4, note5, note6, note7, note8}{}
      
      byte notes[8];
      byte* getNotes() {return notes;} 
    };

    struct C_MAJ : public Scale {
      byte notes[8] = {C, D, E, F, G, A+12, B+12, C+12};
      virtual byte* getNotes() override {return notes;}
    } C_maj;

    struct G_MAJ : public Scale {
      byte notes[8] = {G, A+12, B+12, C+12, D+12, E+12, Fs+12, G+12};
      virtual byte* getNotes() override {return notes;}
    } G_maj;

    struct D_MAJ : public Scale {
      byte notes[8] = {D, E, Fs, G, A+12, B+12, Cs+12, D+12};
      virtual byte* getNotes() override {return notes;}
    } D_maj;

    struct A_MAJ : public Scale {
      byte notes[8] = {A, B, Cs, D, E, Fs, Gs, A+12};
      virtual byte* getNotes() override {return notes;}
    } A_maj;

    struct E_MAJ : public Scale {
      byte notes[8] = {E, Fs, Gs, A+12, B+12, Cs+12, Ds+12, E+12};
      virtual byte* getNotes() override {return notes;}
    } E_maj;

#define Cb_maj B_maj // same scale, different note names
    struct B_MAJ : public Scale {
      byte notes[8] = {B, Cs, Ds, E, Fs, Gs, As+12, B+12};
      virtual byte* getNotes() override {return notes;}
    } B_maj;

#define Gb_maj Fs_maj // same scale, different note names
    struct Fs_MAJ : public Scale {
      byte notes[8] = {Fs, Gs, As+12, B+12, Cs+12, Ds+12, F+12, Fs+12};
      virtual byte* getNotes() override {return notes;}
    } Fs_maj;

#define Db_maj Cs_maj // same scale, different note names
    struct Cs_MAJ : public Scale {
      byte notes[8] = {Cs, Ds, F, Fs, Gs, As+12, C+12, Cs+12};
      virtual byte* getNotes() override {return notes;}
    } Cs_maj;

  // FLATS -> SHARPS FOR THESE SCALES
    struct F_MAJ : public Scale {
      byte notes[8] = {F, G, A+12, As+12, C+12, D+12, E+12, F+12};
      virtual byte* getNotes() override {return notes;}
    } F_maj;

    struct Bb_MAJ : public Scale {
      byte notes[8] = {As, C, D, Ds, F, G, A+12, As+12};
      virtual byte* getNotes() override {return notes;}
    } Bb_maj;

    struct Eb_MAJ : public Scale {
      byte notes[8] = {Ds, F, G, Gs, As+12, C+12, D+12, Ds+12};
      virtual byte* getNotes() override {return notes;}
    } Eb_maj;

    struct Ab_MAJ : public Scale {
      byte notes[8] = {Gs, As+12, C+12, Cs+12, Ds+12, F+12, G+12, Gs+12};
      virtual byte* getNotes() override {return notes;}
    } Ab_maj;



  // MINOR SCALES (imma define them cuz it just makes it a bit easier)
    
    struct A_MIN : public Scale {
      byte notes[8] = {A, B, C, D, E, F, G, A+12};
      virtual byte* getNotes() override {return notes;}
    } A_min;

    struct E_MIN : public Scale {
      byte notes[8] = {E, Fs, G, A+12, B+12, C+12, D+12, E+12};
      virtual byte* getNotes() override {return notes;}
    } E_min;

    struct B_MIN : public Scale {
      byte notes[8] = {B, Cs, D, E, Fs, G, A+12, B+12};
      virtual byte* getNotes() override {return notes;}
    } B_min;

    struct Fs_MIN : public Scale {
      byte notes[8] = {Fs, Gs, A+12, B+12, Cs+12, D+12, E+12, Fs+12};
      virtual byte* getNotes() override {return notes;}
    } Fs_min;

    struct Cs_MIN : public Scale {
      byte notes[8] = {Cs, Ds, E, Fs, Gs, A+12, B+12, Cs+12};
      virtual byte* getNotes() override {return notes;}
    } Cs_min;

#define Ab_min Gs_min // same scale, different note names
    struct Gs_MIN : public Scale {
      byte notes[8] = {Gs, As+12, B+12, Cs+12, Ds+12, E+12, Fs+12, Gs+12};
      virtual byte* getNotes() override {return notes;}
    } Gs_min;

#define Eb_min Ds_min // same scale, different note names
    struct Ds_MIN : public Scale {
      byte notes[8] = {Ds, F, Fs, Gs, As+12, B+12, Cs+12, Ds+12};
      virtual byte* getNotes() override {return notes;}
    } Ds_min;

#define Bb_min As_min // same scale, different note names
    struct As_MIN : public Scale {
      byte notes[8] = {As, C, Cs, Ds, F, Fs, Gs, As+12};
      virtual byte* getNotes() override {return notes;}
    } As_min;


// SHARPS -> FLATS

    struct F_MIN : public Scale {
      byte notes[8] = {F, G, Gs, As+12, C+12, Cs+12, Ds+12, F+12};
      virtual byte* getNotes() override {return notes;}
    } F_min;

    struct C_MIN : public Scale {
      byte notes[8] = {C, D, Ds, F, G, Gs, As+12, C+12};
      virtual byte* getNotes() override {return notes;}
    } C_min;

    struct G_MIN : public Scale {
      byte notes[8] = {G, A+12, As+12, C+12, D+12, Ds+12, F+12, G+12};
      virtual byte* getNotes() override {return notes;}
    } G_min;

    struct D_MIN : public Scale {
      byte notes[8] = {D, E, F, G, A+12, As+12, C+12, D+12};
      virtual byte* getNotes() override {return notes;}
    } D_min;
    
} // namespace scales

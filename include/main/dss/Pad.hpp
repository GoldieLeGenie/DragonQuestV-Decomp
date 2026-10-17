#pragma once
#include <globaldefs.h>
#include "main/dss/UnkOverlaySlot.hpp"

namespace dss {
    struct Pad {
        unsigned short playMask_;               // 0x00 keys still read from the pad while playing
        unsigned short wait_;                   // 0x02 frames before the record/play starts
        unsigned short playCount_;              // 0x04
        unsigned short mode_;                   // 0x06 0: none, 1: record, 2: play
        unsigned short recordCount_;            // 0x08
        unsigned short playIndex_;              // 0x0A
        int unk_0c;                             // 0x0C record buffer full: unkfunc_0204bc44 instead of stopping
        int unk_10;                             // 0x10 play the record file block by block
        int unk_14;                             // 0x14 next block of the record file
        char fileName_[0x80];                   // 0x18 record file
        int unk_98;                             // 0x98 nonzero: do not read the record file
        unsigned short trig_;                   // 0x9C
        unsigned short cont_;                   // 0x9E
        unsigned short repeat_;                 // 0xA0
        unsigned short release_;                // 0xA2
        unsigned short unk_a4;                  // 0xA4
        unsigned short dir_;                    // 0xA6
        int unk_a8;                             // 0xA8
        unsigned int repeatTimer_[12];          // 0xAC
        unsigned short mask_;                   // 0xDC
        int maskL_;                             // 0xE0

        Pad();
        void unkfunc_0204b640();                // init
        void unkfunc_0204b660();                // read the keys
        void unkfunc_0204baec();                // update
        int pad();                              // held keys & enable mask
        int padDir();                           // direction
        int edge();                             // triggered keys & enable mask
        int unkfunc_0204bc00();                 // repeat keys & enable mask
        int unkfunc_0204bc10();                 // L+R+SELECT+START held
        void unkfunc_0204bc24(int flag);        // flag != 0: mask out the L button
        void unkfunc_0204bc44();                // record buffer full
        void unkfunc_0204bc48();                // stop recording
        int unkfunc_0204bc78();                 // load the next block of the record file
        void unkfunc_0204bd50(unsigned short playMask);    // start playing, keeping playMask keys
        void unkfunc_0204bd74();                // start playing
        void unkfunc_0204bd98();                // play again
        unsigned short unkfunc_0204bdb8();      // next played keys
        void unkfunc_0204be10(unsigned short keys);     // record keys
        void unkfunc_0204be48();                // stop playing
        void unkfunc_0204be8c();                // clear the record
        void unkfunc_0204be98(unsigned short keys, int count);  // record keys count times
        void unkfunc_0204bef0(unsigned short keys, int count);  // record count presses of keys
    };

    extern Pad g_Pad;
}

extern unsigned short data_020f9918[7201];      // recorded keys (0xFFFF: end)


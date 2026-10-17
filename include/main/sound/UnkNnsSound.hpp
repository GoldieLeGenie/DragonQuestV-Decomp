#pragma once
#include <globaldefs.h>

// BGM/SE player handles (two BGM handles to switch without reloading)
struct UnkSoundHandle {
    int handle_[2];                             // 0x00 NNSSndHandle
    int current_;                               // 0x08 handle in use
    int prev_;                                  // 0x0C
    int pause_;                                 // 0x10
    int unk_14;                                 // 0x14
    int volumeSys_;                             // 0x18
    int volume_;                                // 0x1C
    int bgm_[2];                                // 0x20 player of each handle
    int seArc_;                                 // 0x28
    int seIndex_;                               // 0x2C
    int sePlaying_;                             // 0x30
    int active_[2];                             // 0x34

    UnkSoundHandle();
    ~UnkSoundHandle();
    void unkfunc_0204fde0(int a);                       // init
    void unkfunc_0204fdfc(int bgm, int sub);            // play bgm
    void unkfunc_0204feac(int fade);                    // stop bgm
    int unkfunc_0204fed0();                             // bgm playing
    int unkfunc_0204ff08();                             // bgm stopped
    void unkfunc_0204ff40(int pause);                   // pause
    int unkfunc_0204ff50();                             // paused
    void unkfunc_0204ff54(int fade);                    // stop all
    void unkfunc_0204ff74(int seqArc, int index);       // play se
    int unkfunc_020500c4(int seqArc, int index);        // se playing
    void unkfunc_020500dc(int fade);                    // stop se
    int unkfunc_020500f8();
    void unkfunc_0205011c(int volume);                  // set volume
    void unkfunc_0205012c();                            // apply the volume
};

// Game wrapper of the NNS sound library
struct UnkNnsSound {
    void* memory_;                              // 0x00 sound heaps memory
    int size_;                                  // 0x04 size of the main heap
    void* heap_[3];                             // 0x08 main, sub, wave heaps
    unsigned char arc_[0x94];                   // 0x14 sound archive
    int unk_a8;                                 // 0xA8
    void* file_;                                // 0xAC sound archive file
    int group_;                                 // 0xB0 load the group 20
    int unk_b4;                                 // 0xB4
    int bgm_;                                   // 0xB8
    int subBgm_;                                // 0xBC
    int state_;                                 // 0xC0
    int saved_;                                 // 0xC4
    int heapState_[3];                          // 0xC8

    UnkNnsSound();
    ~UnkNnsSound();
    void unkfunc_0205015c(void* file, void* memory, int size, int group);  // init
    void unkfunc_020501c0();                            // load the sound archive
    void unkfunc_0205027c();                            // NNS_SndMain
    void unkfunc_02050284(int bgm, int sub);            // load a bgm
    void unkfunc_020503f4(int a, int b);
    int unkfunc_0205040c(int no, void* heap);           // load a sequence
    int unkfunc_02050418(int no, void* heap);           // load a bank
    int unkfunc_02050424(int no, void* heap);           // load a wave archive
};

struct UnkSoundMember {
    int unk_00;                                 // 0x00
    int unk_04;                                 // 0x04

    UnkSoundMember();
    ~UnkSoundMember();
    void unkfunc_02050438();
    void unkfunc_02050440(int no);
    void unkfunc_0205045c(int value);
    int unkfunc_02050464();
};

extern int data_02101570[2];
extern int data_0209a370;
extern UnkNnsSound data_02101584;
extern int data_0209a374;

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
    void init(int a);                       // init
    void playBgm(int bgm, int sub);            // play bgm
    void stopBgm(int fade);                    // stop bgm
    int isBgmPlaying();                             // bgm playing
    int isBgmStopped();                             // bgm stopped
    void setPause(int pause);                   // pause
    int isPaused();                             // paused
    void stopAll(int fade);                    // stop all
    void playSe(int seqArc, int index);       // play se
    int isSe(int seqArc, int index);        // se playing
    void stopSe(int fade);                    // stop se
    int isSePlaying();
    void setVolume(int volume);                  // set volume
    void applyVolume();                            // apply the volume
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
    int subBgmLoaded_;                                 // 0xB4
    int bgm_;                                   // 0xB8
    int subBgm_;                                // 0xBC
    int state_;                                 // 0xC0
    int saved_;                                 // 0xC4
    int heapState_[3];                          // 0xC8

    UnkNnsSound();
    ~UnkNnsSound();
    void init(void* file, void* memory, int size, int group);  // init
    void loadArchive();                            // load the sound archive
    void update();                            // NNS_SndMain
    void loadBgm(int bgm, int sub);            // load a bgm
    void preload(int a, int b);
    int loadSeq(int no, void* heap);           // load a sequence
    int loadBank(int no, void* heap);           // load a bank
    int loadWaveArc(int no, void* heap);           // load a wave archive
};

struct UnkSoundMember {
    int unk_00;                                 // 0x00
    int unk_04;                                 // 0x04

    UnkSoundMember();
    ~UnkSoundMember();
    void init();
    void play(int no);
    void stop(int value);
    int isPlaying();
};

extern int data_02101570[2];
extern int data_0209a370;
extern UnkNnsSound data_02101584;
extern int data_0209a374;

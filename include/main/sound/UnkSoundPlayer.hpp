#pragma once
#include <globaldefs.h>
#include "main/sound/UnkNnsSound.hpp"

// sound player of the game (bgm and se handles)
struct UnkSoundPlayer {
    int enable_;                                // 0x000
    int bgm_;                                   // 0x004
    UnkSoundMember unk_008;                     // 0x008
    UnkSoundHandle bgmHandle_[3];               // 0x010
    UnkSoundHandle seHandle_[8];                // 0x0C4
    UnkSoundHandle unk_2a4;                     // 0x2A4
    int bgmVolumeSys_;                          // 0x2E0
    int bgmVolume_;                             // 0x2E4
    int seVolumeSys_;                           // 0x2E8
    int seVolume_;                              // 0x2EC

    UnkSoundPlayer();
    ~UnkSoundPlayer();
    void init();                        // init
    void loadBgm(int bgm, int sub);        // load bgm
    void preload(int a, int b);
    void playBgm(int player, int bgm, int sub);   // play bgm
    void stopBgm(int player, int fade);    // stop bgm
    void stopAllBgm(int player, int fade);    // stop all bgm
    int isBgmPlaying(int player);               // bgm playing
    int isBgmStopped(int player);               // bgm stopped
    void pauseBgm(int player, int pause);   // pause bgm
    void setBgmVolumeSys(int volume);              // set bgm volume (sys)
    void setBgmVolume(int volume);              // set bgm volume
    int getBgmVolume();                         // get bgm volume
    void setSeVolumeSys(int volume);              // set se volume (sys)
    void applyBgmVolume();                        // apply bgm volume
    void applySeVolume();                        // apply se volume
    void applySeHandleVolume(int index);
    int playSe(int seqArc, int index);    // play se
    void stopSeHandle(int index, int fade);     // stop a se handle
    void stopSe(int seqArc, int index, int fade);    // stop se
    void stopAllSe(int fade);                // stop all se
    void playStrm(int no);
    void stopStrm(int value);
    int isStrmPlaying();
    void updateSe();                        // update the se handles
};

extern UnkSoundPlayer data_021025e0;

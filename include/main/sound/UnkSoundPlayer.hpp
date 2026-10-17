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
    void unkfunc_02054fd0();                        // init
    void unkfunc_02055010(int bgm, int sub);        // load bgm
    void unkfunc_02055024(int a, int b);
    void unkfunc_02055038(int player, int bgm, int sub);   // play bgm
    void unkfunc_02055070(int player, int fade);    // stop bgm
    void unkfunc_02055088(int player, int fade);    // stop all bgm
    int unkfunc_020550a0(int player);               // bgm playing
    int unkfunc_020550b0(int player);               // bgm stopped
    void unkfunc_020550c0(int player, int pause);   // pause bgm
    void unkfunc_020550d4(int volume);              // set bgm volume (sys)
    void unkfunc_020550e4(int volume);              // set bgm volume
    int unkfunc_020550f4();                         // get bgm volume
    void unkfunc_020550fc(int volume);              // set se volume (sys)
    void unkfunc_0205510c();                        // apply bgm volume
    void unkfunc_0205513c();                        // apply se volume
    void unkfunc_0205516c(int index);
    int unkfunc_02055194(int seqArc, int index);    // play se
    void unkfunc_020551f0(int index, int fade);     // stop a se handle
    void unkfunc_02055208(int seqArc, int index, int fade);    // stop se
    void unkfunc_0205523c(int fade);                // stop all se
    void unkfunc_02055260(int no);
    void unkfunc_02055270(int value);
    int unkfunc_02055280();
    void unkfunc_0205528c();                        // update the se handles
};

extern UnkSoundPlayer data_021025e0;

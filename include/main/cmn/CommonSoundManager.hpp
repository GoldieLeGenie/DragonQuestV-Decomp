#pragma once
#include <globaldefs.h>

namespace cmn {
    struct CommonSoundManager {
        int nextMapMe_;                             // 0x00
        int interruptMe_;                           // 0x04
        int soundType_;                             // 0x08
        int playSoundNo_;                           // 0x0C
        int waitSoundTime_;                         // 0x10
        int playTime_;                              // 0x14
        int soundCount_;                            // 0x18
        int preSoundIndex_;                         // 0x1C
        int isPlaySound_;                           // 0x20

        void initialize();
        void setPlaySound(int music, bool flag);
        int isPlaySound();
        void execSound();
        void setFadeOut(int frame);
    };

    extern CommonSoundManager g_cmnSoundManager;
}

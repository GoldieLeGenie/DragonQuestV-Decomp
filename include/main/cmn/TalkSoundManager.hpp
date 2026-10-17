#pragma once
#include <globaldefs.h>

namespace cmn {
    struct TalkSoundManager {
        static const int MESSAGE_COUNT = 33;

        int orderSound_[MESSAGE_COUNT];             // 0x00
        int orderDataCount_;                        // 0x84
        int index_;                                 // 0x88
        int charaNo_;                               // 0x8C

        void setup();
        void setVoice(int charaNo);
        void setMessageSound(int count, int character);
        int getOrderMessageSound();
        int getDefaultMessageSound();
        void setOrderMessage(int sound);
        int getCharacterVoice(int character);
        int getPlayerVoice();
        int getPlayerVoice(int charaNo);
        int getMostHeroicVoice();
    };

    extern TalkSoundManager g_talkSound;
}

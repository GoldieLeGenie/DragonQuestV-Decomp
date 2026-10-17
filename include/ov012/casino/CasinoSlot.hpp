#pragma once
#include <globaldefs.h>
#include "ov012/casino/CasinoMiniGameBase.hpp"

namespace casino {
    struct CasinoSlot : CasinoMiniGameBase {
        static const char* stageSlot100;
        static const char* stageSlot10;
        static const char* stageSlot1;
        static const int reelMax = 5;

        enum {
            SLOT_REEL_TYPEA = 0,
            SLOT_REEL_TYPEB = 1,
            SLOT_REEL_TYPEC = 2,
            SLOT_REEL_TYPED = 3,
            SLOT_REEL_TYPEE = 4,
            SLOT_REEL_TYPE_MAX = 5,
        };

        int slotType_;                          // 0x08
        int waitTimer_;                         // 0x0C
        int stopFlag_;                          // 0x10
        int bingoType_;                         // 0x14
        int reelID[reelMax];                    // 0x18
        int lineBingo[9];                       // 0x2C
        int bingoCounter[9];                    // 0x50

        CasinoSlot();
        static CasinoSlot* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        virtual char* getStageName();
        void playLightAnim(int pos);
        void playDarkAnim(int pos);
        void setSlotType(int type);
        void rotReel(int index, unsigned short angle);
        char* getSlotStageName(int type);
        void stopEventAnim();
        void setUseReel(int type, bool flag);
        void setLineLamp(int line, bool flag);
        void setLampReelOff();
        void setLampOff();
        void setLineBingo(int line);
        int setBingoAnim(int image, int count);
        void judgeBingoType(int type);
        void setBigBingoAnim();
        void setBingoType(int type);
    };
}

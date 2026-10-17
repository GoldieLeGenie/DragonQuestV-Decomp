#pragma once
#include "globaldefs.h"
#include "main/dss/DssUtils.hpp"

namespace dq5 {
namespace level {
    struct FurnitureParam;
}
}

namespace twn
{
    struct TownFurnitureObject
    {
        enum {
            PHASE_NONE = 0,
            PHASE_FIRST_MESSAGE = 1,
            PHASE_WAIT_OPEN = 2,
            PHASE_OPEN = 3,
            PHASE_WAIT_CLOSE = 4,
            PHASE_NEXT_MESSAGE = 5,
            PHASE_EXTEND_CLOSE = 6,
            PHASE_CLOSE = 7
        };
        enum {
            ANIM_NONE = 0,
            ANIM_NORMAL = 1,
            ANIM_OPEN = 2,
            ANIM_STAY = 3,
            ANIM_CLOSE = 4
        };
        static const int OPEN_ANIM_ENABLE = 1;
        static const int CLOSE_ANIM_ENABLE = 2;
        static const int CHECK_ANIM_FLAG = 4;
        static const int CHECK_MESSAGE_FLAG = 8;
        static const int DEFAULT_SETTING = OPEN_ANIM_ENABLE | CLOSE_ANIM_ENABLE | CHECK_MESSAGE_FLAG;

        dq5::level::FurnitureParam* common_;    /* 0x04 */
        int uid_;                               /* 0x08 */
        int data_;                              /* 0x0C */
        dss::BitFlag<unsigned char> furniture_; /* 0x10 */
        int openWindow_;                        /* 0x14 */
        int phase_;                             /* 0x18 */
        int index_;                             /* 0x1C */

        TownFurnitureObject();
        ~TownFurnitureObject();
        void setup(int uid, int data, dq5::level::FurnitureParam* pCommon, int search);
        virtual void setupExtend(int data);
        virtual bool isRiseupEnd();
        virtual void cleanup();
        void execute();
        void setMessage();
        void openObject();
        void closeObject();
        virtual void setFirstMessage();
        virtual void setSecondMessage() = 0;
        virtual void startRiseup();
        virtual bool endRiseup();
        virtual bool soundStart();
        dss::Fix32Vector3 getFurnPosition();
        unsigned long checkMsg();
        void addMessage(int mesID, bool flag);
        bool isFinish();
    };

    struct TownFurnitureEncount : TownFurnitureObject
    {
        unsigned short monster_;                /* 0x20 */

        TownFurnitureEncount();
        ~TownFurnitureEncount();
        virtual void setupExtend(int data);
        virtual void setSecondMessage();
        virtual void cleanup();
    };

    struct TownFurnitureGold : TownFurnitureObject
    {
        TownFurnitureGold();
        ~TownFurnitureGold();
        virtual void setSecondMessage();
        virtual void startRiseup();
        virtual bool endRiseup();
        void addPartyGold();
        virtual bool isRiseupEnd();
    };

    struct TownFurnitureItem : TownFurnitureObject
    {
        static const int SOUND_WAIT = 0xbe;

        int counter_;                           /* 0x20 */

        TownFurnitureItem();
        ~TownFurnitureItem();
        virtual void setSecondMessage();
        virtual void startRiseup();
        virtual bool endRiseup();
        int addPlayerItem();
        virtual bool isRiseupEnd();
        virtual bool soundStart();
    };

    struct TownFurnitureMessage : TownFurnitureObject
    {
        TownFurnitureMessage();
        ~TownFurnitureMessage();
        virtual void setFirstMessage();
        virtual void setSecondMessage();
    };

    struct TownFurnitureNothing : TownFurnitureObject
    {
        int getFlag_;                           /* 0x20 */

        TownFurnitureNothing();
        ~TownFurnitureNothing();
        virtual void setSecondMessage();
    };

    struct TownFurnitureManager
    {
        enum {
            CHECK_NONE = 0,
            CHECK_MESSAGE = 1,
            CHECK_ITEM = 2,
            CHECK_GOLD = 3,
            CHECK_MONSTER = 4,
        };

        struct TwinklePoint {
            dss::Fix32Vector3 position;             // 0x00
            int enable;                             // 0x0C
        };

        static const int interval_ = 32;
        static const int MAX_TWINKLE_POS = 16;
        static const int twinkleEffect = 0x38b;

        TownFurnitureObject* object_;               // 0x000
        TownFurnitureNothing nothingObject_;        // 0x004
        TownFurnitureMessage msgObject_;            // 0x028
        TownFurnitureItem itemObject_;              // 0x048
        TownFurnitureGold goldObject_;              // 0x06C
        TownFurnitureEncount encountObject_;        // 0x08C
        int list_;                                  // 0x0B0 first FurnitureData record of the map
        int remiIndex_;                             // 0x0B4
        int size_;                                  // 0x0B8
        int floorItem_;                             // 0x0BC
        int phase_;                                 // 0x0C0
        int force_;                                 // 0x0C4
        int prevCheck_;                             // 0x0C8
        TwinklePoint twinkle[MAX_TWINKLE_POS];      // 0x0CC

        TownFurnitureManager();
        ~TownFurnitureManager();
        static TownFurnitureManager* getSingleton();
        void initialize();
        void terminate();
        void execute();
        bool isProcess();
        void forceProcess();
        int getFurnitureIndex(int uid);
        void draw();
        void returnFurnitureEncount();
        void openDoor(int uid);
        void closeDoor(int uid);
        bool isOpenDoor(int uid);
        void setFurnFlag(int uid, int flag);
        bool checkObject(int uid, bool rev, bool search, int lock);
        bool checkRevMessage(int index);
        int checkCoffer(int uid);
        int getCofferType(int uid);
        int searchFloorItem();
        void setTwinklePoint();
        void drawTwinklePoint();
        bool isActive();
        void bootSlot(int uid);
        bool mirrorTalk();
        int getLeaderIndex();
        int getTwinkleEffectID();
    };
} // namespace twn

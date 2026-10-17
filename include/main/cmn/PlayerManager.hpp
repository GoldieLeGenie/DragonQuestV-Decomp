#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/cmn/MoveBase.hpp"

namespace cmn
{
    struct PlayerManager {
        static const int SCRIPT_SEARCH_OBJECT_NUM = 16;

        // vtable                               // 0x00
        int flagMapLink_;                       // 0x04
        int charaColl_;                         // 0x08
        MoveAction scriptMove_;                 // 0x0C
        int scriptSearchUid_[SCRIPT_SEARCH_OBJECT_NUM]; // 0x60
        int talkRefresh_;                       // 0xA0

        static int locked_;

        PlayerManager();
        ~PlayerManager();
        static void setLock(bool flag);
        static bool isLock();
        void setScriptSearchObject(int uid);
        void delScriptSearchObject(int uid);
        void resetTalkRefresh();
        void setTownCharaColl(bool charaColl);
        virtual void setPosition(dss::Fix32Vector3& position) = 0;
        virtual dss::Fix32Vector3& getPosition() = 0;
        virtual short getDirection() = 0;
        virtual void setDirection(short direction) = 0;
        virtual void resetParty();
        virtual void resetDrawPartyCount() = 0;
        virtual void resetAlpha();
        virtual void setMoveToFirstFlag() = 0;
        virtual bool getMoveToFirstFlag() = 0;
        virtual void setPartyDrawOne() = 0;
        virtual void setDrawPartyNone() = 0;
        virtual int getPartyDrawCount() = 0;
        virtual bool isEqalNextPos(int index) = 0;
        virtual char getPartyDrawAlpha(int index) = 0;
        virtual void addPartyDrawAlpha(int index, char alpha) = 0;
        virtual void scriptColl(dss::Fix32Vector3& position, short& direction) = 0;
        virtual bool checkScriptSearch() = 0;
    };
} // namespace cmn

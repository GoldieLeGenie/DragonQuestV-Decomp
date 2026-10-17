#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/leveldata/ActionTypeList.hpp"
#include "main/leveldata/EffectMessage.hpp"

namespace status {
    extern dq5::level::ActionTypeList* actionType_;
    extern dq5::level::EffectMessage* effectMessage_;

    void getActionType(int index);

    struct StatusChangeOne {
        static const int FLAG_ENABLE = 0x1;
        static const int FLAG_RELEASE = 0x2;

        dss::BitFlag<unsigned int> flag_;   // 0x00
        short actionIndex_;                 // 0x04
        unsigned char damageType_;          // 0x06
        unsigned char count_;               // 0x07
        unsigned char turn_;                // 0x08
        char pattern_;                      // 0x09
        char astron_;                       // 0x0A

        StatusChangeOne();
        ~StatusChangeOne();
        static int getEffectMessage(int index, int actionIndex);
        void setup(dq5::level::ActionParam::ACTIONTYPE type, int actionIndex, bool flag);
        void cleanup();
        void clear();
        int getActionIndex();
        void setTurn(unsigned char turn);
        int getTurn();
        void setEndRound();
        void setCount(int count);
        int getCount();
        void execStartOfTurn();
        void execEndOfTurn();
        void execEndOfRound();
        void execWalk();
        int addTurn();
        bool isCancel();
        void setEnable(bool flag);
        bool isEnable() const;
        void setRelease(bool flag);
        bool isRelease() const;
        static bool isValidOnAstron(int damageType);
        static bool isValidOnSpazz(int damageType);
        static bool isAfterOnSleep(int damageType);
        static bool isAfterOnPath1(int damageType);
        static bool isAfterOnConfuze(int damageType);
        static bool isAfterOnPowerSave(int damageType);
        int getExecMessage();
        int getExecMessage2();
        int getResultPlayerMessage();
        int getResultMonsterMessage();
        int getAgainEnableMessage();
        int getAgainDisableMessage();
        int getReleaseMessage();
    };
}

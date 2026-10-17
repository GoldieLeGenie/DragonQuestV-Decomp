#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/StatusChangeOne.hpp"
#include "main/leveldata/ActionParam.hpp"

namespace status {
    struct StatusChange {
        StatusChangeOne status_[51];                // 0x000

        static StatusChangeOne statusFizzleZone_;
        static StatusChangeOne statusCloseDoor_;
        static StatusChangeOne statusToherosu_;
        static StatusChangeOne statusSinobiasi_;
        static StatusChangeOne statusMonstersFood_;
        static StatusChangeOne statusTimeStop_;
        static CharacterType characterTypeForTimeStop_;

        StatusChange();
        ~StatusChange();
        StatusChangeOne& getStatusChangeOne(int rel);
        StatusChangeOne* getStatusChangeOneForOnlyOne(int rel);
        void restore(int index);
        void store(int index);
        bool setup(int actionIndex, bool flag);
        void cleanup(dq5::level::ActionParam::ACTIONTYPE rel);
        void setup(dq5::level::ActionParam::ACTIONTYPE re, bool flag);
        void clear();
        bool isValidBefore(int damageType);
        void checkValidAfter(int damageType);
        int isEnable(dq5::level::ActionParam::ACTIONTYPE rel);
        void setTurn(dq5::level::ActionParam::ACTIONTYPE status, unsigned char turn);
        void setCount(dq5::level::ActionParam::ACTIONTYPE status, unsigned char count);
        int getRestTurn(dq5::level::ActionParam::ACTIONTYPE status);
        void execStartOfTurn();
        void execEndOfTurn();
        void execEndOfRound();
        void execEndOfRoundForAll();
        void printAll();
        void print(dq5::level::ActionParam::ACTIONTYPE type, char* name);
        void execEndOfBattle();
        void execWalk();
        dq5::level::ActionParam::ACTIONTYPE isRelease();
        bool isRelease(dq5::level::ActionParam::ACTIONTYPE rel);
        void release(dq5::level::ActionParam::ACTIONTYPE rel);
        int getActionIndex(dq5::level::ActionParam::ACTIONTYPE rel);
        int getExecMessage(dq5::level::ActionParam::ACTIONTYPE rel);
        int getExecMessage2(dq5::level::ActionParam::ACTIONTYPE rel);
        int getResultMessage(dq5::level::ActionParam::ACTIONTYPE rel, CharacterType type);
        int getResultMessage2(dq5::level::ActionParam::ACTIONTYPE rel, CharacterType type);
        int getAgainEnableMessage(dq5::level::ActionParam::ACTIONTYPE rel);
        int getAgainDisableMessage(dq5::level::ActionParam::ACTIONTYPE rel);
        int getReleaseMessage();
        int getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE rel);
        static void setToherosInfo(unsigned short info);
        static unsigned short getToherosInfo();
        static void setSinobiasiInfo(unsigned short info);
        static unsigned short getSinobiasiInfo();
        static void setMonstersFoodInfo(unsigned short info);
        static unsigned short getMonstersFoodInfo();
        static void StaticClear();
        static StatusChangeOne& getTimeStop();
        static void setCharacterTypeForTimeStop(CharacterType type);
        static CharacterType getCharacterTypeForTimeStop();
    };
}

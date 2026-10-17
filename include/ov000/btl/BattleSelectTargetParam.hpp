#pragma once
#include <globaldefs.h>

namespace status {
    struct CharacterStatus;
}

namespace btl {
    struct BattleSelectTargetParam {
        enum CallTargetSelect {
            StartRound = 0,
            StartTurn = 1,
        };

        static const int CHARACTER_MAX = 18;

        status::CharacterStatus* sourceCharacterStatus[CHARACTER_MAX];  // 0x00
        status::CharacterStatus* targetCharacterStatus[CHARACTER_MAX];  // 0x48
        status::CharacterStatus* actorCharacterStatus_;                 // 0x90
        int sourceCount_;                                               // 0x94
        int targetCount_;                                               // 0x98
        int actionIndex_;                                               // 0x9C
        int targetGroup_;                                               // 0xA0
        int targetIndex_;                                               // 0xA4
        CallTargetSelect callTarget_;                                   // 0xA8

        BattleSelectTargetParam();
        ~BattleSelectTargetParam();
        void clear();
        void setActorCharacterStatus(status::CharacterStatus* info);
        status::CharacterStatus* getActorCharacterStatus();
        void setTargetGroupIndex(int group);
        int getTargetGroupIndex();
        void setTargetIndex(int index);
        int getTargetIndex();
        void setSourceCharacterStatus(int index, status::CharacterStatus* characterStatus);
        status::CharacterStatus* getSourceCharacterStatus(int index);
        void setSourceCount(int count);
        int getSourceCount();
        int getSourceGroup(int index);
        int getSourceCountForGroup(int group);
        status::CharacterStatus* getSourceCharacterStatusForGroup(int group, int index);
        int getSourceCountForGroupDead(int group);
        status::CharacterStatus* getSourceCharacterStatusForGroupDead(int group, int index);
        void setTargetCharacterStatus(int index, status::CharacterStatus* characterStatus);
        status::CharacterStatus* getTargetCharacterStatus(int index);
        void setTargetCount(int count);
        int getTargetCount();
        void setActionIndex(int actionIndex);
        int getActionIndex();
        void setCallTarget(CallTargetSelect call);
        CallTargetSelect getCallTarget();
    };
}

#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/UseActionMessage.hpp"
#include "main/status/UseActionFlag.hpp"

namespace status
{
    struct CharacterStatus;
    struct HaveItemSack;

    struct UseActionParam {
        CharacterStatus* actorCharacterStatus_;     // 0x000
        CharacterStatus* targetCharacterStatus_[18];// 0x004
        int targetResult_[18];                      // 0x04C
        HaveItemSack* actorHaveItemSack_;           // 0x094
        int actionIndex_;                           // 0x098
        int addActionIndex_;                        // 0x09C
        int preActionIndex_;                        // 0x0A0
        int itemIndex_;                             // 0x0A4
        int itemSortIndex_;                         // 0x0A8
        int targetCount_;                           // 0x0AC
        int damage_;                                // 0x0B0
        int currentTargetIndex_;                    // 0x0B4
        int actionDefenceValue_;                    // 0x0B8
        int effectValue_;                           // 0x0BC
        int playerEffectValue_;                     // 0x0C0
        int monsterEffectValue_;                    // 0x0C4
        UseActionMessage message_[18];              // 0x0C8
        UseActionFlag actionFlag_;                  // 0x428
        int result_;                                // 0x42C
        int exec_;                                  // 0x430

        UseActionParam();
        ~UseActionParam();
        void clear();
        void clearMessage();
        void setPlayerEffectValue(int value);
        void setMonsterEffectValue(int value);
        void setActionIndex(int index);
        CharacterStatus* getActorCharacterStatus();
        CharacterStatus* getTargetCharacterStatus(int index);
        int getCurrentTargetIndex();
        int getPlayerEffectValue();
        int getMonsterEffectValue();
        UseActionMessage& getUseActionMessage(int index);
        void setTargetCharacterStatus(int index, CharacterStatus* info);
        int getActionIndex();
        void setAddActionIndex(int actionIndex);
        void setTargetCount(int count);
        int getTargetCount();
        void setEffectValue(int value);
        int getEffectValue();
        void setResult(bool flag);
        int getActionDefenceValue();
        void setActorCharacterStatus(CharacterStatus* info);
        int getPreActionIndex();
        void setActionDefenceValue(int value);
        bool isResult();
        bool isTargetResult(int index);
        int getAddActionIndex();
        void clearAddActionIndex();
        int getItemSortIndex();
        void setCurrentTargetIndex(int index);
        void setItemSortIndex(int sortIndex);
        void setDamage(int dm);
    };
} // namespace status

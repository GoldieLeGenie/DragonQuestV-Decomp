#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"

namespace status {
    struct CharacterStatus {
        enum DamageAnimation {
            NoAnim = 0,
            Damage = 1,
            Death = 2,
            Disappear = 3,
            MultiDamage = 4,
        };
        enum DamageSound {
            NoSe = 0,
            KaishinSe = 1,
            TsukonSe = 2,
        };

        static const int FLAG_ANIMATION_DAMAGE = 0x1;
        static const int FLAG_ANIMATION_DEATH = 0x2;
        static const int FLAG_ANIMATION_DISAPPEAR = 0x4;
        static const int FLAG_ANIMATION_ESCAPE = 0x80;
        static const int FLAG_ANIMATION_DAMAGE_ADD = 0x100;
        static const int FLAG_ANIMATION_REBIRTH = 0x200;

        // vtable                                       // 0x000
        CharacterType characterType_;                   // 0x004
        HaveStatusInfo haveStatusInfo_;                 // 0x008
        HaveBattleStatus haveBattleStatus_;             // 0x434
        int characterIndex_;                            // 0x4E4
        int characterGroup_;                            // 0x4E8
        int arrayIndex_;                                // 0x4EC
        dss::Flag menuStatusFlag_;                      // 0x4F0
        DamageAnimation damageAnimation_;               // 0x4F4
        DamageAnimation damageAnimationMulti_;          // 0x4F8
        DamageSound damageSound_;                       // 0x4FC
        dss::Flag damageAnimationFlag_;                 // 0x500
        dss::Flag type_;                                // 0x504

        CharacterStatus();
        ~CharacterStatus();
        bool isActionEnable();
        bool isActionEnableWithoutDragoram();
        void setup(CharacterType type, int group, int index);
        void setMenuStatusFlag(HaveStatusInfo::DiffStatus status);
        void setNoneAnimation();
        HaveStatusInfo& getHaveStatusInfo();
        CharacterType getCharacterType();
        int getGroupIndex();
        void setCharacterIndex(int index);
        int getCharacterIndex();
        HaveBattleStatus& getHaveBattleStatus();
        void setArrayIndex(int index);
        int getArrayIndex();
        void setCommandType(CommandType type);
        void setDamageAnimation();
        void clearDamageAnimation();
        bool isDamageAnimation();
        void setAddDamageAnimation();
        void clearAddDamageAnimation();
        void setDeathAnimation();
        void clearDeathAnimation();
        bool isDeathAnimation();
        void setDisappearAnimation();
        void clearDisappearAnimation();
        bool isDisappearAnimation();
        void setEscapeAnimation();
        void clearEscapeAnimation();
        bool isEscapeAnimation();
        void setRebirthAnimation();
        void clearRebirthAnimation();
        bool isRebirthAnimation();

        virtual void setMosyasChange(int monsterIndex);
        virtual void setMosyasChange(CharacterStatus* target);
        virtual void setMosyasRelease();
        virtual bool isDeathDisable();
        void setKaishinSound();
        void setTsukonSound();
        bool isKaishinSound();
        bool isTsukonSound();
        void setNoneSound();
        int getCommandType() const;
        void clearTsukonSound();
        virtual void print();
        virtual void printAction();
    };
}

#pragma once
#include <globaldefs.h>
#include "main/status/GameFlag.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "ov000/btl/BattleSelectTargetParam.hpp"

namespace status {
    struct CharacterStatus;
    struct PlayerStatus;
}

namespace btl {
    struct AutoActionParam {
        static const int MONSTER_MAX = 12;

        // vtable                                                   // 0x000
        status::CharacterStatus* player_;                           // 0x004
        int actionIndex_;                                           // 0x008
        int itemIndex_;                                             // 0x00C
        int effectValue_;                                           // 0x010
        short targetEffectValue_[MONSTER_MAX];                      // 0x014
        int targetCount_;                                           // 0x02C
        short targetActionDefence_[MONSTER_MAX];                    // 0x030
        int lastEffectValue_[MONSTER_MAX];                          // 0x048
        int targetGroupEffectValue_[5];                             // 0x078
        int targetGroupEffectValueCount_[5];                        // 0x08C
        int maxGroup_;                                              // 0x0A0
        int maxIndex_;                                              // 0x0A4
        short lastDamageRate_[MONSTER_MAX];                         // 0x0A8
        BattleSelectTargetParam battleSelectTargetParam_;           // 0x0C0

        static status::GameFlag actionFlag_[5];
        static int bossFlag_;
        static int turnCount_;

        AutoActionParam();
        ~AutoActionParam();
        void setup(int actionIndex, int itemIndex, status::CharacterStatus* player);
        void clear();
        virtual void setupTarget();
        virtual void calcEffectValue();
        virtual void calcEffectValueException();
        void calcActionDefence();
        void calcTargetEffectValue();
        virtual void calcCorrectEffectVelue();
        virtual void calcCorrectEffectVelueException();
        void calcGroupValue();
        void calcAllValue();
        virtual void calcTargetCount();
        void calcSelectGroup();
        void calcSelectIndex();
        int getSelectValue();
        int getActionIndex();
        int getAction();
        int getItem();
        int getSelectGroup();
        int getSelectIndex();
        int getDamageRatio();
        void setSelectGroup(int grp);
        void setSelectIndex(int idx);
        void enableTargetMahotone(int action, BattleSelectTargetParam& param);
        void enableTargetFubaha(int action, BattleSelectTargetParam& player, BattleSelectTargetParam& monster);
        void enableTargetMahokite(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player);
        void enableTargetInstantDeath(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player);
        void enableTargetRukaniRukanan(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player);
        void enableMpZeroTargetEnable(int action, BattleSelectTargetParam& param);
        bool checkTargetHaveMahotoneAction(int index, BattleSelectTargetParam& param);
        bool checkTargetHaveFubahaAction(int index, BattleSelectTargetParam& param);
        bool checkTargetHaveMahokiteAction(int index, BattleSelectTargetParam& param);
        bool checkTargetHaveInstantDeathAction(int index, BattleSelectTargetParam& param);
        bool checkTargetHaveRukaniRukanan(int index, BattleSelectTargetParam& param);
        void disableTarget2Count(int action, BattleSelectTargetParam& param);
        void disableTarget2CountInGroup(int group, int action, BattleSelectTargetParam& param);
        void disableOnceUse(int action, BattleSelectTargetParam& param);
        void disableOnceUseInGroup(int group, int action, BattleSelectTargetParam& param);
        void disableStatusChange(int action, dq5::level::ActionParam::ACTIONTYPE type, BattleSelectTargetParam& param);
        void disableStatusChange2(int action, dq5::level::ActionParam::ACTIONTYPE type, int action1, int action2, int action3, BattleSelectTargetParam& param);
        static void setFlag(int group, int actionIndex);
        static void clearFlag();
        static void setBossMode(bool flag);
        static int isBossMode();
        static void setTurnCount(int count);
    };

    struct AttackAutoActionParam : AutoActionParam {
        static int normalAttack_;
        static int normalAttackRatio_;
        static int attackActionRatio_;

        AttackAutoActionParam();
        ~AttackAutoActionParam();
        virtual void setupTarget();
        virtual void calcEffectValue();
        virtual void calcEffectValueException();
        virtual void calcCorrectEffectVelue();
        virtual void calcCorrectEffectVelueException();
        virtual void calcTargetCount();
        void calcCorrectEffectVelueMahokanta();
        void calcCorrectEffectVelueMahosute();
        static void setNormalAttack(bool flag);
        static void setNormalAttackRatio(int ratio);
        static void setAttackActionRatio(int ratio);
    };

    struct RecoveryAutoActionParam : AutoActionParam {
        RecoveryAutoActionParam();
        ~RecoveryAutoActionParam();
        virtual void setupTarget();
        virtual void calcEffectValue();
        virtual void calcEffectValueException();
        virtual void calcCorrectEffectVelue();
        virtual void calcCorrectEffectVelueException();
        virtual void calcTargetCount();
        bool isMemberHpDown(int persent);
        bool isMemberDeath();
        int getMemberSpazz();
        int getMemberPoison();
        int getMemberVenom();
    };

    struct DefenceAutoActionParam : AutoActionParam {
        DefenceAutoActionParam();
        ~DefenceAutoActionParam();
        virtual void setupTarget();
        virtual void calcEffectValue();
        virtual void calcEffectValueException();
        virtual void calcCorrectEffectVelue();
        void calcCorrectEffectValueForMonster();
        void calcCorrectEffectValueForPlayer();
        void calcCorrectEffectVelueMahokanta();
    };

    struct AssistAutoActionParam : AutoActionParam {
        AssistAutoActionParam();
        ~AssistAutoActionParam();
        virtual void setupTarget();
        virtual void calcEffectValue();
        virtual void calcEffectValueException();
        virtual void calcCorrectEffectVelue();
        void calcCorrectEffectValueForMonster();
        void calcCorrectEffectValueForPlayer();
        void calcCorrectEffectVelueMahokanta();
        void disableBaikiruto(BattleSelectTargetParam& player, BattleSelectTargetParam& monster);
    };

    struct AutoAction {
        static const int ACTION_MAX = 32;

        status::PlayerStatus* player_;                          // 0x0000
        int attackCount_;                                       // 0x0004
        int recoveryCount_;                                     // 0x0008
        int defenceCount_;                                      // 0x000C
        int assistCount_;                                       // 0x0010
        int attackMaxIndex_;                                    // 0x0014
        int recoveryMaxIndex_;                                  // 0x0018
        int defenceMaxIndex_;                                   // 0x001C
        int assistMaxIndex_;                                    // 0x0020
        AttackAutoActionParam attackActionParam_[ACTION_MAX];       // 0x0024
        RecoveryAutoActionParam recoveryActionParam_[ACTION_MAX];   // 0x2DA4
        DefenceAutoActionParam defenceActionParam_[ACTION_MAX];     // 0x5B24
        AssistAutoActionParam assistActionParam_[ACTION_MAX];       // 0x88A4
        int monsterLevel_;                                      // 0xB624
        int playerLevel_;                                       // 0xB628
        int turnCount_;                                         // 0xB62C
        int debugCount_;                                        // 0xB630
        int selectAction_;                                      // 0xB634
        int selectGroup_;                                       // 0xB638

        static int attackActionRatio_;

        AutoAction();
        ~AutoAction();
        void clear();
        void setup(status::PlayerStatus* player, int count, bool round);
        void setLevelDifference();
        void selectAction();
        void selectMaxAction();
        void setSelectAction();
        void setRandomAction();
        void add(int actionIndex, int itemIndex);
        bool validAction(int actionIndex);
        void setSelectAttackAction(bool flag);
        void setSelectRecoveryAction();
        void setSelectAssistAction();
        void setSelectDefenceAction();
        void setForceDefenceAction();
        void setDefenceAction();
        void setAssistAction();
        void setDebugAction();
        void setDebugDefenceAction();
        void setDebugConfuseAction();
        void setDebugNormalAttackAction(int count);
        void setDebugParupunteAction();
        void setRecoveryAction();
        void setRebirthAction();
        void setAntiSpazzAction();
        void setAntiPoisonAction();
        void setAntiVenomAction();
        void setAction(int actionIndex, int itemIndex, int groupIndex, int targetIndex);
    };

    extern AutoAction autoAction;
}

#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status
{
    struct CharacterStatus;

    struct BaseActionStatus {
        static const unsigned int FLAG_MP_ZERO = 0x20;

        static int effectValue_;
        static int playerEffectValue_;
        static int actionIndex_;
        static int meganteDamage_;
        static int poisonMessFlag_;
        static int dragoramMessFlag_;
        static int parameterDisable_;
        static int mahotoneMessFlag_;
        static int manusaMessFlag_;
        static int baikirutoMessFlag_;
        static int spazzMessFlag_;
        static int sleepMessFlag_;
        static int confusionMessFlag_;
        static int mahokantaMessFlag_;
        static int execCallKingSlime_;
        static int execCallFriend_;
        static int eventBattle_;
        static int work_;
        static dss::Flag flag_;
        static int monsterEffectValue_;

        static void clear();
        static void setActionIndex(int actionIndex);
        static void setEffectValue(int effectValue, int playerEffectValue, int monsterEffectValue);
        static int getEffectValue(CharacterStatus* target);
        static bool actionTypeDamage(CharacterStatus* actor, CharacterStatus* target);
        static bool actionTypeRecovery(CharacterStatus* target);
        static void actionTypeInstantDeath(CharacterStatus* target);
        static int actionTypeRebirth(CharacterStatus* target);
        static bool actionTypeAddMP(CharacterStatus* target);
        static bool actionTypeSubMP(CharacterStatus* actor, CharacterStatus* target);
        static bool actionTypeStatusClear(CharacterStatus* target);
        static int actionTypeCallFriend(CharacterStatus* target);
        static bool actionTypePartyReorder(CharacterStatus* target);
        static void actionTypeChangeTactics();
        static bool actionTypeDisappear(CharacterStatus* target);
        static bool actionTypeAddStrength(CharacterStatus* target);
        static bool actionTypeAddAgility(CharacterStatus* target);
        static bool actionTypeAddProtection(CharacterStatus* target);
        static bool actionTypeAddWisdom(CharacterStatus* target);
        static bool actionTypeAddMaxHp(CharacterStatus* target);
        static bool actionTypeAddMaxMp(CharacterStatus* target);
        static void actionTypeAstoron(CharacterStatus* target);
        static bool actionTypeSpazz(CharacterStatus* target);
        static bool actionTypeSleep(CharacterStatus* target);
        static void actionTypeManusa(CharacterStatus* target);
        static bool actionTypeBaikiruto(CharacterStatus* target);
        static bool actionTypeDefenceChange(CharacterStatus* target);
        static void actionTypeEerieLight(CharacterStatus* target);
        static void actionTypeFubaha(CharacterStatus* target);
        static void actionTypeMahokanta(CharacterStatus* target);
        static bool actionTypeMosyas(CharacterStatus* actor, CharacterStatus* target);
        static void actionTypePowerSave(CharacterStatus* target);
        static void actionTypeMahoton(CharacterStatus* target);
        static void actionTypeDragoram(CharacterStatus* target);
        static void actionTypeConfusion(CharacterStatus* target);
        static void actionTypePath1(CharacterStatus* target);
        static void actionTypePoison(CharacterStatus* target);
        static void actionTypeCloseDoor(CharacterStatus* target);
        static bool actionTypeCurse1(CharacterStatus* target);
        static bool actionTypeCurse2(CharacterStatus* target);
        static bool actionTypeCurse3(CharacterStatus* target);
        static bool actionTypeCurse4(CharacterStatus* target);
        static bool actionTypeCurse5(CharacterStatus* target);
        static void actionTypeMahokite(CharacterStatus* target);
        static void actionTypeDefence(CharacterStatus* target);
        static void actionTypeFizzleZone(CharacterStatus* target);
        static void actionTypeTimeStop(CharacterStatus* target);
        static bool actionTypeToherosu(CharacterStatus* target);
        static bool actionTypeSinobiasi(CharacterStatus* target);
        static bool actionTypeMonstersFood(CharacterStatus* target);
        static bool actionTypeMsgOnly(CharacterStatus* target);
        static bool actionTypeMsgSuccess();
        static bool actionTypeMsgFailed();
        static void statusChangeRelease(CharacterStatus* target);
        static int actionTypeNone(CharacterStatus* actor, CharacterStatus* target);
        static void characterClearOut(CharacterStatus* target, int drop);
        static void setMpZero(bool flag);
        static bool isMpZero();
        static bool checkFlag(unsigned int flag);
        static void removeFlag(unsigned int flag);
        static int getWork();
        static bool isMahokantaMessage();
        static void setMahokantaMessage(bool flag);
        static bool isConfusionMessage();
        static void setConfusionMessage(bool flag);
        static bool isSleepMessage();
        static void setSleepMessage(bool flag);
        static bool isBaikirutoMessage();
        static void setBaikirutoMessage(bool flag);
    };
} // namespace status

void unkfunc_unused_15();

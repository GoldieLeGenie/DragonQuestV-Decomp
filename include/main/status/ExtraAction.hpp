#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/CharacterStatus.hpp"

namespace status
{
    bool isNormalAttack(int actionIndex);
    bool isNormalAttackForSE(int actionIndex);
    bool isDoubleAction(CharacterStatus* actor, int actionIndex);
    bool isMultiTargetEquipment(CharacterStatus* actor);
    bool isGroupTargetEquipment(CharacterStatus* actor);
    bool isAllTargetEquipment(CharacterStatus* actor);
    int getUsuallyAttackEffectValue(CharacterStatus* actor, CharacterStatus* target);
    int getUsuallyAttackEffectValueForAI(CharacterStatus* actor, CharacterStatus* target);
    int getKaishinAttackEffectValue(CharacterStatus* actor, CharacterStatus* target);
    int getTsukon1AttackEffectValue(CharacterStatus* actor);
    int getTsukon2AttackEffectValue(CharacterStatus* actor);
    int getRandomVariation(int value, int under, int over);
    bool isExecRula();
    bool isExecRiremito();
    bool isExecImpas();
    bool isExecLanaruta();
    bool isExecFloomi();
    bool isExecToherosu();
    void initCallMonster();
    void addCallMonster(CharacterStatus* monster);
    int getCallMonsterCount();
    CharacterStatus* getCallMonsterStatus(int index);
    void setCallMonster(bool flag);
    int isCallMonster();
    bool callDifferentMonster(int monsterGroup, int monsterIndex);
    void checkCloseDoor(CharacterStatus* target);

    extern CharacterStatus* callMonsterStatus[12];
    extern int callMonsterIndex;
    extern int callMonsterCount;
    extern int callMonsterFlag;
    extern int metalSlimeBeforeIndex;
    extern int metalSlimeCount;
} // namespace status

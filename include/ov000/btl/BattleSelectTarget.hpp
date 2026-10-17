#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/UseAction.hpp"
#include "ov000/btl/BattleSelectTargetParam.hpp"

namespace status {
    struct CharacterStatus;
    struct UseActionParam;
}

namespace btl {
    struct BattleSelectTarget {
        static status::CharacterStatus* specialTarget_[8];

        static void setTarget(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call);
        static bool setTargetSet(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call);
        static status::UseAction::UseArea setWeaponArea(status::CharacterStatus* actor, int actionIndex);
        static int checkCurseSecond(status::CharacterStatus* actor, int actionIndex);
        static bool checkTurnSelectOne(BattleSelectTargetParam* targetParam);
        static bool checkTurnSelectGroup(BattleSelectTargetParam* targetParam);
        static bool checkTurnSelectAll(BattleSelectTargetParam* targetParam);
        static void setTargetPlayer(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetPlayerWithDeath(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetPlayerAll(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetPlayerAllWithDeath(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetMonster(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetMonsterWithDeath(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetStadiumMonster(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetPlayerAndMonster(BattleSelectTargetParam* targetParam, int playerMax, int monsterMax);
        static bool setTargetBoth(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetMyself(status::CharacterStatus* actor, BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetFriend(status::CharacterStatus* actor, int actionIndex, BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetEnemy(status::CharacterStatus* actor, int actionIndex, BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetNone(status::CharacterStatus* actor, BattleSelectTargetParam* battleSelectTargetParam);
        static void setNextAction(BattleSelectTargetParam* targetParam);
        static bool setTargetOne(BattleSelectTargetParam* battleSelectTargetParam);
        static bool setPersonalTarget(BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetGroup(BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetAll(BattleSelectTargetParam* battleSelectTargetParam);
        static bool setTargetAllWithCarriage(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetSpecial(status::UseActionParam* useActionParam);
        static void setTargetSpecialToPlayer(status::UseActionParam* useActionParam);
        static void setTargetSpecialToMonster(status::UseActionParam* useActionParam);
        static int setTargetSpecialToMonsterNoAstoron(int targetCount);
        static int setTargetSpecialToMonsterNoSleep(int targetCount);
        static int setTargetSpecialToMonsterNoSpazz2(int targetCount);
        static int setTargetSpecialToMonsterNoConfusion2(int targetCount);
        static int setTargetSpecialToMonsterNearDeath2(int targetCount);
        static int setTargetSpecialToMonsterHpMin2(int targetCount);
        static void setTargetSpecialToParam2(status::UseActionParam* useActionParam);
        static bool setTargetCrossFire(status::UseActionParam* useActionParam);
        static void setActorAction(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call);
        static bool checkStadiumAction(int actionIndex);
        static bool checkFriendTarget(BattleSelectTargetParam* targetParam);
    };
}

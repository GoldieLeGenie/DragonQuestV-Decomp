#pragma once
#include <globaldefs.h>

namespace status {
    struct CharacterStatus;
    struct UseActionParam;
}

namespace btl {
    struct BattleActorAnimation {
        static int airMaxHeight;
        static int groundMaxHeight;

        static int setExecAnimation(status::UseActionParam& useActionParam);
        static bool checkExecAnimation(status::UseActionParam& useActionParam);
        static bool checkNormalAnimation(status::UseActionParam& useActionParam);
        static void setResultAnimation(status::UseActionParam& useActionParam, int currentTarget);
        static void setDamangeDraw(status::CharacterStatus* target);
        static bool checkResultAnimation(status::UseActionParam& useActionParam, int currentTarget);
        static void setResultAnimationMonster(status::CharacterStatus* actor, status::CharacterStatus* target, int currentTarget, bool flag);
        static void setAfterAnimation(status::CharacterStatus* actor, status::CharacterStatus* target, int targetCount, int currentIndex);
        static void setMosyasSetup(status::UseActionParam* useActionParam);
        static void setMosyasChange(status::CharacterStatus* actor);
        static void setMosyasReverse(status::CharacterStatus* actor);
        static void setCallFriend(status::CharacterStatus* target);
        static void gattaiSlimeStart(status::CharacterStatus* actor, int actionIndex);
        static void gattaiSlime(status::CharacterStatus* actor, int actionIndex);
    };
}

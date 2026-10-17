#pragma once
#include <globaldefs.h>

namespace status
{
    struct UseActionParam;

    struct ActionCheckActor {
        static bool checkStatusRelease(UseActionParam* useActionParam);
        static void checkConfusion(UseActionParam* useActionParam);
        static void checkActorKaishin(UseActionParam* useActionParam);
        static void checkActorImmediateItem(UseActionParam* useActionParam);
        static bool isActionEnable(UseActionParam* useActionParam);
        static bool isCarriageInside(UseActionParam* useActionParam);
        static bool isAstoron(UseActionParam* useActionParam);
        static bool isSpazz(UseActionParam* useActionParam);
        static bool isSleep(UseActionParam* useActionParam);
        static bool isPath1(UseActionParam* useActionParam);
        static bool isTimeStop(UseActionParam* useActionParam);
        static bool isCloseDoor(UseActionParam* useActionParam);
        static bool isUseMp(UseActionParam* useActionParam);
        static bool isMahoton(UseActionParam* useActionParam);
        static bool isFizzleZone(UseActionParam* useActionParam);
        static bool isCurse(UseActionParam* useActionParam);
        static bool isMinadein(UseActionParam* useActionParam);
        static void useMp(UseActionParam* useActionParam);
        static bool isUseMpMyself(UseActionParam* useActionParam);
        static void checkActor(UseActionParam* useActionParam);
        static void checkPowerSave(UseActionParam* useActionParam);
        static void checkManusa(UseActionParam* useActionParam);
        static void checkBaikiruto(UseActionParam* useActionParam);
        static void checkEffectValue(UseActionParam* useActionParam);
        static void checkItemMissA(UseActionParam* useActionParam);
        static void checkItemMuchiB(UseActionParam* useActionParam);
        static void checkItemDamageC(UseActionParam* useActionParam);
        static void checkItemDamageD(UseActionParam* useActionParam);
        static void checkActionEnd(UseActionParam* useActionParam);
        static void checkItemRecoveryI(UseActionParam* useActionParam);
        static bool isAlive(UseActionParam* useActionParam);
    };
} // namespace status

#pragma once
#include <globaldefs.h>

namespace status
{
    struct CharacterStatus;
    struct UseActionParam;

    struct ActionCheckTarget {
        static void setTargetReSelect(UseActionParam* useActionParam);
        static CharacterStatus* checkTargetSpecialSelect(UseActionParam* useActionParam);
        static bool changeMahokantaTarget(UseActionParam* useActionParam);
        static bool checkTargetMahokanta(UseActionParam* useActionParam);
        static bool isActionEnable(UseActionParam* useActionParam);
        static bool isCarriageInside(UseActionParam* useActionParam);
        static bool checkZaoraruZaoriku(UseActionParam* useActionParam);
        static bool checkDeadOrAlive(UseActionParam* useActionParam);
        static void checkMpZero(UseActionParam* useActionParam);
        static void checkBaikiruto(UseActionParam* useActionParam);
        static bool checkAstoron(UseActionParam* useActionParam);
        static void checkFubaha(UseActionParam* useActionParam);
        static void checkDefence(UseActionParam* useActionParam);
        static bool checkJouk(UseActionParam* useActionParam);
        static bool checkSplitJouk(UseActionParam* useActionParam);
        static bool checkPoison(UseActionParam* useActionParam);
        static bool checkUseMp(UseActionParam* useActionParam);
        static void checkTarget(UseActionParam* useActionParam);
        static void checkActionEnd(UseActionParam* useActionParam);
        static void checkReleaseConfusionSleep(UseActionParam* useActionParam);
        static void checkReleaseItetsukuhadou(UseActionParam* useActionParam);
        static void checkMahokite(UseActionParam* useActionParam);
    };
} // namespace status

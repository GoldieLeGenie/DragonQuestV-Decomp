#pragma once
#include <globaldefs.h>

namespace status
{
    struct UseActionParam;

    struct ActionEffectValue {
        static int specialTargetEffectValue_;

        static void execActionDefence(UseActionParam* useActionParam);
        static void execActionDefenceBasic(UseActionParam* useActionParam);
        static void execActionDefenceException(UseActionParam* useActionParam);
        static void addActionDefence(UseActionParam* useActionParam, int ratio);
        static void clearEffectValue();
        static void setEffectValue(UseActionParam* useActionParam, bool flag);
        static void checkMultiAttack(UseActionParam* useActionParam);
        static void setEffectValueNormalAttack(UseActionParam* useActionParam);
        static void setEffectValueBasic(UseActionParam* useActionParam);
        static void setEffectValueAdd(UseActionParam* useActionParam, int ratio, int offset);
        static void execEffectValueWithEquipment(UseActionParam* useActionParam);
        static void setEffectValueWithEquipmentAttack(UseActionParam* useActionParam);
        static void setEffectValueWithEquipmentDefence(UseActionParam* useActionParam);
        static void setEffectValueWithEquipmentActionDefence(UseActionParam* useActionParam);
        static void setEffectValueException(UseActionParam* useActionParam);
        static void setEffectValueWithDoubleAttack(UseActionParam* useActionParam);
    };
} // namespace status

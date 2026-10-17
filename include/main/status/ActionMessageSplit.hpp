#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/UseActionMessage.hpp"

namespace status
{
    struct CharacterStatus;
    struct UseActionParam;

    struct ActionMessageSplit {
        static int splitFlag_;
        static int actionIndex_;
        static UseActionParam* useActionParam_;

        static int setSplitMessage(CharacterStatus* actor, CharacterStatus* target, UseActionMessage& useActionMessage, int actionIndex);
        static int setSplitMessage(CharacterStatus* actor, CharacterStatus* target, int mess);
        static int getMessagePlayerOne(CharacterStatus* target, int splitIndex);
        static int getMessagePlayerMany(CharacterStatus* target, int splitIndex);
        static int getMessagePlayerOneInCarriage(int splitIndex);
        static int getMessagePlayerManyInCarriage(int splitIndex);
        static int getMessageMonster1(UseActionParam* useActionParam, int splitIndex);
        static int getMessageMonster2(UseActionParam* useActionParam, int splitIndex);
        static int getMessageMonster1G(CharacterStatus* target, int splitIndex);
        static int getMessageMonster2G(CharacterStatus* target, int splitIndex);
        static int getMessageMonsterD(CharacterStatus* target, int splitIndex);
        static int getMessageTargetNoVenom(CharacterStatus* target, int splitIndex);
        static int getMessageTargetVenom(CharacterStatus* target, int splitIndex);
        static int getMessageTargetNoManusaAlready(CharacterStatus* target, int splitIndex);
        static int getMessageTargetManusaAlready(CharacterStatus* target, int splitIndex);
        static int getMessageTargetMpZero(CharacterStatus* target, int splitIndex);
        static int getMessageTargetMpNoZero(CharacterStatus* target, int splitIndex);
        static int getMessageTargetAlive(CharacterStatus* target, int splitIndex);
        static int getMessageTargetDead(CharacterStatus* target, int splitIndex);
        static int getMessageTargetAstoron(CharacterStatus* target, int splitIndex);
        static int getMessageTargetNoMosyasu(CharacterStatus* target, int splitIndex);
        static int getMessageTargetNoSplitNoJouk(CharacterStatus* target, int splitIndex);
        static int getMessageTargetSplit(CharacterStatus* target, int splitIndex);
        static int getMessageTargetJouk(CharacterStatus* target, int splitIndex);
        static int getMessageWeaponEquipment(CharacterStatus* actor, int splitIndex);
        static int getMessageNoWeaponEquipment(CharacterStatus* actor, int splitIndex);
        static int getMessageActorMale(CharacterStatus* actor, int splitIndex);
        static int getMessageActorFemale(CharacterStatus* actor, int splitIndex);
        static int getMessageActorHuman(CharacterStatus* actor, int splitIndex);
        static int getMessageActorMonster(CharacterStatus* actor, int splitIndex);
        static int getMessageTargetMale(CharacterStatus* target, int splitIndex);
        static int getMessageTargetFemale(CharacterStatus* target, int splitIndex);
        static int getMessageTargetHuman(CharacterStatus* target, int splitIndex);
        static int getMessageTargetMonster(CharacterStatus* target, int splitIndex);
        static int getMessageNotNextMap(int splitIndex);
        static int getMessageNoSpace(int splitIndex);
        static int getMessageNoUse(CharacterStatus* actor, int splitIndex);
        static int getMessageRulaOff(int splitIndex);
        static int getMessageRiremitoOff(int splitIndex);
        static int getMessageVainTimeZon(int splitIndex);
        static int getMessageItemInBox(int splitIndex);
        static int getMessageMonsterInBox(int splitIndex);
        static int getMessageGoldInBox(int splitIndex);
        static int getMessageZeroInBox(int splitIndex);
        static int getMessageItemInPot(int splitIndex);
        static int getMessageMonsterInPot(int splitIndex);
        static int getMessageGoldInPot(int splitIndex);
        static int getMessageZeroInPot(int splitIndex);
        static int getMessageNoTarget(int splitIndex);
        static int getMessageRandom(int splitIndex);
        static int getMessageZero(int splitIndex);
        static int getMessageSpecial(int splitIndex);
        static void setUseActionParam(UseActionParam* useActionParam);
    };
} // namespace status

#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/UseActionMessage.hpp"

namespace status
{
    struct CharacterStatus;
    struct UseActionParam;

    struct ActionMessage {
        static int instantDeath_;

        static void setInstantDeath(bool flag);
        static void setExecMessage(int actionIndex, UseActionMessage& useActionMessage);
        static void setResultMessage(int actionIndex, CharacterStatus& characterStatus, UseActionMessage& useActionMessage, int result);
        static int getExecMessage(int actionIndex, int index);
        static int getResultMessage(int actionIndex, CharacterType type, int result);
        static int getResultSuccessMessage(int actionIndex, CharacterType type);
        static int getResultFailedMessage(int actionIndex, CharacterType type);
        static int getFinishMessage(int actionIndex);
        static void setExecMessage(UseActionMessage& useActionMessage, int mes0, int mes1, int mes2, int mes3);
        static void setResultMessage(UseActionMessage& useActionMessage, int mes0, int mes1);
        static void setAddMessage(UseActionMessage& useActionMessage, int mes0, int mes1);
        static void setMessageNotEnoughMp(int actionIndex, UseActionMessage& useActionMessage);
        static void setExecMessageAdd(int actionIndex, UseActionMessage& useActionMessage);
        static void setExecMessageAdd(UseActionParam* useActionParam);
        static int getPlayerDeathMessage();
    };
} // namespace status

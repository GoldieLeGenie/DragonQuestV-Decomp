#pragma once
#include "main/menu/MenuBase.hpp"

namespace MenuAPI {
    void openMenuByIndex();
    void changeMenuModeNormal();
    void changeMenuModeExtra();
    int isMenuModeNormal();
    int isMenuModeExtra();
    void menuEnable(int enable);
    void openMenu(menu::MenuBase* menu);
    void closeMenu();
    int isFinishMenu();
    void clearMenuAll();
    void openTownMenu();
    int isTownMenuRoot();
    void openBattleMenu();
    void openFriendMenu();
    void setBattleBackDrop(unsigned short backDrop);
    void openBattleStadiumAbort();
    void closeBattleStadiumAbort();
    void openMessage(int message, int count);
    void openCommonMessage();
    void addCommonMessage(int message);
    void waitCommonMessage();
    void clearCommonMessage();
    bool isWaitMessage();
    int isMessageWaitTrigger();
    void clearMessageWaitTriggerSE();
    void clearMessageWaitTriggerNOSE();
    void openEncountMessage();
    void openBattleMessage();
    void addMessage(int message);
    void addMessageSerial(int message);
    void catMessage(int message);
    void shakeMessage();
    void setMessageCursor(bool flag);
    void openMessageWindowMenu();
    int isFinishMessageWindow();
    int isFinishMessage();
    int isEndMessage();
    void suspendMessageKeyInput(int flag);
    bool judgeReserveWord(char* name);
    int judgePartyName(char* name, int index);
    bool judgeRepeatWord(unsigned char* name);
    bool judgeOverlapWord(unsigned char* name);
}

const int* unkfunc_unused_MenuAPI();

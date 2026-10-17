#pragma once
#include "globaldefs.h"
#include "GameInfo.hpp"
#include "main/menu/MenuBase.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuDisplay.hpp"
#include "main/menu/UnkMessageWindow.hpp"
#include "main/menu/UnkMenuFaceDisplay.hpp"

struct TownMenu_MESSAGE : menu::MenuBase
{
    int pushKey_;                               // 0x1C  pad edge that closed the last page
    int keyEnable_;                             // 0x20
    int ynFlag_;                                // 0x24
    int ynExec_;                                // 0x28
    int ynCursor_;                              // 0x2C
    int ynPosX_;                                // 0x30
    int ynPosY_;                                // 0x34
    int ynSuperCancel_;                         // 0x38
    int suspendInput_;                          // 0x3C
    menu::MenuItem yesNoItem_;                  // 0x40
    int busyIcon_;                              // 0xA4
    int busyIconWait_;                          // 0xA8  frames before the busy icon shows
    eMessageWindow windowType_;                 // 0xAC

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();

    void openMessageForTALK();
    void openMessageForMENU();
    void openMessageForENCOUNT();
    void openMessageForBATTLE();
    void openMessageForBATTLESHOP();
    void openMessage(eMessageWindow type);
    void addMessageNOWAIT(int messageID);
    void addMessage(int messageID);
    void addMessage(int messageID1, int messageID2);
    void addMessage(int messageID1, int messageID2, int messageID3);
    void addMessageCount(int messageID, int count);
    void addMessageSerial(int messageID);
    void addMessage(const char* message);
    void setYesNo();
    void setYesNo(int cursor);
    void setYesNoSuperCancel(bool flag);
    void restartMessage();
    void addMessageWAITKEY();
    bool isMessageWAITPROG();
    void clearMessageWAITPROG();
    void setMessageCursor(bool flag);
    void setMessageIntervalCursor(bool flag);
    void setMessageLastCursor(bool flag);
    void setBusyIcon(bool flag);
};

extern TownMenu_MESSAGE gTownMenu_MESSAGE;

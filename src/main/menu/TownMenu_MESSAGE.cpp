#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/dss/Pad.hpp"
#include "main/menu/CommonMenu_YESNO.hpp"
#include "main/status/GameStatus.hpp"
#include "main/debug/DebugInfo.hpp"

static MENUITEM_DATA yesNoItemData[] = {
    {1, 2, 0, 0, 0x100, 0xc0},
    {-1, -1, 0, 0, 0, 0},
};

THUMB void TownMenu_MESSAGE::menuSetup()
{
    yesNoItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    keyEnable_ = 0;
    ynFlag_ = 0;
    ynExec_ = 0;
    ynPosX_ = 0xc0;
    ynPosY_ = 0x40;
    ynSuperCancel_ = 1;
    suspendInput_ = 0;
    busyIcon_ = 0;
    busyIconWait_ = 0;
    data_020c2d10.unkfunc_02027cdc();
}

THUMB void TownMenu_MESSAGE::menuExecute()
{
    if (ynExec_ == 0) {
        yesNoItem_.setMenuItem(yesNoItemData, 1, 1, 1);
    }
    if (busyIcon_ != 0) {
        MenuFaceDisplay* const busy = &data_02114dd4.face_;
        busy->mode_ = 11;
        busy->setPriority(0);
        busy->setPosition(0xe0, 0x164);
        busy->setEnable(1);
    }
}

THUMB void TownMenu_MESSAGE::menuDraw()
{
    s_draw->setEnable(1);
    if (windowType_ == UNK_MESSAGE_WINDOW_7) {
        unkfunc_02061c5c(0, 0);
        UnkMenuParts parts[] = {
            {3, 0xd0, (short)0xf000, 0, 0, 0, 0x100, 0xc0},
            {0xff},
        };
        unkfunc_0206297c(parts, 0);
    }
    if (busyIconWait_ != 0) {
        busyIconWait_--;
        if (busyIconWait_ == 0) {
            busyIcon_ = 1;
        }
    }
}

THUMB void TownMenu_MESSAGE::menuUpdate()
{
    if (frame_ >= 2 && suspendInput_ == 0) {
        if (ynExec_ == 0) {
            yesNoItem_.result_ = 0;
            yesNoItem_.lastresult_ = 0;
            yesNoItem_.execInput();
            int key = 0;
            int pushKey = 0;
            if ((dss::g_Pad.edge() & 0x1) || (dss::g_Pad.edge() & 0x2) ||
                (dss::g_Pad.edge() & 0x400) || (dss::g_Pad.edge() & 0x800) ||
                (dss::g_Pad.edge() & 0x40) || (dss::g_Pad.edge() & 0x10) ||
                (dss::g_Pad.edge() & 0x80) || (dss::g_Pad.edge() & 0x20) ||
                (dss::g_Pad.edge() & 0x200) || (dss::g_Pad.edge() & 0x100)) {
                key = 1;
                pushKey = dss::g_Pad.edge();
            }
            if (keyEnable_ != 0) {
                if (ynFlag_ != 0) {
                    if (s_draw->unkfunc_02066b74() && key == 1) {
                        s_draw->unkfunc_02066bc4();
                        keyEnable_ = 0;
                    }
                    if (s_draw->unkfunc_02066b88()) {
                        data_020a2b04.open();
                        data_020a2b04.setYesNo(ynCursor_);
                        data_020a2b04.setPosition(ynPosX_, ynPosY_);
                        data_020a2b04.setSuperCancel(ynSuperCancel_);
                        ynExec_ = 1;
                        keyEnable_ = 0;
                    }
                } else {
                    if (s_draw->unkfunc_02066b74() && key == 1) {
                        s_draw->unkfunc_02066bc4();
                        keyEnable_ = 0;
                    }
                    if (s_draw->unkfunc_02066b88() && key == 1) {
                        s_draw->unkfunc_02066bc4();
                        keyEnable_ = 0;
                        pushKey_ = pushKey;
                    }
                }
            } else {
                if (s_draw->unkfunc_02066b74() && key == 0) {
                    keyEnable_ = 1;
                }
                if (s_draw->unkfunc_02066b88() && key == 0) {
                    keyEnable_ = 1;
                }
            }
            if (s_draw->unkfunc_02066b9c()) {
                stat_ = MENUBASE_STAT_OK;
            }
        } else {
            if (data_020a2b04.stat_ == MENUBASE_STAT_OK) {
                stat_ = MENUBASE_STAT_OK;
            }
            if (data_020a2b04.stat_ == MENUBASE_STAT_CANCEL) {
                stat_ = MENUBASE_STAT_CANCEL;
            }
        }
    }
}

THUMB void TownMenu_MESSAGE::openMessageForTALK()
{
    openMessage(TALK_MESSAGE_WINDOW);
}

THUMB void TownMenu_MESSAGE::openMessageForMENU()
{
    openMessage(MENU_MESSAGE_WINDOW);
}

THUMB void TownMenu_MESSAGE::openMessageForENCOUNT()
{
    openMessage(ENCOUNT_MESSAGE_WINDOW);
}

THUMB void TownMenu_MESSAGE::openMessageForBATTLE()
{
    openMessage(BATTLE_MESSAGE_WINDOW);
}

THUMB void TownMenu_MESSAGE::openMessageForBATTLESHOP()
{
    openMessage(UNK_MESSAGE_WINDOW_7);
}

THUMB void TownMenu_MESSAGE::openMessage(eMessageWindow type)
{
    int language = 0;
    if (status::g_Game.language_ == Japanese) {
        language = 0;
    }
    if (status::g_Game.language_ == English) {
        language = 1;
    }
    if (status::g_Game.language_ == French) {
        language = 2;
    }
    if (status::g_Game.language_ == German) {
        language = 3;
    }
    if (status::g_Game.language_ == Italian) {
        language = 4;
    }
    if (status::g_Game.language_ == Spanish) {
        language = 5;
    }
    ui_MsgSetup(type, language);
    open();
    suspendInput_ = 0;
    windowType_ = type;
}

THUMB void TownMenu_MESSAGE::addMessageNOWAIT(int messageID)
{
    ui_MsgAdd(messageID);
    data_020c2d10.addMessageID(messageID);
}

THUMB void TownMenu_MESSAGE::addMessage(int messageID)
{
    if (messageID > 2000000) {
        addMessage((const char*)messageID);
        return;
    }
    ui_MsgAdd(messageID);
    ui_MsgAddWaitTrigger();
    data_020c2d10.addMessageID(messageID);
}

THUMB void TownMenu_MESSAGE::addMessage(int messageID1, int messageID2)
{
    addMessage(messageID1);
    addMessage(messageID2);
}

THUMB void TownMenu_MESSAGE::addMessage(int messageID1, int messageID2, int messageID3)
{
    addMessage(messageID1);
    addMessage(messageID2);
    addMessage(messageID3);
}

THUMB void TownMenu_MESSAGE::addMessageCount(int messageID, int count)
{
    for (int i = 0; i < count; i++) {
        addMessage(messageID + i);
    }
}

THUMB void TownMenu_MESSAGE::addMessageSerial(int messageID)
{
    int count = ui_MsgAddSerial(messageID);
    for (int i = 0; i < count; i++) {
        data_020c2d10.addMessageID(messageID + i);
    }
}

THUMB void TownMenu_MESSAGE::addMessage(const char* message)
{
    ui_MsgAdd(message);
    ui_MsgAddWaitTrigger();
    data_020c2d10.addMessageID(99999999);
}

THUMB void TownMenu_MESSAGE::setYesNo()
{
    ynFlag_ = 1;
    ynCursor_ = 0;
}

THUMB void TownMenu_MESSAGE::setYesNo(int cursor)
{
    ynFlag_ = 1;
    ynCursor_ = cursor;
}

THUMB void TownMenu_MESSAGE::setYesNoSuperCancel(bool flag)
{
    ynSuperCancel_ = flag;
}

THUMB void TownMenu_MESSAGE::restartMessage()
{
    stat_ = MENUBASE_STAT_ACTIVE;
    keyEnable_ = 0;
    ynFlag_ = 0;
    ynExec_ = 0;
    ynPosX_ = 0xc0;
    ynPosY_ = 0x40;
    s_draw->unkfunc_02066b48();
    s_msgCount = 0;
    data_020c2d10.unkfunc_02027cdc();
}

THUMB void TownMenu_MESSAGE::addMessageWAITKEY()
{
    ui_MsgAddWait();
}

THUMB bool TownMenu_MESSAGE::isMessageWAITPROG()
{
    return s_draw->unkfunc_02066bb0();
}

THUMB void TownMenu_MESSAGE::clearMessageWAITPROG()
{
    s_draw->unkfunc_02066be8(0);
}

THUMB void TownMenu_MESSAGE::setMessageCursor(bool flag)
{
    s_draw->intervalCursor_ = flag;
    s_draw->lastCursor_ = flag;
}

THUMB void TownMenu_MESSAGE::setMessageIntervalCursor(bool flag)
{
    s_draw->intervalCursor_ = flag;
}

THUMB void TownMenu_MESSAGE::setMessageLastCursor(bool flag)
{
    s_draw->lastCursor_ = flag;
}

THUMB void TownMenu_MESSAGE::setBusyIcon(bool flag)
{
    MenuFaceDisplay* const busy = &data_02114dd4.face_;
    if (flag) {
        busyIconWait_ = 2;
        busy->unkfunc_02064c80();
        busy->mode_ = 11;
        busy->setPriority(0);
        busy->setPosition(0xe0, 0x164);
        busy->setEnable(0);
        return;
    }
    busy->mode_ = 0;
    busy->setEnable(0);
    busyIcon_ = 0;
}

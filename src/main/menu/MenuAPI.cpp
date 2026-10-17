#pragma ipa file
#include "main/menu/MenuAPI.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkCommonMenuApitest.hpp"
#include "main/menu/CommonMenu_YESNO.hpp"
#include "main/menu/MenuManager.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov018/menu/BattleMenu.hpp"
#include "ov012/materielmenu/MaterielMenuPokerBetcoin.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"

static char* s_menuName[] = {
    0,
    "gCommonMenu_APITEST",
    "gTownMenu_ROOT",
    "gTownMenu_MESSAGE",
    "gCmmonMenu_YESNO",
    "gTownMenu_TOWN",
    "gMaterielMenu_POKER",
};

static int s_menuIndex;
static menu::MenuBase* s_rootmenu;

static const int unk_unused_MenuAPI = 0;

THUMB void MenuAPI::unkfunc_020199cc()
{
    char* name = 0;
    if (s_menuIndex != 0) {
        name = s_menuName[s_menuIndex];
    }
    if (name != 0) {
        menu::MenuBase* menu = 0;
        if (dss::strcmp(name, "gCommonMenu_APITEST") == 0) {
            menu = &data_020a2ae8;
        }
        if (dss::strcmp(name, "gTownMenuRoot") == 0) {
            menu = &gTownMenu_ROOT;
        }
        if (dss::strcmp(name, "gTownMenu_MESSAGE") == 0) {
            menu = &gTownMenu_MESSAGE;
        }
        if (dss::strcmp(name, "gCommonMenu_YESNO") == 0) {
            menu = &data_020a2b04;
        }
        if (dss::strcmp(name, "gMaterielMenu_POKER_BETCOIN") == 0) {
            menu = &gMaterielMenu_POKER_BETCOIN;
        }
        if (menu != 0) {
            clearMenuAll();
            openMenu(menu);
        }
    }
}

THUMB void MenuAPI::changeMenuModeNormal()
{
    clearMenuAll();
    MenuManager::requestMenuMode(MENUDISPLAY_NORMAL);
}

THUMB void MenuAPI::changeMenuModeExtra()
{
    clearMenuAll();
    MenuManager::requestMenuMode(MENUDISPLAY_EXTRA);
}

THUMB int MenuAPI::isMenuModeNormal()
{
    return MenuManager::isMenuMode(MENUDISPLAY_NORMAL);
}

THUMB int MenuAPI::isMenuModeExtra()
{
    return MenuManager::isMenuMode(MENUDISPLAY_EXTRA);
}

THUMB void MenuAPI::menuEnable(int enable)
{
    MenuManager::setMenuEnable(enable);
}

THUMB void MenuAPI::openMenu(menu::MenuBase* menu)
{
    clearMenuAll();
    s_rootmenu = menu;
    menu->open();
}

THUMB void MenuAPI::closeMenu()
{
    s_rootmenu->close();
    s_rootmenu = 0;
}

THUMB int MenuAPI::isFinishMenu()
{
    if (s_rootmenu == 0) {
        return true;
    }
    if (s_rootmenu->stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        return true;
    }
    if (s_rootmenu->stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
        return true;
    }
    return false;
}

THUMB void MenuAPI::clearMenuAll()
{
    MenuManager::clearMenuAll();
    s_rootmenu = 0;
}

THUMB void MenuAPI::openTownMenu()
{
    if (s_menuIndex != 0) {
        unkfunc_020199cc();
    } else {
        openMenu(&gTownMenu_ROOT);
    }
}

THUMB int MenuAPI::isTownMenuRoot()
{
    if (s_rootmenu == &gTownMenu_ROOT) {
        return true;
    }
    return false;
}

THUMB void MenuAPI::openBattleMenu()
{
    btl::BattleMonsterMask::getSingleton()->setup();
    BattleMenuJudge::getSingleton()->baseSetup();
    openMenu(&gBattleMenu_ROOT);
}

THUMB void MenuAPI::openFriendMenu()
{
    BattleMenuPlayerControl::getSingleton()->allClear();
    openMenu(&gBattleMenu_FRIEND_ENTRANCE);
}

THUMB void MenuAPI::setBattleBackDrop(unsigned short backDrop)
{
    unkfunc_0204ccdc(backDrop);
}

THUMB void MenuAPI::openBattleStadiumAbort()
{
    gBattleMenu_StadiumAbort.open();
    gBattleMenu_StadiumAbort.menuSetup();
}

THUMB void MenuAPI::closeBattleStadiumAbort()
{
    gBattleMenu_StadiumAbort.close();
}

THUMB void MenuAPI::openMessage(int message, int count)
{
    openMenu(&gTownMenu_MESSAGE);
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageCount(message, count);
}

THUMB void MenuAPI::openCommonMessage()
{
    openMenu(&gTownMenu_MESSAGE);
    gTownMenu_MESSAGE.openMessageForTALK();
}

THUMB void MenuAPI::addCommonMessage(int message)
{
    gTownMenu_MESSAGE.addMessage(message);
}

THUMB void MenuAPI::waitCommonMessage()
{
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void MenuAPI::clearCommonMessage()
{
    gTownMenu_MESSAGE.clearMessageWAITPROG();
}

THUMB bool MenuAPI::isWaitMessage()
{
    return gTownMenu_MESSAGE.isMessageWAITPROG();
}

THUMB int MenuAPI::isMessageWaitTrigger()
{
    return s_draw->unkfunc_02066b74();
}

THUMB void MenuAPI::clearMessageWaitTriggerSE()
{
    s_draw->unkfunc_02066bc4();
}

THUMB void MenuAPI::clearMessageWaitTriggerNOSE()
{
    s_draw->unkfunc_02066bd4();
}

THUMB void MenuAPI::openEncountMessage()
{
    openMenu(&gTownMenu_MESSAGE);
    gTownMenu_MESSAGE.openMessageForENCOUNT();
    if (g_StadiumData.stadiumFlag_ == 0) {
        gBattleMenuSub_HISTORY.open();
        gBattleMenuSub_HISTORY.history_ = 0;
    }
}

THUMB void MenuAPI::openBattleMessage()
{
    int abort = gBattleMenu_StadiumAbort.isOpen();
    openMenu(&gTownMenu_MESSAGE);
    gTownMenu_MESSAGE.openMessageForBATTLE();
    if (g_StadiumData.stadiumFlag_ == 0) {
        gBattleMenuSub_HISTORY.open();
        gBattleMenuSub_HISTORY.history_ = 1;
        if (abort) {
            gBattleMenu_StadiumAbort.open();
        }
    }
}

THUMB void MenuAPI::addMessage(int message)
{
    gTownMenu_MESSAGE.addMessage(message);
}

THUMB void MenuAPI::addMessageSerial(int message)
{
    gTownMenu_MESSAGE.addMessageSerial(message);
}

THUMB void MenuAPI::catMessage(int message)
{
    gTownMenu_MESSAGE.addMessageNOWAIT(message);
}

THUMB void MenuAPI::shakeMessage()
{
    UnkMessageWindow* window = s_draw;
    window->shake_ = 1;
    window->shakeCount_ = 0;
    window->shakeRepeat_ = 1;
}

THUMB void MenuAPI::setMessageCursor(bool flag)
{
    gTownMenu_MESSAGE.setMessageIntervalCursor(flag);
    gTownMenu_MESSAGE.setMessageLastCursor(flag);
}

THUMB void MenuAPI::openMessageWindowMenu()
{
    gTownMenu_MESSAGE.openMessageForMENU();
}

THUMB int MenuAPI::isFinishMessageWindow()
{
    if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        return true;
    }
    if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
        return true;
    }
    return false;
}

THUMB int MenuAPI::isFinishMessage()
{
    return s_draw->unkfunc_02066b88();
}

THUMB int MenuAPI::isEndMessage()
{
    return s_draw->unkfunc_02066b9c();
}

THUMB void MenuAPI::suspendMessageKeyInput(int flag)
{
    gTownMenu_MESSAGE.suspendInput_ = flag;
}

THUMB bool MenuAPI::judgeReserveWord(char* name)
{
    if (judgePartyName(name, 2)) {
        return true;
    }
    if (judgePartyName(name, 3)) {
        return true;
    }
    if (judgePartyName(name, 4)) {
        return true;
    }
    if (judgePartyName(name, 5)) {
        return true;
    }
    if (judgePartyName(name, 6)) {
        return true;
    }
    if (judgePartyName(name, 7)) {
        return true;
    }
    if (judgePartyName(name, 8)) {
        return true;
    }
    if (judgePartyName(name, 9)) {
        return true;
    }
    if (judgePartyName(name, 10)) {
        return true;
    }
    if (judgePartyName(name, 11)) {
        return true;
    }
    if (judgePartyName(name, 12)) {
        return true;
    }
    if (judgePartyName(name, 15)) {
        return true;
    }
    if (judgePartyName(name, 0x3b)) {
        return true;
    }
    if (judgePartyName(name, 0x52)) {
        return true;
    }
    return false;
}

THUMB int MenuAPI::judgePartyName(char* name, int index)
{
    char text[0x200];
    TextAPI::extractText(text, sizeof(text), 0x50000000, index + 0x1f4);
    if (dss::strcmp(name, text) == 0) {
        return true;
    }
    return false;
}

THUMB bool MenuAPI::judgeRepeatWord(unsigned char* name)
{
    if (TextAPI::m_lang != 0) {
        return false;
    }
    int count = 0;
    UnkUtf8Iterator it;
    it.unkfunc_0204a800((const char*)name);
    unsigned short first = it.unkfunc_0204a990();
    if (first != 0) {
        unsigned short c;
        do {
            c = it.unkfunc_0204a990();
            it.unkfunc_0204a9ec();
            if (c != first) {
                break;
            }
            count++;
            if (count >= 4) {
                return true;
            }
        } while (c != 0);
    }
    return false;
}

THUMB bool MenuAPI::judgeOverlapWord(unsigned char* name)
{
    status::g_Party.setBattleModeAndCarriage();
    bool overlap = false;
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (dss::strcmp(status::PlayerDataAll::playerData_[status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerIndex_].name_, (const char*)name) == 0) {
            overlap = true;
            break;
        }
    }
    if (!overlap) {
        for (int i = 0; i < 0x10; i++) {
            if (status::PlayerDataAll::isRuidaFlag(i) == true && dss::strcmp(status::PlayerDataAll::playerData_[i].name_, (const char*)name) == 0) {
                overlap = true;
                break;
            }
        }
    }
    if (!overlap) {
        for (int i = 0x10; i < 0x58; i++) {
            if (status::PlayerDataAll::isMonsterOldManFlag(i) == true && dss::strcmp(status::PlayerDataAll::playerData_[i].name_, (const char*)name) == 0) {
                overlap = true;
                break;
            }
        }
    }
    return overlap;
}

THUMB const int* unkfunc_unused_MenuAPI()
{
    return &unk_unused_MenuAPI;
}

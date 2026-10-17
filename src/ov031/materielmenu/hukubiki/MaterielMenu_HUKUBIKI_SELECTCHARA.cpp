#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_SELECTCHARA.hpp"
#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_ROOT.hpp"
#include "ov031/leveldata/HukubikiMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_HUKUBIKI_ROOT::setRetryHukubiki()
{
    retryHukubiki_ = 1;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

inline dq5::level::HukubikiMessage* dq5::level::HukubikiMessage::getRecord(int index)
{
    return (HukubikiMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::HukubikiMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    partyCount_ = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1;
    navigator_.setupBase();
    navigator_.setup(5, 2, partyCount_);
    ticketCount_ = gMaterielMenu_HUKUBIKI_ROOT.getTicket(true);
    mode_ = MODE_NONE;
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2(&menuItem_, menuItem_.active_, partyCount_);
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::menuDraw()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217be90(0, prize_);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
        }
        return;
    }
    navigator_.setup(5, 2, partyCount_);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        if (result == 3) {
            showMessage(12, 0, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CHACK_1;
        }
        if (result == 2) {
            selectChara();
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::selectYes()
{
    switch (mode_) {
        case MODE_CHACK_1:
            showMessage(13, 0, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CHACK_2;
            break;
        case MODE_CHACK_2:
            showRetryMessage(14, 0);
            break;
        case MODE_RETRY:
            close();
            gMaterielMenu_HUKUBIKI_ROOT.open();
            gMaterielMenu_HUKUBIKI_ROOT.setRetryHukubiki();
            break;
        case MODE_SORT:
            haveMaxItem();
            break;
        case MODE_SELECT_CHARA:
            showMessage(11, 0, 0, 0);
            mode_ = MODE_NONE;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::selectNo()
{
    switch (mode_) {
        case MODE_CHACK_1:
        case MODE_CHACK_2:
            showMessage(11, 0, 0, 0);
            mode_ = MODE_NONE;
            break;
        case MODE_RETRY:
            showMessage(29, 0, 0, 0);
            mode_ = MODE_END;
            break;
        case MODE_SORT:
            showMessage(19, 0, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_SELECT_CHARA;
            break;
        case MODE_SELECT_CHARA:
            showMessage(12, 0, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CHACK_1;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::selectChara()
{
    int active = menuItem_.active_;
    if (active == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        MenuStatusInfo::addFukuroItem(prize_, 1);
        showRetryMessage(15, 0);
    }
    else if (MenuStatusInfo::getPlayerItemCount(active) == 12) {
        showMessage(16, 0, 0, 0);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = MODE_SORT;
    }
    else {
        showGetPrizeMessage(0);
    }
    if (prize_ == 0xfd) {
        status::g_Story.setGoldCard(true);
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::haveMaxItem()
{
    int active = menuItem_.active_;
    if (MenuStatusInfo::isPlayerItemSort(active) == true) {
        MenuStatusInfo::sortPlayerItem(active);
        MenuStatusInfo::addPlayerItem(active, prize_);
        showRetryMessage(17, 0);
    }
    else {
        showMessage(18, 19, 0, 0);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = MODE_SELECT_CHARA;
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::showGetPrizeMessage(int first)
{
    int active = menuItem_.active_;
    MenuStatusInfo::addPlayerItem(active, prize_);
    int mes1;
    if (MenuStatusInfo::isCarriagePosition(active, MenuStatusInfo::POSITION_CARRIAGE_IN) == true) {
        mes1 = 26;
    }
    else if (MenuStatusInfo::isPlayerCondition(active, MenuStatusInfo::CONDITION_DEATH) == true) {
        mes1 = 25;
    }
    else {
        mes1 = 24;
    }
    if (first != 0) {
        showRetryMessage(first, mes1);
    }
    else {
        showRetryMessage(mes1, 0);
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::showRetryMessage(int first, int second)
{
    int mes3 = 0;
    int mes2;
    if (ticketCount_ == 0) {
        mes2 = 28;
        mes3 = 29;
    }
    else {
        mes2 = 27;
    }
    if (second == 0) {
        showMessage(first, mes2, mes3, 0);
    }
    else {
        showMessage(first, second, mes2, mes3);
    }
    if (ticketCount_ == 0) {
        mode_ = MODE_END;
    }
    else {
        gTownMenu_MESSAGE.setYesNo();
        mode_ = MODE_RETRY;
    }
}

THUMB void MaterielMenu_HUKUBIKI_SELECTCHARA::showMessage(int mes1, int mes2, int mes3, int mes4)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    int active = menuItem_.active_;
    if (active < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(menuItem_.active_));
    }
    TextAPI::setMACRO0(0x72, 0xf0000000, ticketCount_);
    gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes1)->getMessage1());
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes2)->getMessage1());
    }
    if (mes3 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes3)->getMessage1());
    }
    if (mes4 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes4)->getMessage1());
    }
}

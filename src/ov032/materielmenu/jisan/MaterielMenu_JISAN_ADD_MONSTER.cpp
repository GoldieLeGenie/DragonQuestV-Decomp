#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ADD_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_JISAN_ROOT::setActiveMenu(char select)
{
    active_ = select;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 1;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    mode_ = MODE_INIT;
    if (status::g_Menu.returnMenuType_ != 0) {
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.returnMenuType_ = 0;
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Menu.targetIndex_);
        gTownMenu_MESSAGE.addMessage(getMessageNo(0x18));
        status::g_Menu.drawFlag_ = 0;
        if (status::g_Menu.addMessageFlag_ == 1) {
            if (MenuStatusInfo::isPlayerCondition(MenuStatusInfo::getPlayerSortIndex(status::g_Menu.targetIndex_), MenuStatusInfo::CONDITION_DEATH) == true) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x4a));
            }
            else {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x19));
            }
        }
        ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(cmn::g_cmnPartyInfo.ctrlID_));
        status::g_Menu.targetIndex_ = 0;
        status::g_Menu.addMessageFlag_ = 0;
        mode_ = MODE_RETURN;
    }
    status::g_Menu.drawFlag_ = 1;
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::menuExecute()
{
    unkfunc_0201c904(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int page = navigator_.getPageNo();
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c3dc(page, pageMax, 1, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            messageUpdate();
        }
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(navigator_.getIndex(menuItem_.active_));
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
            mode_ = MODE_BOOKING;
        }
        if (result == 2) {
            int index = navigator_.getIndex(menuItem_.active_);
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(index));
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x17));
            mode_ = MODE_SELECT;
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::messageUpdate()
{
    gTownMenu_MESSAGE.close();
    switch (mode_) {
        case MODE_SELECT: {
            int index = navigator_.getIndex(menuItem_.active_);
            int ctrl = status::PlayerDataAll::getMonsterCtrlInOldMan(index);
            status::g_Menu.drawFlag_ = 0;
            if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT) == 4) {
                status::g_Menu.addMessageFlag_ = 1;
            }
            status::g_Menu.drawFlag_ = 1;
            status::g_Menu.targetIndex_ = MenuStatusInfo::getPlayerIndex(index);
            status::g_Menu.bookingFlag_ = menu::BOOKING_JISAN;
            status::g_Menu.returnMenuType_ = 1;
            MenuStatusInfo::addPlayer(ctrl);
            status::PlayerDataAll::setMonsterOldManFlag(ctrl, false);
            cmn::GameManager::getSingleton().resetParty();
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        }
        case MODE_RETURN: {
            status::g_Menu.drawFlag_ = 0;
            int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
            status::g_Menu.drawFlag_ = 1;
            int monsterCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
            if (partyCount < 8 && MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) > 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x1a));
                mode_ = MODE_INIT;
                return;
            }
            returnRoot();
            break;
        }
        case MODE_BOOKING:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_JISAN_ADD_MONSTER::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_JISAN_ROOT.setActiveMenu(0);
    gMaterielMenu_JISAN_ROOT.open();
}

THUMB int MaterielMenu_JISAN_ADD_MONSTER::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

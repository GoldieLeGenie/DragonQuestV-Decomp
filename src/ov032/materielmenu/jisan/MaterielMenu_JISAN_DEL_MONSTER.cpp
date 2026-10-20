#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_DEL_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/GameFlag.hpp"
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

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 1;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    mode_ = MODE_SELECT;
    activeChara_ = 0;
    systemMessage_[0] = 0;
    systemMessage_[1] = 0;
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int page = navigator_.getPageNo();
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c3dc(page, pageMax, 3, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
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
            return;
        }
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        activeChara_ = navigator_.getIndex(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(activeChara_);
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
            mode_ = MODE_END;
        }
        if (result == 2) {
            int index = MenuStatusInfo::getPlayerIndex(activeChara_);
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, index);
            if (MenuStatusInfo::getPlayerData(activeChara_).getKindIndex() == 0x11) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x24));
                mode_ = MODE_END;
            }
            else if (MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x26));
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x27));
                gTownMenu_MESSAGE.setYesNo(1);
                mode_ = MODE_DEATH;
                systemMessage_[0] = getMessageNo(0x2a);
                systemMessage_[1] = getMessageNo(0x2b);
            }
            else {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x25));
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x27));
                gTownMenu_MESSAGE.setYesNo(1);
                mode_ = MODE_ALIVE;
                systemMessage_[0] = getMessageNo(0x28);
                systemMessage_[1] = getMessageNo(0x29);
            }
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::selectYes()
{
    switch (mode_) {
        case MODE_DEATH:
        case MODE_ALIVE: {
            switch (MenuStatusInfo::getPlayerData(activeChara_).getKindIndex()) {
                case 0x3a:
                    g_AreaFlag.remove(0x22a);
                    break;
                case 0x3b:
                    g_AreaFlag.set(0x22b);
                    break;
                case 0x52:
                    g_AreaFlag.remove(0x190);
                    break;
            }
            cmn::g_talkSound.setOrderMessage(0x32);
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(2, -1);
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
            gTownMenu_MESSAGE.addMessage(systemMessage_[0], systemMessage_[1]);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(cmn::g_cmnPartyInfo.ctrlID_));
            int itemCount = MenuStatusInfo::getPlayerItemCount(activeChara_);
            for (int i = 0; i < itemCount; i++) {
                MenuStatusInfo::addFukuroItem(MenuStatusInfo::getPlayerItemID(activeChara_, 0), 1);
                MenuStatusInfo::throwPlayerItem(activeChara_, 0);
                if (MenuStatusInfo::getPlayerItemCount(activeChara_) == 0) {
                    break;
                }
            }
            int ctrl = status::PlayerDataAll::getMonsterCtrlInOldMan(activeChara_);
            status::PlayerDataAll::delFriendMonster(ctrl);
            status::PlayerDataAll::setMonsterOldManFlag(ctrl, false);
            mode_ = MODE_END;
            break;
        }
        case MODE_END:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::selectNo()
{
    switch (mode_) {
        case MODE_DEATH:
        case MODE_ALIVE:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
            mode_ = MODE_END;
            break;
    }
}

THUMB void MaterielMenu_JISAN_DEL_MONSTER::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_JISAN_ROOT.setActiveMenu(0);
    gMaterielMenu_JISAN_ROOT.open();
}

THUMB int MaterielMenu_JISAN_DEL_MONSTER::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

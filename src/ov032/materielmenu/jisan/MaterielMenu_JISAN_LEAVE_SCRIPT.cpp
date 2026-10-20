#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_SCRIPT.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_JISAN_LEAVE_SCRIPT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    for (int i = 0; i < 8; i++) {
        party_[i] = -1;
    }
    addMonster_ = status::g_Menu.addMonsterIndex_;
    if (addMonster_ < 0x12) {
        addMonster_ = 0;
    }
    else {
        party_[0] = 999;
        monsterCount_ = 1;
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < partyCount; i++) {
        if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            party_[monsterCount_] = i;
            monsterCount_++;
        }
    }
    navigator_.setupBase();
    navigator_.setup(5, 1, monsterCount_);
    navigator_.setPageNo(0);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(party_[0]);
    mode_ = MODE_SELECT;
}

THUMB void MaterielMenu_JISAN_LEAVE_SCRIPT::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_LEAVE_SCRIPT::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int page = navigator_.getPageNo();
        int pageMax = navigator_.getPageMaxCount() - 1;
        drawMemberChangeScreen(page, pageMax, 10, addMonster_);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_LEAVE_SCRIPT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            if (mode_ == MODE_YESNO) {
                int active = navigator_.getIndex(menuItem_.active_);
                if (active == 0 && addMonster_ != 0) {
                    int mes = 0xc3cc9;
                    switch (addMonster_) {
                        case 0x52:
                            mes = 0x5b33;
                            break;
                        case 0x3b:
                            mes = 0x5f87;
                            break;
                        case 0x3a:
                            mes = 0x75b8;
                            break;
                    }
                    TextAPI::setMACRO0(0x81, 0x50000000, getFriendMonsterName());
                    gTownMenu_MESSAGE.openMessageForMENU();
                    gTownMenu_MESSAGE.addMessage(mes);
                    int ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(addMonster_);
                    status::PlayerDataAll::setMonsterOldManFlag(ctrl, true);
                    status::PlayerDataAll::setFriendMonsterFlag(ctrl, true);
                    if (mes == 0x5f87) {
                        cmn::PartyTalk::getSingleton().setPreMessageNo(mes);
                    }
                    mode_ = MODE_END;
                    return;
                }
                int activeChara = party_[active];
                int equipCount = 0;
                int carriageOut = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
                int index = MenuStatusInfo::getPlayerIndex(activeChara);
                int itemCount = MenuStatusInfo::getPlayerItemCount(activeChara);
                for (int i = 0; i < itemCount; i++) {
                    if (MenuStatusInfo::isPlayerEquipItemIndex(activeChara, i) == true) {
                        equipCount++;
                    }
                }
                while (equipCount < MenuStatusInfo::getPlayerItemCount(activeChara)) {
                    MenuStatusInfo::addFukuroItem(MenuStatusInfo::getPlayerItemID(activeChara, equipCount), 1);
                    MenuStatusInfo::throwPlayerItem(activeChara, equipCount);
                }
                MenuStatusInfo::delPlayer(activeChara);
                status::PlayerDataAll::setMonsterOldManFlag(index, true);
                if (status::g_Menu.addMonsterIndex_ >= 0x10) {
                    int ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(status::g_Menu.addMonsterIndex_);
                    status::PlayerDataAll::setFriendMonsterFlag(ctrl, true);
                    MenuStatusInfo::addPlayer(ctrl);
                    if (activeChara < carriageOut) {
                        int reorderParty[4] = {-1};
                        for (int i = 0; i < 4; i++) {
                            reorderParty[i] = -1;
                        }
                        for (int i = 0; i < carriageOut; i++) {
                            if (i == activeChara) {
                                reorderParty[i] = MenuStatusInfo::getPlayerSortIndex(ctrl);
                            }
                            else {
                                reorderParty[i] = i;
                            }
                        }
                        for (int i = 0; i < carriageOut - 1; i++) {
                            if (reorderParty[i] > reorderParty[i + 1]) {
                                int temp = reorderParty[i];
                                reorderParty[i] = reorderParty[i + 1];
                                reorderParty[i + 1] = temp;
                            }
                        }
                        MenuStatusInfo::reorder(reorderParty[0], reorderParty[1], reorderParty[2], reorderParty[3]);
                    }
                }
                int mes = 0xc3ccc;
                switch (addMonster_) {
                    case 0x52:
                        mes = 0x5b36;
                        break;
                    case 0x3b:
                        mes = 0x5f8a;
                        break;
                    case 0x3a:
                        mes = 0x75bb;
                        break;
                }
                TextAPI::setMACRO0(0x12, 0x50000000, index);
                TextAPI::setMACRO0(0x81, 0x50000000, getFriendMonsterName());
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(mes);
                if (mes == 0x5f8a) {
                    cmn::PartyTalk::getSingleton().setPreMessageNo(mes);
                }
                mode_ = MODE_END;
                return;
            }
            if (mode_ == MODE_END) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                cmn::GameManager::getSingleton().resetParty();
            }
        }
        else if (stat == MENUBASE_STAT_CANCEL) {
            int mes = 0xc3cc0;
            switch (addMonster_) {
                case 0x52:
                    mes = 0x5b2a;
                    break;
                case 0x3b:
                    mes = 0x5f7e;
                    break;
                case 0x3a:
                    mes = 0x75af;
                    break;
            }
            gTownMenu_MESSAGE.close();
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(mes);
            mode_ = MODE_RETRY;
        }
        return;
    }
    navigator_.setup(5, 1, monsterCount_);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = navigator_.getIndex(menuItem_.active_);
        int page = navigator_.getPageNo();
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(party_[active]);
        menu::MaterielMenuPlayerControl::getSingleton()->activeCharaPage_ = page;
        if (result == 2) {
            int mes = 0xc3cc6;
            switch (addMonster_) {
                case 0x52:
                    mes = 0x5b30;
                    break;
                case 0x3b:
                    mes = 0x5f84;
                    break;
                case 0x3a:
                    mes = 0x75b5;
                    break;
            }
            if (active == 0 && addMonster_ != 0) {
                TextAPI::setMACRO0(0x12, 0x50000000, getFriendMonsterName());
            }
            else {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(party_[active]));
            }
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(mes);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_YESNO;
        }
        redraw_ = 1;
    }
}

THUMB int MaterielMenu_JISAN_LEAVE_SCRIPT::getFriendMonsterName()
{
    int ctrl = status::g_Menu.addMonsterIndex_;
    if (ctrl >= 0x10) {
        ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(ctrl);
    }
    if (addMonster_ == 0x3a) {
        return 0x22e;
    }
    if (addMonster_ == 0x3b) {
        return 0x22f;
    }
    if (addMonster_ == 0x52) {
        return 0x246;
    }
    return ctrl;
}

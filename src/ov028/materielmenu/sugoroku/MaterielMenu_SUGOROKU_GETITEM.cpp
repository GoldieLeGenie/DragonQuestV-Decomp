#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_GETITEM.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    int itemCount = MenuStatusInfo::getPlayerItemCount(0);
    for (int i = 0; i < itemCount; i++) {
        if (MenuStatusInfo::isPlayerEquipItemIndex(0, i) == false) {
            if (i > 5) {
                i -= 6;
                menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 1;
            }
            else {
                menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            }
            menuItem_.active_ = i;
            break;
        }
    }
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
    navigator_.setupBase();
    navigator_.setup(2, 3, itemCount);
    navigator_.setPageNo(menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_);
    meCount_ = 0;
    menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    if (itemID_ == 0xa6) {
        gTownMenu_MESSAGE.addMessage(0xca692);
        gTownMenu_MESSAGE.addMessageWAITKEY();
        mode_ = 0;
        return;
    }
    gTownMenu_MESSAGE.addMessage(0xca692);
    if (itemID_ == 0xd1) {
        MenuStatusInfo::setMedal(MenuStatusInfo::getMedal() + 1);
        if (status::g_Story.isMedalFlag() == false) {
            gTownMenu_MESSAGE.addMessage(0xc45c2, 0xc45c3);
            status::g_Story.setMedalFlag(true);
        }
        mode_ = 4;
        return;
    }
    if (itemCount == 12) {
        gTownMenu_MESSAGE.addMessage(0xca693);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = 0;
        return;
    }
    MenuStatusInfo::addPlayerItem(0, itemID_);
    mode_ = 4;
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::menuExecute()
{
    unkfunc_0201c8e8(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() == false) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217bed8(1);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (meCount_ == 0) {
                SoundManager::playRestart(0x2c, 5);
                meCount_++;
                return;
            }
            if (meCount_ > 0xb4) {
                gTownMenu_MESSAGE.clearMessageWAITPROG();
                gTownMenu_MESSAGE.restartMessage();
                TextAPI::setMACRO0(10, 0x40000000, itemID_);
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(0));
                if (MenuStatusInfo::getPlayerItemCount(0) == 12) {
                    gTownMenu_MESSAGE.addMessage(0xca693);
                    gTownMenu_MESSAGE.setYesNo();
                    mode_ = 0;
                    return;
                }
                gTownMenu_MESSAGE.addMessage(0xc44c0);
                MenuStatusInfo::addPlayerItem(0, itemID_);
                mode_ = 4;
                return;
            }
            meCount_++;
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
            return;
        }
        return;
    }
    navigator_.setup(2, 3, MenuStatusInfo::getPlayerItemCount(0));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xca696);
            mode_ = 1;
        }
        if (result == 2) {
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO1(10, 0x40000000, itemID_);
            TextAPI::setMACRO2(10, 0x40000000, MenuStatusInfo::getPlayerItemID(0, navigator_.getIndex(menuItem_.active_)));
            gTownMenu_MESSAGE.addMessage(0xca699);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = 2;
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::selectYes()
{
    switch (mode_) {
        case 0:
            MenuStatusInfo::addFukuroItem(itemID_, 1);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case 2: {
            int index = navigator_.getIndex(menuItem_.active_);
            MenuStatusInfo::addFukuroItem(MenuStatusInfo::getPlayerItemID(0, index), 1);
            MenuStatusInfo::throwPlayerItem(0, index);
            MenuStatusInfo::addPlayerItem(0, itemID_);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        }
        case 4:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_SUGOROKU_GETITEM::selectNo()
{
    switch (mode_) {
        case 0:
        case 2:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xca696);
            mode_ = 1;
            break;
    }
}

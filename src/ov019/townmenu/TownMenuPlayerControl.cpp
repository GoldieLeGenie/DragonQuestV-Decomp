#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/GameFlag.hpp"

menu::TownMenuPlayerControl menu::gTownMenuPlayerControl;

THUMB menu::TownMenuPlayerControl* menu::TownMenuPlayerControl::getSingleton()
{
    return &gTownMenuPlayerControl;
}

THUMB void menu::TownMenuPlayerControl::initialize()
{
    if (initializeLock_ == 1) {
        initializeLock_ = 0;
        return;
    }
    setup();
    targetChara_ = 0;
    activeMagic_ = 0;
    activeItemPage_ = 0;
    activeFukuro_ = 0;
    targetItem_ = 0;
    targetItemPage_ = 0;
    targetFukuro_ = 0;
    activeCommand_ = 0;
    activeTactics_ = 0;
    actorIndex_ = 0;
    targetIndex_ = 0;
    targetCharaPage_ = 0;
    unk_24 = 0;
    unk_25 = 0;
    prevCommand_ = 0;
}

THUMB short menu::TownMenuPlayerControl::getActiveItemIndexToAll()
{
    if (activeFukuro_) {
        return MenuStatusInfo::getFukuroItemIndexToAll(activeItem_, activeItemPage_);
    } else {
        int index = activeItem_ + activeItemPage_ * 6;
        int maxCount = MenuStatusInfo::getPlayerItemCount(activeChara_);
        return index;
    }
}

THUMB short menu::TownMenuPlayerControl::getTargetItemIndexToAll()
{
    if (targetFukuro_) {
        return MenuStatusInfo::getFukuroItemIndexToAll(targetItem_, targetItemPage_);
    } else {
        int index = targetItem_ + targetItemPage_ * 6;
        int maxCount = MenuStatusInfo::getPlayerItemCount(targetChara_);
        return index;
    }
}

THUMB void menu::TownMenuPlayerControl::setActiveCommand(unsigned char activeCommand)
{
    bool show = MenuStatusInfo::ableToShow();
    activeCommand_ = activeCommand;
    if (activeFukuro_) {
        if (show == true && activeCommand > 2) {
            activeCommand_ += 1;
        } else if (activeCommand > 2) {
            activeCommand_ += 2;
        }
        return;
    }
    int activeItem = activeItem_;
    int pageTop = activeItemPage_ * 6;
    if (!MenuStatusInfo::isAbleToEqip(activeChara_, activeItem + pageTop) && !show) {
        if (activeCommand > 2) {
            activeCommand_ += 2;
        }
    } else if (!MenuStatusInfo::isAbleToEqip(activeChara_, activeItem + pageTop)) {
        if (activeCommand > 2) {
            activeCommand_ += 1;
        }
    } else if (!show) {
        if (activeCommand > 3) {
            activeCommand_ += 1;
        }
    }
}

THUMB unsigned char menu::TownMenuPlayerControl::getActiveCommand()
{
    unsigned char command = activeCommand_;
    int show = 0;
    int equip = 0;
    if (activeFukuro_ == 0) {
        equip = MenuStatusInfo::isAbleToEqip(activeChara_, getActiveItemIndexToAll());
    }
    if (MenuStatusInfo::ableToShow() == true) {
        show = 1;
    }
    switch (command) {
    case 4:
        if (activeFukuro_ == 1 || !equip) {
            command -= 1;
        }
        break;
    case 5:
        if (activeFukuro_ == 1) {
            if (show == 1) {
                command -= 1;
            } else {
                command -= 2;
            }
        } else if (!show && !equip) {
            command -= 2;
        } else if (!show || !equip) {
            command -= 1;
        }
        break;
    }
    return command;
}

THUMB unsigned char menu::TownMenuPlayerControl::getDrawCharaCount(TOWN_MENU menuType)
{
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (menuType == TOWN_MENU_ITEM) {
        count++;
    }
    if (g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
        count--;
    }
    return count;
}

THUMB void menu::TownMenuPlayerControl::setPlayerActiveItemByChangeMax()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int maxCount = MenuStatusInfo::getPlayerItemCount(activeChara_);
    if (activeItem_ + activeItemPage_ * 6 >= maxCount) {
        activeItem_--;
        if (activeItemPage_ == 1 && activeItem_ < 0) {
            activeItemPage_ = 0;
            activeItem_ = 5;
        }
        if (activeItem_ < 0) {
            activeItemPage_ = 0;
            activeItem_ = 0;
        }
    }
}

THUMB void menu::TownMenuPlayerControl::setFukuroActiveItemByChangeMax()
{
    int pageMax = MenuStatusInfo::getFukuroMaxPage();
    if (activeItemPage_ >= pageMax) {
        activeItemPage_ = pageMax - 1;
        activeItem_ = (unsigned char)(MenuStatusInfo::getFukuroItemCountInPage(activeItemPage_) - 1);
        return;
    }
    if (activeItem_ >= MenuStatusInfo::getFukuroItemCountInPage(activeItemPage_)) {
        activeItem_--;
        if (activeItem_ < 0) {
            activeItemPage_--;
            activeItem_ = 5;
            if (activeItemPage_ < 0) {
                activeItemPage_ = 0;
                activeItem_ = 0;
            }
        }
    }
}

THUMB void menu::TownMenuPlayerControl::setPlayerTargetItemByChangeMax()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int maxCount = MenuStatusInfo::getPlayerItemCount(targetChara_);
    if (targetItem_ + targetItemPage_ * 6 >= maxCount) {
        targetItem_--;
        if (targetItemPage_ == 1 && targetItem_ < 0) {
            targetItemPage_ = 0;
            targetItem_ = 5;
        }
        if (targetItem_ < 0) {
            targetItemPage_ = 0;
            targetItem_ = 0;
        }
    }
}

THUMB void menu::TownMenuPlayerControl::setFukuroTargetItemByChangeMax()
{
    int pageMax = MenuStatusInfo::getFukuroMaxPage();
    if (targetItemPage_ >= pageMax) {
        targetItemPage_ = pageMax - 1;
        targetItem_ = (unsigned char)(MenuStatusInfo::getFukuroItemCountInPage(targetItemPage_) - 1);
        return;
    }
    if (targetItem_ >= MenuStatusInfo::getFukuroItemCountInPage(targetItemPage_)) {
        targetItem_--;
        if (targetItem_ < 0) {
            targetItemPage_--;
            targetItem_ = 5;
            if (targetItemPage_ < 0) {
                targetItemPage_ = 0;
                targetItem_ = 0;
            }
        }
    }
}

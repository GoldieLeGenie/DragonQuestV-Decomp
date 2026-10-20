#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectCommand.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int twn::TownPlayerManager::getSearchMapUid()
{
    return searchMapUid_;
}

inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index)
{
    return museumitem_[index];
}

inline unsigned short status::MuseumItemStatus::getIconID()
{
    return iconid_;
}

inline unsigned short status::MuseumItemStatus::getMapID()
{
    return mapid_;
}

inline char dq5::level::MeisanhinData::getLevel()
{
    return (byte_1 & 0xc) >> 2;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void cmn::CommonCounterInfo::setCounter(int index, unsigned char counter)
{
    dayCounter_[index] = counter;
}

inline void TownMenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void TownMenuPlayerControl::setActiveItemPage(char page)
{
    activeItemPage_ = page;
}

THUMB void TownMenuItemSelectChara::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->activeItem_;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    activeFukuro_ = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    navigator_.setupBase();
    if (activeFukuro_ == 1) {
        navigator_.setup(2, 3, MenuStatusInfo::getFukuroItemCount());
    } else {
        navigator_.setup(2, 3, MenuStatusInfo::getPlayerItemCount(activeChara));
    }
    navigator_.setPageNo(TownMenuPlayerControl::getSingleton()->activeItemPage_);
    mode_ = MODE_SELECT_ITEM;
    setItem_ = 0;
    daizaItem_ = 0;
    curseMessage_ = 0;
    if (meisanhinFlag_ == 1) {
        int uid = twn::TownPlayerManager::getSingleton().getSearchMapUid();
        daizaItem_ = status::g_MuseumStatus.getMuseumItemStatus(status::g_MuseumStatus.findMuseumItemStatus(uid)).getIconID();
    }
    cmn::g_cmnSoundManager.initialize();
}

THUMB void TownMenuItemSelectChara::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    setupItemIcon32Layout2x3(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void TownMenuItemSelectChara::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true && curseMessage_ == 0) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_02172f6c(0, navigator_.getPageNo());
        menuItem_.drawActive();
    }
}

THUMB void TownMenuItemSelectChara::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    if (curseMessage_ != 0) {
        cmn::g_talkSound.setOrderMessage(0x32);
        cmn::g_talkSound.setOrderMessage(0x30);
        cmn::g_talkSound.setMessageSound(2, -1);
        gTownMenu_MESSAGE.openMessageForTALK();
        MenuAPI::addMessageSerial(curseMessage_);
        curseMessage_ = 0;
    }
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
    if (activeFukuro_ == 1) {
        navigator_.setup(2, 3, MenuStatusInfo::getFukuroItemCount());
    } else {
        navigator_.setup(2, 3, MenuStatusInfo::getPlayerItemCount(TownMenuPlayerControl::getSingleton()->activeChara_));
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton()->setActiveItem((unsigned char)menuItem_.active_);
        TownMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (activeFukuro_ == 1) {
            if (meisanhinFlag_ == 1) {
                status::g_Menu.meisanSackActive_ = menuItem_.active_;
                status::g_Menu.meisanSackActivePage_ = navigator_.getPageNo();
            } else {
                status::g_Menu.sackActive_ = menuItem_.active_;
                status::g_Menu.sackActivePage_ = navigator_.getPageNo();
            }
        }
        if (result == 3) {
            if (activeFukuro_ == 0) {
                TownMenuPlayerControl::getSingleton()->setActiveItem(0);
                TownMenuPlayerControl::getSingleton()->setActiveItemPage(0);
            }
            close();
            data_ov019_02183524.fromMateriel_ = meisanhinFlag_;
            data_ov019_02183524.open();
        }
        if (result == 2) {
            if (meisanhinFlag_ == 1) {
                int activeItem = navigator_.getIndex(menuItem_.active_);
                if (activeFukuro_ == 1) {
                    setItem_ = MenuStatusInfo::getFukuroItemID(activeItem, 0);
                } else {
                    setItem_ = MenuStatusInfo::getPlayerItemID(TownMenuPlayerControl::getSingleton()->activeChara_, activeItem);
                }
                if (status::UseItem::getItemType(setItem_) != ITEM_SPECIALTY) {
                    TextAPI::setMACRO0(10, 0x40000000, setItem_);
                    gTownMenu_MESSAGE.openMessageForMENU();
                    gTownMenu_MESSAGE.addMessage(status::UseItem::getStopMessage(setItem_));
                    mode_ = MODE_END;
                } else {
                    gTownMenu_MESSAGE.openMessageForMENU();
                    TextAPI::setMACRO0(10, 0x40000000, setItem_);
                    gTownMenu_MESSAGE.addMessage(0xc54a5);
                    gTownMenu_MESSAGE.setYesNo();
                    mode_ = MODE_SET_ITEM;
                }
            } else {
                close();
                gTownMenuItemSelectCommand.open();
            }
        }
        redraw_ = 1;
    }
}

THUMB void TownMenuItemSelectChara::setMeisanhin()
{
    int activeItem = navigator_.getIndex(menuItem_.active_);
    int uid = twn::TownPlayerManager::getSingleton().getSearchMapUid();
    int no = status::g_MuseumStatus.findMuseumItemStatus(uid);
    status::MuseumItemStatus& museum = status::g_MuseumStatus.getMuseumItemStatus(no);
    int daizaLevel;
    switch (museum.getMapID()) {
        case status::MUSEUMFLOOR_F1:
            daizaLevel = 1;
            break;
        case status::MUSEUMFLOOR_F2:
            daizaLevel = 2;
            break;
        case status::MUSEUMFLOOR_F3:
            daizaLevel = 3;
            break;
        default:
            daizaLevel = 0;
            break;
    }
    if (activeFukuro_ == 1) {
        museum.setIconIDandRedraw(setItem_);
        MenuStatusInfo::throwFukuroItemForID(setItem_);
        TownMenuPlayerControl::getSingleton()->setFukuroActiveItemByChangeMax();
    } else {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        museum.setIconIDandRedraw(setItem_);
        MenuStatusInfo::throwPlayerItem(activeChara, activeItem);
        TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
    }
    if (setItem_ == 0xf4) {
        int itemLevel = museum.meisan_.getLevel() - daizaLevel;
        if (itemLevel == -3) {
            curseMessage_ = 0x3885;
        }
        if (itemLevel == -2) {
            curseMessage_ = 0x3882;
        }
        if (itemLevel == -1) {
            curseMessage_ = 0x387f;
        }
    }
    if (curseMessage_ != 0) {
        cmn::g_cmnSoundManager.setPlaySound(1, false);
    } else {
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(10, 0x40000000, setItem_);
        gTownMenu_MESSAGE.addMessage(0xc54ab);
        if (setItem_ == 0xf1) {
            cmn::g_CommonCounterInfo.setCounter(7, 1);
        }
    }
    mode_ = MODE_END;
}

THUMB void TownMenuItemSelectChara::selectYes()
{
    switch (mode_) {
        case MODE_SELECT_ITEM:
            break;
        case MODE_SET_ITEM:
            setMeisanhin();
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void TownMenuItemSelectChara::selectNo()
{
    switch (mode_) {
        case MODE_SELECT_ITEM:
            break;
        case MODE_SET_ITEM:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc5499);
            mode_ = MODE_SELECT_ITEM;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemMeisanMessage.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/leveldata/MeisanhinData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenuItemMeisanMessage::menuDraw()
{
}

inline void TownMenuItemMeisanMessage::menuExecute()
{
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::MeisanhinData* dq5::level::MeisanhinData::getRecord(int index)
{
    return (MeisanhinData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::MeisanhinData::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned short dq5::level::MeisanhinData::getItemid()
{
    return itemid;
}

inline unsigned long dq5::level::MeisanhinData::getMizusashiMsg()
{
    return mizusashiMsg;
}

inline unsigned long dq5::level::MeisanhinData::getHousekiMsg()
{
    return housekiMsg;
}

inline unsigned long dq5::level::MeisanhinData::getMigakiMsg()
{
    return migakiMsg;
}

inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index)
{
    return museumitem_[index];
}

inline unsigned short status::MuseumItemStatus::getIconID()
{
    return iconid_;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void cmn::CommonCounterInfo::setCounter(int index, unsigned char counter)
{
    dayCounter_[index] = counter;
}

inline short status::MenuStatus::getActorIndex()
{
    return actorIndex_;
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return coll_GetObjId(m_fld.m_coll, polygonNo);
}

THUMB void TownMenuItemMeisanMessage::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    cmn::g_cmnSoundManager.initialize();
    m_message = 0;
    m_isPlaySound = 0;
    int nowId = twn::TownPlayerManager::getSingleton().player_.townActionWalk_.collId_;
    int objId = twn::TownStageManager::getSingleton()->stage_.collGetObjId(nowId);
    int uid = twn::TownStageManager::getSingleton()->stage_.m_fld.GetMapObjUid(objId);
    m_daizaUid = status::g_MuseumStatus.findMuseumItemStatus(uid);
    m_daizaItem = status::g_MuseumStatus.getMuseumItemStatus(m_daizaUid).getIconID();
}

THUMB void TownMenuItemMeisanMessage::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    if (m_isPlaySound == 1) {
        gTownMenu_MESSAGE.restartMessage();
        gTownMenu_MESSAGE.addMessage(m_message);
        m_isPlaySound = 0;
        m_message = 0;
    }
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            if (m_message != 0) {
                cmn::g_cmnSoundManager.setPlaySound(13, false);
                m_isPlaySound = 1;
                return;
            }
            gTownMenu_MESSAGE.close();
            close();
            gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
        }
        return;
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(1, 0x50000000, status::g_Menu.getActorIndex());
    TextAPI::setMACRO0(0x12, 0x50000000, status::g_Menu.getActorIndex());
    TextAPI::setMACRO0(10, 0x40000000, m_daizaItem);
    int daizaItem = m_daizaItem;
    if (daizaItem == 0) {
        TextAPI::setMACRO0(10, 0x40000000, m_useItem);
        switch (m_useItem) {
            case 0xc8:
                gTownMenu_MESSAGE.addMessage(0xc4169, 0xc424e);
                break;
            case 0xd6:
                gTownMenu_MESSAGE.addMessage(0xc4169, 0xc416a);
                break;
            case 0xfb:
                gTownMenu_MESSAGE.addMessage(0xc41e2, 0xc41e3);
                break;
        }
    } else {
        status::MuseumItemStatus& museum = status::g_MuseumStatus.getMuseumItemStatus(m_daizaUid);
        if (m_useItem == 0xfb && daizaItem == 0xdb) {
            museum.setIconIDandRedraw(0xdc);
            gTownMenu_MESSAGE.addMessage(0xc544c);
            m_message = 0xc544d;
            g_AreaFlag.set(0x2c5);
        } else if (m_useItem == 0xc8 && daizaItem == 0xf0) {
            museum.setIconIDandRedraw(0xf1);
            cmn::g_CommonCounterInfo.setCounter(7, 1);
            gTownMenu_MESSAGE.addMessage(0xc546e);
            m_message = 0xc546f;
            g_AreaFlag.set(0x2c7);
        } else if (m_useItem == 0xc8 && daizaItem == 0xf1) {
            gTownMenu_MESSAGE.addMessage(0xc5471);
            if (cmn::g_CommonCounterInfo.isEndDayCounter(7) == true) {
                gTownMenu_MESSAGE.addMessage(0xc5472, 0xc5473, 0xc5474);
                int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
                int i = 0;
                bool add = false;
                for (; i < partyCount; i++) {
                    if (MenuStatusInfo::getPlayerIndex(i) == status::g_Menu.getActorIndex() && MenuStatusInfo::getPlayerItemCount(i) != 12) {
                        MenuStatusInfo::addPlayerItem(i, 0xa5);
                        add = true;
                        break;
                    }
                }
                if (add == false) {
                    MenuStatusInfo::addFukuroItem(0xa5, 1);
                    TextAPI::setMACRO0(0xc, 0x50000000, status::g_Menu.getActorIndex());
                    TextAPI::setMACRO0(10, 0x40000000, 0xa5);
                    gTownMenu_MESSAGE.addMessage(0xc3cb0);
                }
                cmn::g_CommonCounterInfo.setCounter(7, 1);
            }
        } else if (m_useItem == 0xd6 && daizaItem == 0xdf) {
            museum.setIconIDandRedraw(0xe0);
            if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
                MenuStatusInfo::throwFukuroItemForID(0xd6);
            } else {
                int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
                int itemCount = MenuStatusInfo::getPlayerItemCount(activeChara);
                for (int i = 0; itemCount != 0; i++) {
                    if (MenuStatusInfo::getPlayerItemID(activeChara, i) == 0xd6) {
                        MenuStatusInfo::throwPlayerItem(activeChara, i);
                        break;
                    }
                }
            }
            gTownMenu_MESSAGE.addMessage(0xc547b);
            m_message = 0xc547c;
            g_AreaFlag.set(0x2c6);
        } else if (m_useItem == 0xfb) {
            gTownMenu_MESSAGE.addMessageSerial(dq5::level::MeisanhinData::getRecord(getRecordNo())->getMigakiMsg());
        } else if (m_useItem == 0xc8) {
            gTownMenu_MESSAGE.addMessageSerial(dq5::level::MeisanhinData::getRecord(getRecordNo())->getMizusashiMsg());
        } else {
            gTownMenu_MESSAGE.addMessageSerial(dq5::level::MeisanhinData::getRecord(getRecordNo())->getHousekiMsg());
        }
    }
    status::g_Menu.actorIndex_ = 0;
    status::g_Menu.targetIndex_ = 0;
}

THUMB int TownMenuItemMeisanMessage::getRecordNo()
{
    int count = dq5::level::MeisanhinData::getArraySize();
    for (int i = 0; i < count; i++) {
        if (m_daizaItem == dq5::level::MeisanhinData::getRecord(i)->getItemid()) {
            return i;
        }
    }
    return -1;
}

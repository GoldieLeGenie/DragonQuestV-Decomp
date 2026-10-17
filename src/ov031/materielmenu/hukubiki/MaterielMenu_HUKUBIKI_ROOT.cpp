#pragma ipa file
#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_ROOT.hpp"
#include "ov031/materielmenu/hukubiki/MaterielMenu_HUKUBIKI_SELECTCHARA.hpp"
#include "ov031/leveldata/HukubikiMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov001/town/TownFukubikiDraw.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/HukubikiPrize.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_HUKUBIKI_ROOT::menuExecute()
{
}

inline void MaterielMenu_HUKUBIKI_ROOT::menuDraw()
{
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void MaterielMenu_HUKUBIKI_SELECTCHARA::setPrize(short itemID)
{
    prize_ = itemID;
}

inline dq5::level::HukubikiPrize* dq5::level::HukubikiPrize::getRecord(int index)
{
    return (HukubikiPrize*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline short dq5::level::HukubikiPrize::getPrize()
{
    return prize;
}

inline dq5::level::HukubikiMessage* dq5::level::HukubikiMessage::getRecord(int index)
{
    return (HukubikiMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::HukubikiMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    mode_ = HUKUBIKI_FIRST;
    getPrize_ = status::g_Menu.fukubikiPrize_;
    ticketCount_ = getTicket(false);
    retryHukubiki_ = 0;
    cmn::g_cmnSoundManager.initialize();
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
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
    hukubikiUpdate();
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::selectYes()
{
    switch (mode_) {
        case HUKUBIKI_FIRST:
            showMessage(4, 0, 0);
            mode_ = HUKUBIKI_START;
            break;
        case HUKUBIKI_START:
            setHukubikiPrize();
            status::g_Menu.bookingFlag_ = menu::BOOKING_FUKUBIKI;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case HUKUBIKI_NEXT:
            if (getPrize_ == 5 || getPrize_ == 6) {
                showMessage(4, 0, 0);
                mode_ = HUKUBIKI_START;
            }
            else {
                short prize = dq5::level::HukubikiPrize::getRecord(getPrize_ + 1)->getPrize();
                close();
                gMaterielMenu_HUKUBIKI_SELECTCHARA.setPrize(prize);
                gMaterielMenu_HUKUBIKI_SELECTCHARA.open();
                menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
                retryHukubiki_ = 0;
            }
            break;
        case HUKUBIKI_END:
            status::g_Menu.bookingFlag_ = 0;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::selectNo()
{
    switch (mode_) {
        case HUKUBIKI_FIRST:
        case HUKUBIKI_NEXT:
            showMessage(29, 0, 0);
            mode_ = HUKUBIKI_END;
            break;
        case HUKUBIKI_START:
        case HUKUBIKI_DRAW:
        case HUKUBIKI_GET:
            break;
        case HUKUBIKI_END:
            status::g_Menu.bookingFlag_ = 0;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::hukubikiUpdate()
{
    switch (mode_) {
        case HUKUBIKI_FIRST:
            if (retryHukubiki_ == 1) {
                showMessage(4, 0, 0);
                status::g_Menu.bookingFlag_ = menu::BOOKING_FUKUBIKI;
                mode_ = HUKUBIKI_START;
                return;
            }
            if (status::g_Menu.bookingFlag_ == menu::BOOKING_RETURN) {
                status::g_Menu.bookingFlag_ = 0;
                if (status::g_Menu.fukubikiPrize_ == 0) {
                    cmn::g_cmnSoundManager.setPlaySound(10, false);
                }
                mode_ = HUKUBIKI_GET;
                return;
            }
            if (ticketCount_ == 0) {
                showMessage(1, 28, 29);
                mode_ = HUKUBIKI_END;
                return;
            }
            TextAPI::setMACRO0(0x72, 0xf0000000, ticketCount_);
            showMessage(1, 2, 3);
            gTownMenu_MESSAGE.setYesNo();
            break;
        case HUKUBIKI_GET: {
            mode_ = HUKUBIKI_NEXT;
            if (getPrize_ == 6) {
                ticketCount_ = getTicket(true);
                if (ticketCount_ == 0) {
                    showMessage(5, 28, 29);
                    mode_ = HUKUBIKI_END;
                    return;
                }
                TextAPI::setMACRO0(0x72, 0xf0000000, ticketCount_);
                showMessage(5, 27, 0);
                gTownMenu_MESSAGE.setYesNo();
                return;
            }
            if (getPrize_ == 0) {
                showMessage(6, 7, 11);
                return;
            }
            if (getPrize_ == 5) {
                TextAPI::setMACRO0(0x72, 0xf0000000, ticketCount_);
                showMessage(8, 9, 27);
                gTownMenu_MESSAGE.setYesNo();
                return;
            }
            char UTFcolor[512];
            if (getPrize_ == 1) {
                TextAPI::extractText(UTFcolor, sizeof(UTFcolor), 0xe0000000, 0x3d7);
            }
            if (getPrize_ == 2) {
                TextAPI::extractText(UTFcolor, sizeof(UTFcolor), 0xe0000000, 0x3d8);
            }
            if (getPrize_ == 3) {
                TextAPI::extractText(UTFcolor, sizeof(UTFcolor), 0xe0000000, 0x3d9);
            }
            if (getPrize_ == 4) {
                TextAPI::extractText(UTFcolor, sizeof(UTFcolor), 0xe0000000, 0x3da);
            }
            TextAPI::setUserString(0, UTFcolor);
            TextAPI::setMACRO0(0x85, 0xd0000000, 0);
            TextAPI::setMACRO0(0x73, 0xf0000000, getPrize_);
            int id = dq5::level::HukubikiPrize::getRecord(getPrize_ + 1)->getPrize();
            TextAPI::setMACRO0(10, 0x40000000, id);
            showMessage(10, 11, 0);
            break;
        }
        case HUKUBIKI_START:
        case HUKUBIKI_DRAW:
        case HUKUBIKI_NEXT:
        case HUKUBIKI_END:
            break;
    }
}

THUMB short MaterielMenu_HUKUBIKI_ROOT::getTicket(bool sub)
{
    short count = 0;
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        for (int j = 0; j < MenuStatusInfo::getPlayerItemCount(i); j++) {
            if (MenuStatusInfo::getPlayerItemID(i, j) == 0xb3) {
                if (sub == true) {
                    MenuStatusInfo::throwPlayerItem(i, j);
                    sub = false;
                    j = 0;
                }
                else {
                    count++;
                }
            }
        }
    }
    count += MenuStatusInfo::isFukuroHaveItem(0xb3);
    if (sub == true) {
        MenuStatusInfo::throwFukuroItemForID(0xb3);
        count--;
    }
    return count;
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::setHukubikiPrize()
{
    if (UnkDssRand::rand(256) == 0) {
        getPrize_ = 0;
    }
    else if (UnkDssRand::rand(128) == 0) {
        getPrize_ = 1;
    }
    else if (UnkDssRand::rand(36) == 0) {
        getPrize_ = 2;
    }
    else if (UnkDssRand::rand(16) == 0) {
        getPrize_ = 3;
    }
    else if (UnkDssRand::rand(8) == 0) {
        getPrize_ = 4;
    }
    else if (UnkDssRand::rand(2) == 0) {
        getPrize_ = 5;
    }
    else {
        getPrize_ = 6;
    }
    twn::TownFukubikiDraw::getSingleton().garagaraSetup(getPrize_);
    status::g_Menu.fukubikiPrize_ = getPrize_;
}

THUMB void MaterielMenu_HUKUBIKI_ROOT::showMessage(int mes1, int mes2, int mes3)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes1)->getMessage1());
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes2)->getMessage1());
    }
    if (mes3 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::HukubikiMessage::getRecord(mes3)->getMessage1());
    }
}

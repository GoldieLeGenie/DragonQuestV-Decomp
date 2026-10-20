#pragma ipa file
#include "ov023/materielmenu/inn/MaterielMenu_INN_ROOT.hpp"
#include "ov023/leveldata/InnMessage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_INN_ROOT::menuExecute()
{
}

inline dq5::level::InnMessage* dq5::level::InnMessage::getRecord(int index)
{
    return (InnMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::InnMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::InnMessage::getMessage2()
{
    return message2;
}

inline unsigned long dq5::level::InnMessage::getMessage3()
{
    return message3;
}

THUMB void MaterielMenu_INN_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    mode_ = INN_CHECKMONEY;
    fadeMode_ = FADE_OUT;
    innCharge_ = 0;
    unk_20 = 0;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int stayCount = 0;
    for (char i = 0; i < count; i++) {
        if (MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_ALIVE) == true) {
            stayCount++;
        }
    }
    int price;
    if (MaterielMenu_WINDOW_MANAGER::getSingleton()->menuType_ == 7) {
        price = status::g_Shop.getHotelPrice(true);
    }
    else {
        price = status::g_Shop.getHotelPrice(false);
    }
    innCharge_ = stayCount * price;
    extraInnType_ = MaterielMenu_WINDOW_MANAGER::getSingleton()->extraInnType_;
}

THUMB void MaterielMenu_INN_ROOT::menuDraw()
{
    if (unk_20 != 0) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        drawMoneyWindow(-1, -1, 0);
        drawPartyStatusWindows();
    }
}

THUMB void MaterielMenu_INN_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
        }
        else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            showMessage(7, 0);
            status::g_Menu.ownerVoice_ = 0x30;
            mode_ = INN_END;
        }
        return;
    }
    if (mode_ == INN_BRACKOUT) {
        fadeEffect();
        return;
    }
    if (mode_ == INN_END) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        status::g_Menu.eventInnStart_ = 0;
        return;
    }
    int mes1;
    int mes2 = 0;
    int yesno = 0;
    if (status::g_Menu.bookingFlag_ == menu::BOOKING_RETURN) {
        cmn::g_CommonCounterInfo.setChangeDay();
        ui_MsgSndSet(status::g_Menu.ownerVoice_);
        mes1 = 5;
        mode_ = INN_END_MAPCHANGE;
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.ownerVoice_ = 0x30;
    }
    else if (status::g_StageInfo.getDayNight() == dq5::DAY_NIGHT_NIGHT) {
        TextAPI::setMACRO0(0x33, 0xf0000000, innCharge_);
        yesno = 1;
        mes1 = 2;
        mes2 = 3;
        unk_20 = 1;
    }
    else {
        TextAPI::setMACRO0(0x33, 0xf0000000, innCharge_);
        mes1 = 1;
        mes2 = 3;
        unk_20 = 1;
        yesno = 1;
    }
    showMessage(mes1, mes2);
    if (yesno == 1) {
        gTownMenu_MESSAGE.setYesNo();
    }
}

THUMB void MaterielMenu_INN_ROOT::selectYes()
{
    switch (mode_) {
        case INN_CHECKMONEY:
            checkMoney();
            break;
        case INN_BRACKOUT:
            fadeEffect();
            break;
        case INN_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            status::g_Menu.eventInnStart_ = 0;
            break;
        case INN_END_MAPCHANGE:
            status::g_Menu.bookingFlag_ = 0;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            status::g_Menu.eventInnStart_ = 0;
            break;
    }
}

THUMB void MaterielMenu_INN_ROOT::checkMoney()
{
    int mes1;
    int mes2 = 0;
    if (MenuStatusInfo::getGold() >= innCharge_) {
        MenuStatusInfo::setGold(MenuStatusInfo::getGold() - innCharge_);
        int carriageOutCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        int aliveCount = 0;
        for (int i = 0; i < carriageOutCount; i++) {
            if (MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_ALIVE) == true) {
                aliveCount++;
            }
        }
        status::g_Menu.innCount_ = aliveCount;
        mes1 = 4;
        mode_ = INN_BRACKOUT;
        status::PartyStatusUtility::resetForceReorderMember();
    }
    else {
        mes2 = 7;
        mes1 = 6;
        mode_ = INN_END;
    }
    showMessage(mes1, mes2);
}

THUMB void MaterielMenu_INN_ROOT::fadeEffect()
{
    if (extraInnType_ == TYPE_ARAKURE) {
        status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
        cmn::g_CommonCounterInfo.setChangeDay();
        status::g_Menu.bookingFlag_ = 0;
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        status::g_Menu.eventInnStart_ = 1;
        status::g_Menu.ownerVoice_ = 0x30;
        status::g_StageInfo.initDoorOpenFlag();
        return;
    }
    if (extraInnType_ == TYPE_SUGOROKU) {
        switch (fadeMode_) {
            case FADE_OUT:
                status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
                g_Global.fadeOutBlack(60, true);
                cmn::g_cmnSoundManager.setPlaySound(0x12, false);
                fadeMode_ = FADE_SOUND;
                break;
            case FADE_SOUND:
                if (cmn::g_cmnSoundManager.isPlaySound_ == 1) {
                    cmn::g_cmnSoundManager.execSound();
                    break;
                }
                g_Global.fadeInBlack(60);
                fadeMode_ = FADE_END;
                revivalParty();
                redraw_ = 1;
                break;
            case FADE_END:
                if (fadeEffector.isFadeEnd()) {
                    cmn::g_CommonCounterInfo.setChangeDay();
                    showMessage(5, 0);
                    status::g_Menu.ownerVoice_ = 0x30;
                    mode_ = INN_END;
                }
                break;
        }
        return;
    }
    switch (fadeMode_) {
        case FADE_OUT:
            status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
            g_Global.fadeOutBlack(60, true);
            cmn::g_cmnSoundManager.setPlaySound(4, false);
            fadeMode_ = FADE_SOUND;
            break;
        case FADE_SOUND:
            if (cmn::g_cmnSoundManager.isPlaySound_ == 1) {
                cmn::g_cmnSoundManager.execSound();
                break;
            }
            revivalParty();
            status::g_StageInfo.initDoorOpenFlag();
            cmn::g_extraMapLink.setTownINN();
            status::g_Menu.bookingFlag_ = menu::BOOKING_INN;
            mode_ = INN_END;
            break;
    }
}

THUMB void MaterielMenu_INN_ROOT::showMessage(int mesIndex0, int mesIndex1)
{
    dq5::level::InnMessage* pInnMes0 = dq5::level::InnMessage::getRecord(mesIndex0);
    dq5::level::InnMessage* pInnMes1 = dq5::level::InnMessage::getRecord(mesIndex1);
    unsigned long mes0 = 0;
    unsigned long mes1 = 0;
    gTownMenu_MESSAGE.openMessageForTALK();
    switch (innType_) {
        case TYPE_NORMAL:
            mes0 = pInnMes0->getMessage1();
            mes1 = pInnMes1->getMessage1();
            break;
        case TYPE_ARAKURE:
            mes0 = pInnMes0->getMessage2();
            mes1 = pInnMes1->getMessage2();
            break;
        case TYPE_SUGOROKU:
            mes0 = pInnMes0->getMessage3();
            mes1 = pInnMes1->getMessage3();
            break;
    }
    gTownMenu_MESSAGE.addMessage(mes0);
    if (mes1 != 0) {
        gTownMenu_MESSAGE.addMessage(mes1);
    }
}

THUMB void MaterielMenu_INN_ROOT::revivalParty()
{
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < count; i++) {
        if (MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_ALIVE) == true) {
            MenuStatusInfo::getHaveStatusInfo(i).revival();
        }
    }
}

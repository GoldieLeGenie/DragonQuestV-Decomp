#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c7c.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c60.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cb4.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index)
{
    return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void UnkMaterielMenu_02187c7c::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(2, 4, 0x14);
    mode_ = 0;
    price_ = 0;
    isCaptureOffset_ = 0;
    icon_ = status::g_MuseumStatus.playerTaishi_.objectId_;
    icon_ = dq5::level::SurechigaiData::getRecord(icon_)->cgicon;
    TextAPI::setUserString(0, status::g_MuseumStatus.playerTaishi_.taishiName_);
}

THUMB void UnkMaterielMenu_02187c7c::menuExecute()
{
    switch (mode_) {
        case 0: {
            int active = menuItem_.active_;
            menu::MenuTemplate_materiel::surechigaiSelectList(&menuItem_, active, navigator_.getCountInPage());
            break;
        }
        case 1:
            menu::MenuTemplate_materiel::surechigaiSelectPrice(&menuItem_, menuItem_.active_);
            break;
    }
}

THUMB void UnkMaterielMenu_02187c7c::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    drawTagModeEditScreen(mode_, icon_, navigator_.getPageNo(), price_);
    if (mode_ <= 1) {
        menuItem_.drawActive();
    }
}

THUMB void UnkMaterielMenu_02187c7c::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (isCaptureOffset_ == 1) {
        setCaptureOffset(-4, 0);
        isCaptureOffset_ = 0;
    }
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            switch (mode_) {
                case 2:
                    TextAPI::setMACRO0(0x8f, 0xd0000000, 0);
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5ae);
                    mode_ = 3;
                    break;
                case 3:
                    close();
                    data_ov019_0218616c.editMode_ = 1;
                    data_ov019_0218616c.open();
                    resetCaptureOffset();
                    break;
                case 4:
                    status::g_MuseumStatus.recoveryTaishi();
                    close();
                    data_ov019_021854d4.open();
                    if (isCancelEnable_ == 1) {
                        data_ov019_021854d4.isCancelEnable_ = 1;
                    }
                    resetCaptureOffset();
                    break;
            }
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            switch (mode_) {
                case 2:
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5b1);
                    mode_ = 4;
                    break;
                case 3:
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5ba);
                    mode_ = 4;
                    break;
            }
        }
        return;
    }
    int step = 0;
    switch (mode_) {
        case 0:
            navigator_.setup(2, 4, 0x40);
            break;
        case 1:
            switch (menuItem_.active_) {
                case 0:
                    step = 100000;
                    break;
                case 1:
                    step = 10000;
                    break;
                case 2:
                    step = 1000;
                    break;
                case 3:
                    step = 100;
                    break;
                case 4:
                    step = 10;
                    break;
                case 5:
                    step = 1;
                    break;
            }
            navigator_.setup(6, 1, 6);
            break;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (result == 2) {
        decideSelection();
    }
    if (result == 3) {
        mode_--;
        if (mode_ < 0) {
            close();
            data_ov019_0218616c.editMode_ = 0;
            data_ov019_0218616c.open();
        }
        if (mode_ == 0) {
            int active = status::g_MuseumStatus.playerTaishi_.production_ - 1;
            int page = active / 8;
            active = active - page * 8;
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            menuItem_.active_ = active;
            navigator_.setPageNo(page);
        }
        if (mode_ == 1) {
            menuItem_.active_ = 5;
        }
    }
    if (mode_ == 1) {
        if (result == 4) {
            price_ += step;
        }
        if (result == 5) {
            price_ -= step;
        }
        price_ = dss::clamp<int>(0, price_, 999999);
    }
    redraw_ = 1;
}

THUMB void UnkMaterielMenu_02187c7c::decideSelection()
{
    switch (mode_) {
        case 0:
            mode_ = 1;
            status::g_MuseumStatus.playerTaishi_.production_ = navigator_.getIndex(menuItem_.active_) + 1;
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_UP);
            menuItem_.active_ = 5;
            break;
        case 1:
            status::g_MuseumStatus.playerTaishi_.setTaishiProducer(status::PlayerDataAll::playerData_[1].name_);
            status::g_MuseumStatus.playerTaishi_.price_ = price_;
            status::g_MuseumStatus.playerTaishi_.uniqueId_ = status::g_Game.getUniqueID();
            menuItem_.active_ = 0;
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc5ad);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = 2;
            isCaptureOffset_ = 1;
            break;
    }
}

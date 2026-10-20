#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cd0.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c98.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index)
{
    return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline status::TaishiBase& status::MuseumStatus::getOthersTaishi(int index)
{
    return othersTaishi_[index];
}

inline char* status::TaishiBase::getTaishiName()
{
    return taishiName_;
}

inline unsigned char status::TaishiBase::getTaishiObjectId()
{
    return objectId_;
}

THUMB void UnkMaterielMenu_02187cd0::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    unk_20 = status::g_MuseumStatus.getTaishiCount();
    navigator_.setup(2, 4, unk_20);
    unk_98 = 0;
    unk_1c = 0;
}

THUMB void UnkMaterielMenu_02187cd0::menuExecute()
{
    int count = unk_20 - navigator_.getPageNo() * 8;
    menu::MenuTemplate_materiel::unkfunc_0217d790(&menuItem_, menuItem_.active_, dss::clamp<int>(0, count, 8));
}

THUMB void UnkMaterielMenu_02187cd0::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int index = navigator_.getIndex(menuItem_.active_);
    if (unk_1c == 1) {
        unkfunc_0217ad28(index, 0, 0);
        return;
    }
    if (gTownMenu_MESSAGE.isOpen() == true) {
        return;
    }
    int icon = status::g_MuseumStatus.getOthersTaishi(index).getTaishiObjectId();
    if (unk_20 == 0) {
        index = -1;
    } else {
        menuItem_.drawActive();
        icon = dq5::level::SurechigaiData::getRecord(icon)->cgicon;
    }
    int page = navigator_.getPageNo();
    unkfunc_0217c47c(page, navigator_.getPageMaxCount(), index, icon, unk_94);
}

THUMB void UnkMaterielMenu_02187cd0::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (unk_94 == 1) {
                if (stat == MENUBASE_STAT_OK) {
                    unkfunc_02187928();
                    return;
                }
                unkfunc_021879ec();
                return;
            }
        }
        return;
    }
    navigator_.setup(2, 4, unk_20);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (result == 3) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(0xcc635);
        gTownMenu_MESSAGE.addMessageWAITKEY();
        close();
        data_ov019_02184d4c.open();
    }
    if (result == 2 && unk_94 == 1 && unk_20 != 0) {
        int index = navigator_.getIndex(menuItem_.active_);
        TextAPI::setUserString(0, status::g_MuseumStatus.getOthersTaishi(index).getTaishiName());
        TextAPI::setMACRO0(0x93, 0xd0000000, 0);
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(0xcc629);
        gTownMenu_MESSAGE.setYesNo();
        unk_98 = 1;
        unk_1c = 1;
        setCaptureOffset(-4, 0);
    }
    redraw_ = 1;
}

THUMB void UnkMaterielMenu_02187cd0::unkfunc_02187928()
{
    switch (unk_98) {
        case 0:
            resetCaptureOffset();
            break;
        case 1:
            status::g_MuseumStatus.deleteOthersTaishi(navigator_.getIndex(menuItem_.active_));
            unk_1c = 0;
            TextAPI::setMACRO0(0x93, 0xd0000000, 0);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc62a);
            if (status::g_MuseumStatus.getTaishiCount() == 0) {
                unk_98 = 2;
                return;
            }
            gTownMenu_MESSAGE.addMessage(0xcc62b);
            menuItem_.active_ = 0;
            navigator_.setPageNo(0);
            unk_98 = 0;
            unk_20 = status::g_MuseumStatus.getTaishiCount();
            break;
        case 2:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xcc635);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            close();
            data_ov019_02184d4c.open();
            resetCaptureOffset();
            break;
    }
}

THUMB void UnkMaterielMenu_02187cd0::unkfunc_021879ec()
{
    switch (unk_98) {
        case 0:
            break;
        case 1:
            unk_1c = 0;
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc62d);
            unk_98 = 2;
            resetCaptureOffset();
            break;
        case 2:
            break;
    }
}

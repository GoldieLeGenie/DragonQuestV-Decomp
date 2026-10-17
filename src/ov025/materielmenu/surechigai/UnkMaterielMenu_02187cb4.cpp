#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cb4.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c60.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c98.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MuseumStatus.hpp"

using menu::MenuStatusInfo;

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index)
{
    return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void UnkMaterielMenu_02187cb4::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(6, 2, 0x40);
    mode_ = 0;
    unk_20 = 1;
    unk_24 = 0;
    status::g_MuseumStatus.saveTaishi();
}

THUMB void UnkMaterielMenu_02187cb4::menuExecute()
{
    int active = menuItem_.active_;
    menu::MenuTemplate_materiel::surechigaiSelectObject(&menuItem_, active, navigator_.getCountInPage());
}

THUMB void UnkMaterielMenu_02187cb4::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
        int active = menuItem_.active_;
        int page = navigator_.getPageNo();
        unkfunc_0217c460(mode_, active, page, navigator_.getPageMaxCount());
        menuItem_.drawActive();
    }
    if (mode_ == 1) {
        int icon = dq5::level::SurechigaiData::getRecord(status::g_MuseumStatus.playerTaishi_.objectId_)->cgicon;
        int page = navigator_.getPageNo();
        unkfunc_0217c460(mode_, icon, page, navigator_.getPageMaxCount());
    }
}

THUMB void UnkMaterielMenu_02187cb4::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (unk_20 == 1) {
                redraw_ = 1;
                unk_20 = 0;
                return;
            }
            navigator_.setup(6, 2, 0x40);
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result == 0) {
                return;
            }
            if (result == 2) {
                int index = navigator_.getIndex(menuItem_.active_);
                if (status::g_MuseumStatus.selectTaishiFlag_[index] == 1) {
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    gTownMenu_MESSAGE.close();
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc5a8);
                    status::g_MuseumStatus.playerTaishi_.objectId_ = index + 1;
                    mode_ = 1;
                }
            }
            if (result == 3 && unk_24 == 1) {
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc631);
                mode_ = 2;
                return;
            }
            redraw_ = 1;
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == 2) {
                close();
                data_ov019_02184d4c.open();
                status::g_MuseumStatus.recoveryTaishi();
                status::g_MuseumStatus.resetSaveTaishi();
                return;
            }
            if (unk_20 == 0) {
                close();
                data_ov019_0218616c.unk_af = 0;
                data_ov019_0218616c.open();
            }
        }
        return;
    }
    if (unk_20 == 1) {
        gTownMenu_MESSAGE.openMessageForTALK();
        if (unk_24 == 1) {
            gTownMenu_MESSAGE.addMessage(0xcc63c);
        } else {
            gTownMenu_MESSAGE.addMessage(0xcc5a3, 0xcc5a4);
        }
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
}

#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187c98.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cb4.hpp"
#include "ov025/materielmenu/surechigai/UnkMaterielMenu_02187cd0.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/MuseumStatus.hpp"

using menu::MenuStatusInfo;

inline void status::MenuStatus::clearBooking()
{
    bookingFlag_ = 0;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

THUMB void UnkMaterielMenu_02187c98::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    isFirstMessage_ = 1;
    mode_ = 5;
    MaterielMenu_WINDOW_MANAGER::getSingleton()->surechigaiStart_ = 0;
    status::g_Menu.clearBooking();
}

THUMB void UnkMaterielMenu_02187c98::menuExecute()
{
    menu::MenuTemplate_materiel::surechigaiRoot(&menuItem_, menuItem_.active_);
}

THUMB void UnkMaterielMenu_02187c98::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        drawTagModeRootScreen();
        menuItem_.drawActive();
    }
}

THUMB void UnkMaterielMenu_02187c98::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (isFirstMessage_ == 1) {
                redraw_ = 1;
                isFirstMessage_ = 0;
                return;
            }
            navigator_.setup(1, 5, 5);
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result == 0) {
                return;
            }
            if (result == 2) {
                gTownMenu_MESSAGE.clearMessageWAITPROG();
                selectCommand();
            }
            if (result == 3) {
                gTownMenu_MESSAGE.clearMessageWAITPROG();
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc639);
                mode_ = 4;
            }
            redraw_ = 1;
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            unkfunc_02187278();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            unkfunc_02187310();
        }
        return;
    }
    if (isFirstMessage_ == 1) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(0xcc5d3);
        gTownMenu_MESSAGE.addMessageWAITKEY();
    }
}

THUMB void UnkMaterielMenu_02187c98::unkfunc_02187278()
{
    switch (mode_) {
        case 1:
            if (isFirstMessage_ == 1) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(0xcc635);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                mode_ = 5;
                return;
            }
            status::g_Menu.surechigaiMode_ = 2;
            close();
            data_ov019_021854d4.open();
            data_ov019_021854d4.isCancelEnable_ = 1;
            break;
        case 3:
            status::g_Menu.surechigaiMode_ = 4;
            close();
            data_ov019_02185864.open();
            data_ov019_02185864.isDeleteMode_ = 1;
            mode_ = 5;
            break;
        case 4:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case 0:
        case 2:
            break;
    }
}

THUMB void UnkMaterielMenu_02187c98::unkfunc_02187310()
{
    switch (mode_) {
        case 1:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc631);
            isFirstMessage_ = 1;
            break;
        case 4:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->surechigaiStart_ = 0;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->changeTaishi_ = 0;
            break;
        case 0:
        case 2:
        case 3:
            break;
    }
}

THUMB void UnkMaterielMenu_02187c98::selectCommand()
{
    gTownMenu_MESSAGE.close();
    switch (menuItem_.active_) {
        case 0:
            mode_ = 0;
            if (status::g_MuseumStatus.getBlankTaishiNo() == -1) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc61c, 0xcc61d);
                mode_ = 1;
                isFirstMessage_ = 1;
                return;
            }
            status::g_Menu.surechigaiMode_ = 1;
            status::g_Menu.setBooking(menu::BOOKING_SURECHIGAI);
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case 1:
            mode_ = 1;
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xcc63b);
            gTownMenu_MESSAGE.setYesNo(1);
            break;
        case 2:
            mode_ = 2;
            if (status::g_MuseumStatus.getTaishiCount() == 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc645);
                mode_ = 1;
                isFirstMessage_ = 1;
                return;
            }
            status::g_Menu.surechigaiMode_ = 3;
            close();
            data_ov019_02185864.isDeleteMode_ = 0;
            data_ov019_02185864.open();
            break;
        case 3:
            mode_ = 3;
            if (status::g_MuseumStatus.getTaishiCount() == 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc648);
                mode_ = 1;
                isFirstMessage_ = 1;
                return;
            }
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc623, 0xcc624, 0xcc625);
            break;
        case 4:
            mode_ = 4;
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xcc639);
            break;
    }
}

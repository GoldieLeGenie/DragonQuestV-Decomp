#include "ov024/materielmenu/casino/MaterielMenu_SlimeTouch.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/TouchData.hpp"

inline int menu::MenuItem::getActive()
{
    return active_;
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

THUMB void MaterielMenu_SlimeTouch::menuSetup()
{
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = SELECT_START;
    mode_ = MODE_START;
}

THUMB void MaterielMenu_SlimeTouch::menuExecute()
{
    menu::MenuTemplate_materiel::unkfunc_0217d660(&menuItem_);
}

THUMB void MaterielMenu_SlimeTouch::menuDraw()
{
    if (mode_ == MODE_SELECT) {
        unkfunc_0217c2cc();
        menuItem_.drawActive();
    }
    if (mode_ == MODE_RANKING) {
        unkfunc_0217c2f4();
    }
}

THUMB void MaterielMenu_SlimeTouch::menuUpdate()
{
    if (messageUpdate()) {
        commandUpdate();
    }
}

THUMB bool MaterielMenu_SlimeTouch::messageUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() && !gTownMenu_MESSAGE.isMessageWAITPROG()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            redraw_ = 1;
        }
        return false;
    }
    switch (mode_) {
        case MODE_START:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xccd5a);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            mode_ = MODE_SELECT;
            break;
        case MODE_SELECT:
        case MODE_RANKING:
            return true;
        case MODE_NOTRANKIN:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xccd5f);
            mode_ = MODE_START;
            break;
        case MODE_TUTORIAL:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessageCount(0xccd63, 9);
            mode_ = MODE_START;
            break;
    }
    return false;
}

THUMB void MaterielMenu_SlimeTouch::commandUpdate()
{
    switch (mode_) {
        case MODE_SELECT:
            if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
                selectUpdate();
            }
            break;
        case MODE_RANKING:
            if (dss::g_Pad.edge() == 1 || dss::g_Pad.edge() == 2 || dss::g_Pad.edge() == 0x800) {
                mode_ = MODE_START;
                redraw_ = 1;
            }
            break;
    }
}

THUMB void MaterielMenu_SlimeTouch::selectUpdate()
{
    switch (menuItem_.execInput()) {
        case menu::MenuItem::MENUITEM_RESULT_OK:
            okUpdate();
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.close();
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
        case menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL:
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.close();
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            if (menuItem_.active_ == SELECT_START) {
                menuItem_.active_ = SELECT_END;
            }
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            if (menuItem_.active_ == SELECT_END) {
                menuItem_.active_ = SELECT_START;
            }
            break;
    }
    menuItem_.resetResult();
}

THUMB void MaterielMenu_SlimeTouch::okUpdate()
{
    switch (menuItem_.getActive()) {
        case SELECT_START:
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            status::g_TouchData.setUp();
            g_Global.startSlimeTouch();
            break;
        case SELECT_RANKING:
            if (status::g_TouchData.ranking_[0].stage == 0) {
                mode_ = MODE_NOTRANKIN;
            }
            else {
                mode_ = MODE_RANKING;
            }
            break;
        case SELECT_TUTORIAL:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0);
            mode_ = MODE_TUTORIAL;
            break;
        case SELECT_END:
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

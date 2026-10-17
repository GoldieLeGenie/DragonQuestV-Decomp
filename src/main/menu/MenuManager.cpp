#include "main/menu/MenuManager.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuBg.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"

inline void menu::MenuBase::setStat(MENUBASE_STAT s)
{
    stat_ = s;
}

static int s_menuTime;
static MenuSubManager* s_currentMenu;
static int s_requestEnable;
static int s_unk;
static MENUDISPLAY_MODE s_mode;
static MENUDISPLAY_MODE s_next;
static int s_change_count;
static int s_enable;
static int s_redrawTime;
static int s_drawTime;
static int s_redraw;
static int s_updateTime;
static MenuSubManager s_normalMenu;
static MenuSubManager s_extraMenu;

THUMB void MenuManager::setup()
{
    s_normalMenu.setup();
    s_extraMenu.setup();
    s_currentMenu = &s_normalMenu;
    s_mode = MENUDISPLAY_OFF;
    s_next = MENUDISPLAY_OFF;
    s_change_count = 0;
    s_enable = 1;
    s_requestEnable = 1;
    s_redraw = 1;
}

THUMB void MenuManager::setMenuDisplay(int mode)
{
    if (mode == MENUDISPLAY_OFF) {
        unkfunc_0204d050(4);
        data_02106178.icon_.unkfunc_0206375c(0);
        unkfunc_0204cc9c(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    }
    if (mode == MENUDISPLAY_NORMAL) {
        unkfunc_0204d050(4);
        data_02106178.icon_.unkfunc_0206375c(0);
        unkfunc_0204cc9c(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    }
    if (mode == MENUDISPLAY_EXTRA) {
        unkfunc_0204d050(4);
        unkfunc_0204cc9c(&dss::g_DISPLAYPLUGIN_CAPTURE);
        data_02106178.icon_.unkfunc_0206375c(1);
    }
    clearMenuAll();
    data_020f6f9c.unkfunc_0204affc();
    s_currentMenu->m_update = 1;
}

THUMB void MenuManager::requestMenuMode(MENUDISPLAY_MODE mode)
{
    if (s_mode != mode) {
        s_next = mode;
        s_change_count = 0;
        setMenuDisplay(MENUDISPLAY_OFF);
    }
}

THUMB int MenuManager::isMenuMode(MENUDISPLAY_MODE mode)
{
    if (s_mode == mode) {
        return 1;
    }
    return 0;
}

THUMB int MenuManager::isRequesting()
{
    if (s_mode != s_next) {
        return 1;
    }
    return 0;
}

THUMB void MenuManager::execute()
{
    if (s_enable != s_requestEnable) {
        s_enable = s_requestEnable;
        s_redraw = 1;
        if (!s_enable) {
            unkfunc_02061bd8(s_redraw);
            unkfunc_02063568();
            return;
        }
    }
    if (!s_enable) {
        return;
    }
    if (s_mode != s_next) {
        if (s_change_count == 2) {
            s_mode = s_next;
            s_change_count = 0;
            setMenuDisplay(s_mode);
        }
        s_change_count++;
    }
    s_currentMenu->execute();
    if (s_currentMenu->m_update) {
        s_redraw = 1;
    }
    int time = unkfunc_0204afe0();
    unkfunc_02061bd8(s_redraw);
    s_currentMenu->draw(0, 0xC0);
    s_currentMenu->m_update = 0;
    int drawTime = unkfunc_0204afe0() - time;
    if (s_redraw) {
        unkfunc_02063568();
    }
    time = unkfunc_0204afe0();
    s_currentMenu->update();
    int updateTime = unkfunc_0204afe0() - time;
    if (s_redraw) {
        s_redraw = 0;
        s_redrawTime = drawTime;
    } else {
        s_drawTime = drawTime;
    }
    s_menuTime = updateTime;
}

THUMB void MenuManager::addMenu(menu::MenuBase* menu)
{
    s_currentMenu->addMenu(menu);
    menu->setStat(menu::MenuBase::MENUBASE_STAT_ACTIVE);
}

THUMB void MenuManager::deleteMenu(menu::MenuBase* menu)
{
    s_currentMenu->deleteMenu(menu);
}

THUMB void MenuManager::clearMenuAll()
{
    s_currentMenu->clearMenuAll();
}

THUMB int MenuManager::isOpenMenu(menu::MenuBase* menu)
{
    return s_currentMenu->isOpenMenu(menu);
}

THUMB int MenuManager::getUpdateTime()
{
    return s_updateTime;
}

THUMB void MenuManager::setMenuEnable(int enable)
{
    s_requestEnable = enable;
    s_redraw = 1;
}

THUMB int MenuManager::isExtraMenu()
{
    if (s_currentMenu == &s_extraMenu) {
        return 1;
    }
    return 0;
}

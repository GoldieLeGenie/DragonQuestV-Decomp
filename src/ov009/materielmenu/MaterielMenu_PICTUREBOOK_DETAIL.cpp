#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_DETAIL.hpp"
#include "ov009/materielmenu/MaterielMenu_PICTUREBOOK_ROOT.hpp"
#include "ov009/book/BookMonsterDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/BattleResult.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

inline void menu::MenuPlayerControl::setActiveItem(short item) { activeItem_ = item; }
inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active) { activeItemPage_ = active; }

THUMB void MaterielMenu_PICTUREBOOK_DETAIL::menuSetup()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.enableSE_ = 0;
    short active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    activeMonster_ = active + (menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ << 4);
    monsterIndex_ = status::g_BattleResult.getMonsterIndex(activeMonster_);
    navigator_.setupBase();
    navigator_.setup(1, 1, 0xca);
    navigator_.setPageNo(activeMonster_);
    book::BookMonsterDraw::getSingleton().setup(monsterIndex_);
}

THUMB void MaterielMenu_PICTUREBOOK_DETAIL::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_MONSTERANIME(&menuItem_);
}

THUMB void MaterielMenu_PICTUREBOOK_DETAIL::menuDraw()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    drawMonsterBookDetailScreen(activeMonster_);
    menuItem_.drawActive();
}

THUMB void MaterielMenu_PICTUREBOOK_DETAIL::menuUpdate()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    navigator_.setup(1, 1, 0xca);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (result == 3) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(activeMonster_ % 16);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(activeMonster_ / 16);
        close();
        gMaterielMenu_PICTUREBOOK_ROOT.open();
    }
    if (result == 7) {
        activeMonster_ = navigator_.getIndex(0);
        checkPage(true);
        book::BookMonsterDraw::getSingleton().setup(monsterIndex_);
    }
    if (result == 6) {
        activeMonster_ = navigator_.getIndex(0);
        checkPage(false);
        book::BookMonsterDraw::getSingleton().setup(monsterIndex_);
    }
    redraw_ = 1;
}

THUMB void MaterielMenu_PICTUREBOOK_DETAIL::checkPage(bool next)
{
    while (!status::g_BattleResult.isMonsterEncount(activeMonster_)) {
        if (next) {
            activeMonster_++;
            if (activeMonster_ > 0xd1) {
                activeMonster_ = 0;
            }
        } else {
            activeMonster_--;
            if (activeMonster_ < 0) {
                activeMonster_ = 0xd1;
            }
        }
    }
    navigator_.setPageNo(activeMonster_);
    monsterIndex_ = status::g_BattleResult.getMonsterIndex(activeMonster_);
}

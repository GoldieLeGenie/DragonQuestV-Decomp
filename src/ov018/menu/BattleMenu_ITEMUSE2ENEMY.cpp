#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_ITEMUSE2ENEMY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unk_148 = 0;
    unk_14c = 0;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    unk_160 = 0;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_02175a70(&menuItem_);
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_02170084();
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unk_158 = menuItem_.active_;
    if (unkfunc_02173134() && unk_160 == 0) {
        unkfunc_0217310c();
    }
}

THUMB void BattleMenu_ITEMUSE2ENEMY::unkfunc_021730b8()
{
    unk_15c = 0;
    BattleMenuJudge::getSingleton()->setItemEnemy(unk_14c, gBattleMenu_ATTACK.touchRect_[gBattleMenu_ATTACK.menuItem_.active_].group);
    BattleMenuJudge::getSingleton()->setNextPlayer();
    gBattleMenu_ATTACK.unk_f4 = 1;
    close();
    unk_160 = 1;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::unkfunc_0217310c()
{
    menuItem_.execInput();
    int result = menuItem_.result_;
    if (result != menu::MenuItem::MENUITEM_RESULT_NONE && result == menu::MenuItem::MENUITEM_RESULT_OK) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        unkfunc_021730b8();
    }
}

THUMB int BattleMenu_ITEMUSE2ENEMY::unkfunc_02173134()
{
    if ((unsigned int)(menuItem_.result_ - menu::MenuItem::MENUITEM_RESULT_CANCEL) <= 1) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        unk_15c = 0;
        close();
        unk_160 = 1;
        gBattleMenu_ITEM.open();
        return 0;
    }
    return 1;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::unkfunc_0217316c(int chara, int item)
{
    unk_148 = chara;
    unk_14c = item;
}

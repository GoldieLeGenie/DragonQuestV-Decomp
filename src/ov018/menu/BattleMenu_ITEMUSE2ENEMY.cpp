#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_ITEMUSE2ENEMY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    activeChara_ = 0;
    activeItem_ = 0;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    isEnd_ = 0;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    setupBattleFightCancel(&menuItem_);
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    drawItemUseOnEnemyMenu();
}

THUMB void BattleMenu_ITEMUSE2ENEMY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    oldActive_ = menuItem_.active_;
    if (unkfunc_02173134() && isEnd_ == 0) {
        unkfunc_0217310c();
    }
}

THUMB void BattleMenu_ITEMUSE2ENEMY::decideTarget()
{
    monsterMask_ = 0;
    BattleMenuJudge::getSingleton()->setItemEnemy(activeItem_, gBattleMenu_ATTACK.touchRect_[gBattleMenu_ATTACK.menuItem_.active_].group);
    BattleMenuJudge::getSingleton()->setNextPlayer();
    gBattleMenu_ATTACK.isDecided_ = 1;
    close();
    isEnd_ = 1;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::unkfunc_0217310c()
{
    menuItem_.execInput();
    int result = menuItem_.result_;
    if (result != menu::MenuItem::MENUITEM_RESULT_NONE && result == menu::MenuItem::MENUITEM_RESULT_OK) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        decideTarget();
    }
}

THUMB int BattleMenu_ITEMUSE2ENEMY::unkfunc_02173134()
{
    if ((unsigned int)(menuItem_.result_ - menu::MenuItem::MENUITEM_RESULT_CANCEL) <= 1) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        monsterMask_ = 0;
        close();
        isEnd_ = 1;
        gBattleMenu_ITEM.open();
        return 0;
    }
    return 1;
}

THUMB void BattleMenu_ITEMUSE2ENEMY::setItem(int chara, int item)
{
    activeChara_ = chara;
    activeItem_ = item;
}

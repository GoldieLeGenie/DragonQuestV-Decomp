#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "main/menu/MenuStatusInfo.hpp"

using menu::MenuStatusInfo;

THUMB void UnkBattleMenuAttackCancel::menuSetup()
{
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
}

THUMB void UnkBattleMenuAttackCancel::menuExecute()
{
    setupBattleFightCancel(&menuItem_);
}

THUMB void UnkBattleMenuAttackCancel::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    drawAttackCancelMenu();
}

THUMB void UnkBattleMenuAttackCancel::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.execInput();
    int result = menuItem_.result_;
    if ((unsigned int)(result - menu::MenuItem::MENUITEM_RESULT_CANCEL) <= 1) {
        gBattleMenu_ACTIONMENU.open();
        gBattleMenu_ACTIONMENU.pageItem_.active_ = 0;
        btl::BattleMonsterMask::getSingleton()->select(-1);
        close();
        return;
    }
    if (result == menu::MenuItem::MENUITEM_RESULT_OK) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        decideAttack();
    }
}

THUMB void UnkBattleMenuAttackCancel::decideAttack()
{
    BattleMenuJudge::getSingleton()->setAttack(gBattleMenu_ATTACK.touchRect_[gBattleMenu_ATTACK.menuItem_.active_].group);
    BattleMenuJudge::getSingleton()->setNextPlayer();
    btl::BattleMonsterMask::getSingleton()->select(-1);
    redraw_ = 1;
    gBattleMenu_ATTACK.unk_f4 = 1;
    close();
}

#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"

using menu::MenuStatusInfo;

inline void BattleMenuJudge::setMinadeinFlag(bool flag) { minadeinFlag_ = flag; }

THUMB void BattleMenu_MAGIC2ENEMY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    activeMagicIndex_ = 0;
}

THUMB void BattleMenu_MAGIC2ENEMY::menuExecute()
{
    setupBattleFightCancel(&menuItem_);
}

THUMB void BattleMenu_MAGIC2ENEMY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    drawMagicOnEnemyMenu();
}

THUMB void BattleMenu_MAGIC2ENEMY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    menuItem_.execInput();
    int result = menuItem_.result_;
    if ((unsigned int)(result - menu::MenuItem::MENUITEM_RESULT_CANCEL) <= 1) {
        MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::UseAction, -1);
        gBattleMenu_MAGIC.open();
        gBattleMenu_MAGIC.setActiveMagicPos(activeMagicPos_);
        gBattleMenu_ATTACK.isDecided_ = 1;
        close();
        return;
    }
    if (result == menu::MenuItem::MENUITEM_RESULT_OK) {
        redraw_ = 1;
        gBattleMenu_ATTACK.close();
        close();
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        if (MenuStatusInfo::getHaveStatusInfo(chara).haveAction_.getAction(activeMagicIndex_) == 0x12) {
            BattleMenuJudge::getSingleton()->setMinadeinFlag(true);
        }
        BattleMenuJudge::getSingleton()->setMagicEnemy(activeMagicIndex_, gBattleMenu_ATTACK.touchRect_[gBattleMenu_ATTACK.menuItem_.active_].group);
        BattleMenuJudge::getSingleton()->setNextPlayer();
    }
}

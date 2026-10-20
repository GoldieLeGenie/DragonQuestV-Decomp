#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/status/HaveBattleStatus.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_MAGIC2PARTY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    partyMax_ = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    m_magic = BattleMenuPlayerControl::getSingleton()->activeMagic_;
    if (isReviveMagic(MenuStatusInfo::getPlayerActionID(BattleMenuPlayerControl::getSingleton()->activeChara_, m_magic))) {
        for (int i = 0; i < partyMax_; i++) {
            if (MenuStatusInfo::getHaveStatusInfo(i).isDeath()) {
                menuItem_.active_ = i;
                return;
            }
        }
    }
}

THUMB void BattleMenu_MAGIC2PARTY::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    navigator_.setup(2, 2, partyMax_);
    setupBattleParty2x2(&menuItem_, partyMax_);
    setupBattleCancel(&cancelItem_);
}

THUMB void BattleMenu_MAGIC2PARTY::menuDraw()
{
    drawMagicOnPartyMenu();
    menuItem_.drawActive();
}

THUMB void BattleMenu_MAGIC2PARTY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::UseAction, -1);
        close();
        gBattleMenu_MAGIC.open();
        gBattleMenu_MAGIC.setActiveMagicPos(activeMagicPos_);
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 2) {
            close();
            BattleMenuJudge::getSingleton()->setMagicParty(m_magic, menuItem_.active_);
            BattleMenuJudge::getSingleton()->setNextPlayer();
        }
        int target = menuItem_.active_;
        BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
        return;
    }
    int target = menuItem_.active_;
    BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
}

THUMB bool BattleMenu_MAGIC2PARTY::isReviveMagic(int action)
{
    if (action == 0x3d) {
        return true;
    }
    if (action == 0x3e) {
        return true;
    }
    return false;
}

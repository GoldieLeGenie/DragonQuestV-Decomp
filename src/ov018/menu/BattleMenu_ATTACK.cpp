#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"

using menu::MenuStatusInfo;

inline void BattleMenuPlayerControl::setTargetChara(int target) { targetChara_ = target; }

THUMB void BattleMenu_ATTACK::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    enemyMaxNum_ = 0;
    unk_e8 = 0;
    unk_ec = 0;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_NONE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.active_ = 0;
    menuItem_.enableSE_ = 0;
    cancelItem_.enableSE_ = 0;
    enemyMaxNum_ = BattleMenuJudge::getSingleton()->getMonsterTouchRect(touchRect_);
    for (int i = 0; i < enemyMaxNum_; i++) {
        if (touchRect_[i].group == BattleMenuPlayerControl::getSingleton()->getTargetGroup()) {
            menuItem_.active_ = i;
            break;
        }
    }
    BattleMenuPlayerControl::getSingleton()->setTargetChara(touchRect_[menuItem_.active_].group);
    BattleMenuPlayerControl::getSingleton()->setTargetGroup(touchRect_[menuItem_.active_].group);
    unk_f0 = 1;
    unk_f4 = 0;
}

THUMB void BattleMenu_ATTACK::menuExecute()
{
    if (unk_f4 == 0) {
        btl::BattleMonsterMask::getSingleton()->execute();
        enemyMaxNum_ = BattleMenuJudge::getSingleton()->getMonsterTouchRect(touchRect_);
        unkfunc_02175b88(&menuItem_, menuItem_.active_, touchRect_, enemyMaxNum_);
        unkfunc_02175a5c(&cancelItem_);
        if (unk_f0 == 1) {
            btl::BattleMonsterMask::getSingleton()->select(touchRect_[menuItem_.active_].group);
        } else {
            btl::BattleMonsterMask::getSingleton()->select(-1);
        }
    }
}

THUMB void BattleMenu_ATTACK::menuDraw()
{
    if (unk_f4 == 0) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        unkfunc_0217008c(touchRect_[menuItem_.active_].group);
    }
}

THUMB void BattleMenu_ATTACK::menuUpdate()
{
    if (unk_f4 != 0) {
        close();
        return;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unk_e8 = touchRect_[menuItem_.active_].group;
    unk_ec = menuItem_.active_;
    if (unkfunc_02175f50()) {
        unkfunc_02175e7c();
    }
}

THUMB void BattleMenu_ATTACK::unkfunc_02175df0(int index)
{
    while (index != unk_ec) {
        if (index == enemyMaxNum_) {
            index = 0;
            continue;
        }
        if (unk_e8 != touchRect_[index].group) {
            menuItem_.active_ = index;
            return;
        }
        index++;
    }
}

THUMB void BattleMenu_ATTACK::unkfunc_02175e34(int index)
{
    while (index != unk_ec) {
        if (index == -1) {
            index = enemyMaxNum_ - 1;
            continue;
        }
        if (unk_e8 != touchRect_[index].group) {
            menuItem_.active_ = index;
            return;
        }
        index--;
    }
}

THUMB void BattleMenu_ATTACK::unkfunc_02175e7c()
{
    menuItem_.execInput();
    switch (menuItem_.result_) {
    case menu::MenuItem::MENUITEM_RESULT_CHANGE:
        redraw_ = 1;
        if (unk_e8 == touchRect_[menuItem_.active_].group) {
            if (unk_ec < menuItem_.active_) {
                unkfunc_02175df0(menuItem_.active_);
            } else {
                unkfunc_02175e34(menuItem_.active_);
            }
        }
        break;
    case menu::MenuItem::MENUITEM_RESULT_OK:
        redraw_ = 1;
        break;
    case menu::MenuItem::MENUITEM_RESULT_UP:
    case menu::MenuItem::MENUITEM_RESULT_LEFT:
        redraw_ = 1;
        unkfunc_02175e34(enemyMaxNum_ - 1);
        break;
    case menu::MenuItem::MENUITEM_RESULT_DOWN:
    case menu::MenuItem::MENUITEM_RESULT_RIGHT:
        redraw_ = 1;
        unkfunc_02175df0(0);
        break;
    }
    menuItem_.result_ = 0;
    menuItem_.lastresult_ = 0;
    BattleMonsterNamePlate::getSingleton().maxPriority(touchRect_[menuItem_.active_].group);
    BattleMenuPlayerControl::getSingleton()->setTargetChara(touchRect_[menuItem_.active_].group);
    BattleMenuPlayerControl::getSingleton()->setTargetGroup(touchRect_[menuItem_.active_].group);
}

THUMB bool BattleMenu_ATTACK::unkfunc_02175f50()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        unk_f0 = 0;
        close();
        return false;
    }
    return true;
}

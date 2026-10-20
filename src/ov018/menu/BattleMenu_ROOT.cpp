#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB void BattleMenu_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    BattleMenuPlayerControl::getSingleton()->clear();
    BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
    BattleMenuJudge::getSingleton()->turnSetup();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    if (!gBattleMenuSub_HISTORY.isOpen()) {
        gBattleMenuSub_HISTORY.open();
        gBattleMenuSub_HISTORY.commandChara_ = -1;
    }
    gBattleMenuSub_HISTORY.update_ = 1;
    gBattleMenuSub_HISTORY.history_ = 1;
    navigator_.setupBase();
    isCancelWait_ = 0;
    cancelWait_ = 0;
}

THUMB void BattleMenu_ROOT::menuExecute()
{
    if (isCancelWait_ != 0) {
        cancelWait_--;
        menuItem_.active_ = 0;
        if (cancelWait_ <= 0) {
            cancelWait_ = 0;
            isCancelWait_ = 0;
            redraw_ = 1;
        }
        return;
    }
    navigator_.setup(2, 2, 4);
    setupBattleMenuIcon2x2(&menuItem_, 4, menuItem_.active_);
    setupBattleEnemyRect(&cancelItem_);
}

THUMB void BattleMenu_ROOT::menuDraw()
{
    if (isCancelWait_ == 0) {
        drawBattleRootMenu();
        menuItem_.drawActive();
    }
}

THUMB void BattleMenu_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (isCancelWait_ == 0) {
        if (gTownMenu_MESSAGE.isOpen()) {
            if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
                gTownMenu_MESSAGE.close();
                return;
            }
        } else {
            cancelItem_.execInput();
            if (cancelItem_.result_ == menu::MenuItem::MENUITEM_RESULT_CANCEL) {
                isCancelWait_ = 1;
                cancelWait_ = 8;
                cancelItem_.result_ = 0;
                cancelItem_.lastresult_ = 0;
                redraw_ = 1;
                return;
            }
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result == 0) {
                return;
            }
            short active = menuItem_.active_;
            if (result != 2) {
                return;
            }
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            switch (active) {
            case 0:
                close();
                BattleMenuJudge::getSingleton()->setNextPlayer();
                break;
            case 1:
                MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
                if (status::g_Party.getCount() > 1) {
                    close();
                    gBattleMenu_ARRAYMENU.open();
                    break;
                }
                close();
                gBattleMenu_NGMESSAGE.open();
                gBattleMenu_NGMESSAGE.messageID_ = 0xc3d3d;
                gBattleMenu_NGMESSAGE.returnPos_ = 1;
                gBattleMenu_NGMESSAGE.returnMenu_ = BattleMenu_NGMESSAGE::MENU_ROOT;
                break;
            case 2: {
                MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
                int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
                for (int i = 0; i < count; i++) {
                    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
                    if (info.getHaveStatus().isPlayer() && info.getHaveStatus().getPlayerIndex() > 2) {
                        close();
                        gBattleMenu_TACTICSMENU.open();
                        return;
                    }
                }
                close();
                gBattleMenu_NGMESSAGE.open();
                gBattleMenu_NGMESSAGE.messageID_ = 0xc3d3f;
                gBattleMenu_NGMESSAGE.returnPos_ = 2;
                gBattleMenu_NGMESSAGE.returnMenu_ = BattleMenu_NGMESSAGE::MENU_ROOT;
                break;
            }
            case 3:
                close();
                gBattleMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                btl::BattleActorManager::getSingleton()->setEscape(true);
                break;
            }
        }
    }
}

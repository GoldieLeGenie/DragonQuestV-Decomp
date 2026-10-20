#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void BattleMenuJudge::setMinadeinFlag(bool flag) { minadeinFlag_ = flag; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }

THUMB void BattleMenu_MAGIC::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    pageItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    btl::BattleMonsterMask::getSingleton()->select(-1);
    count_ = 0;
    for (int i = 0; i < 30; i++) {
        haveAction_[i] = -1;
        haveActionIndex_[i] = -1;
    }
    setupActionList();
    navigator_.setupBase();
    navigator_.setup(2, 3, count_);
    int pos = BattleMenuPlayerControl::getSingleton()->getMagicPosition();
    int magic = haveActionIndex_[pos];
    BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
    int page = pos / 6;
    pos = pos % 6;
    menuItem_.active_ = pos;
    navigator_.setPageNo(page);
}

THUMB void BattleMenu_MAGIC::setActiveMagicPos(int pos)
{
    int active = pos;
    active %= 6;
    menuItem_.active_ = active;
    navigator_.setPageNo(pos / 6);
}

THUMB void BattleMenu_MAGIC::menuExecute()
{
    navigator_.setup(2, 3, count_);
    setupBattleMagic2x3(&menuItem_, navigator_.getCountInPage());
    setupBattleCancel(&cancelItem_);
    int max = navigator_.getPageMaxCount() - 1;
    setupBattlePageArrow(&pageItem_, navigator_.getIndex(pageItem_.active_), max, 0xd8, 0x78);
}

THUMB void BattleMenu_MAGIC::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (!gTownMenu_MESSAGE.isOpen()) {
        drawMagicMenu(haveAction_, count_, navigator_.getPageNo());
        menuItem_.drawActive();
        cancelItem_.drawActive();
    }
}

THUMB void BattleMenu_MAGIC::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    short pos = navigator_.getIndex(menuItem_.active_);
    int action = haveAction_[pos];
    int magic = haveActionIndex_[navigator_.getIndex(menuItem_.active_)];
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo((short)chara);
    TextAPI::setMACRO0(1, 0x50000000, info.getPlayerIndex());
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        BattleMenuJudge::getSingleton()->backActionMenu(1);
        close();
        return;
    }
    int active = menuItem_.active_;
    if (MenuUpdate_Assist::isPageFlipOne(pageItem_, navigator_, active)) {
        menuItem_.active_ = active;
        redraw_ = 1;
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 2) {
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
            if (!status::UseAction::isUse(action, info)) {
                gTownMenu_MESSAGE.openMessageForBATTLE();
                gTownMenu_MESSAGE.addMessage(0xc3b73);
                gTownMenu_MESSAGE.setMessageLastCursor(false);
                BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
                return;
            }
            if (action == 0x12 && !status::PartyStatusUtility::isExecMinadein()) {
                gTownMenu_MESSAGE.openMessageForBATTLE();
                gTownMenu_MESSAGE.addMessage(0xc3948);
                gTownMenu_MESSAGE.setMessageLastCursor(false);
                BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
                return;
            }
            BattleMenuPlayerControl::getSingleton()->setMagicPosition(pos);
            switch (status::UseAction::getUseType(action)) {
            case status::UseAction::Enemy:
                setMagicTargetEnemy(action, magic);
                break;
            case status::UseAction::Friend:
                if (status::UseAction::getUseArea(action) == status::UseAction::One) {
                    BattleMenuJudge::getSingleton()->setMagicParty(magic, -1);
                    BattleMenuPlayerControl::getSingleton()->targetChara_ = 0;
                    close();
                    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT) > 1) {
                        BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
                        gBattleMenu_MAGIC2PARTY.open();
                        gBattleMenu_MAGIC2PARTY.activeMagicPos_ = navigator_.getIndex(menuItem_.active_);
                    } else {
                        BattleMenuJudge::getSingleton()->setMagicParty(magic, 0);
                        BattleMenuJudge::getSingleton()->setNextPlayer();
                    }
                } else {
                    setMagicTargetFree(magic);
                }
                break;
            default:
                setMagicTargetFree(magic);
                break;
            }
        }
    }
    BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
}

THUMB void BattleMenu_MAGIC::setMagicTargetEnemy(int action, int magic)
{
    if (status::UseAction::getUseArea(action) == status::UseAction::Group || status::UseAction::getUseArea(action) == status::UseAction::One) {
        if (status::g_Monster.getGroupCount() > 1) {
            BattleMenuJudge::getSingleton()->setMagicEnemy(magic, -1);
            int target = BattleMenuJudge::getSingleton()->getLiveMonsterID();
            BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
            close();
            BattleMonsterNamePlate::getSingleton().init();
            BattleMonsterNamePlate::getSingleton().setMonster();
            BattleMenuPlayerControl::getSingleton()->activeMagic_ = magic;
            gBattleMenu_ATTACK.open();
            gBattleMenu_MAGIC2ENEMY.open();
            gBattleMenu_MAGIC2ENEMY.activeMagicPos_ = navigator_.getIndex(menuItem_.active_);
            gBattleMenu_MAGIC2ENEMY.activeMagicIndex_ = magic;
            return;
        }
        if (action == 0x12) {
            BattleMenuJudge::getSingleton()->setMinadeinFlag(true);
        }
        close();
        int group = 0;
        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            if (status::g_Monster.getMonsterStatus(i).isEnable()) {
                group = status::g_Monster.getMonsterGroup(i);
                break;
            }
        }
        BattleMenuJudge::getSingleton()->setMagicEnemy(magic, group);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        return;
    }
    setMagicTargetFree(magic);
}

THUMB void BattleMenu_MAGIC::setupActionList()
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    int count = info.haveAction_.getCount();
    int num = 0;
    count_ = num;
    for (int i = 0; i < 30; i++) {
        haveAction_[i] = -1;
        haveActionIndex_[i] = -1;
    }
    for (int i = 0; i < count; i++) {
        int action = info.haveAction_.getAction(i);
        if (status::UseAction::isBattleUse(action)) {
            haveAction_[num] = action;
            haveActionIndex_[num] = i;
            num++;
        }
    }
    count_ = num;
}

THUMB void BattleMenu_MAGIC::setMagicTargetFree(int magic)
{
    close();
    BattleMenuJudge::getSingleton()->setMagicParty(magic, -1);
    BattleMenuJudge::getSingleton()->setNextPlayer();
}

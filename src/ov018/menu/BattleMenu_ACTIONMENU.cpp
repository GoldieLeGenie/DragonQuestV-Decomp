#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/UseAction.hpp"

using menu::MenuStatusInfo;

inline int BattleMenuJudge::getPlayerIndex() { return BattleMenuPlayerControl::getSingleton()->activeChara_; }
inline void BattleMenuPlayerControl::setTargetChara(int target) { targetChara_ = target; }
inline void BattleMenuPlayerControl::setActiveItem(int item) { activeItem_ = item; }
inline void BattleMenuPlayerControl::setActiveMagic(int magic) { activeMagic_ = magic; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline bool status::HaveStatus::isFriendMonster() const { return playerType_ == TYPE_FRIENDMONSTER; }

THUMB void BattleMenu_ACTIONMENU::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    pageItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    btl::BattleMonsterMask::getSingleton()->select(-1);
    activeCharacter_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
    gBattleMenuSub_HISTORY.commandChara_ = activeCharacter_;
    MenuStatusInfo::getHaveBattleStatus(activeCharacter_).setSelectCommand(status::HaveBattleStatus::NoSelect, 0);
    unk_14c = -1;
    navigator_.setupBase();
}

THUMB void BattleMenu_ACTIONMENU::menuExecute()
{
    navigator_.setup(2, 2, 4);
    setupBattleEnemyRect(&menuItem_);
    setupBattleMenuIcon2x2(&pageItem_, 4, pageItem_.active_);
    setupBattleCancel(&cancelItem_);
}

THUMB void BattleMenu_ACTIONMENU::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int x = 0xf0;
    int chara = activeCharacter_;
    if (BattleMenuPlayerControl::getSingleton()->historyData_[chara].special) {
        x += 0xe0;
    }
    drawBattleActionMenu(x);
    pageItem_.drawActive();
}

THUMB void BattleMenu_ACTIONMENU::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        close();
        BattleMenuJudge::getSingleton()->setPrevPlayer();
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(pageItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (result == 1) {
        if (unk_14c == -1) {
            gBattleMenuSub_HISTORY.select_ = BattleMenuJudge::getSingleton()->getPlayerIndex();
        }
        unk_14c = pageItem_.active_;
    }
    if (result == 2) {
        if (unk_14c == -1) {
            gBattleMenuSub_HISTORY.select_ = BattleMenuJudge::getSingleton()->getPlayerIndex();
        }
        pageItem_.result_ = 0;
        pageItem_.lastresult_ = 0;
        switch (pageItem_.active_) {
        case 0:
            selectAttack();
            return;
        case 1:
            selectMagic();
            return;
        case 2:
            selectItem();
            return;
        case 3:
            selectDefence();
            return;
        }
    }
}

THUMB int BattleMenu_ACTIONMENU::getUseActionNum(int& index)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    int count = info.haveAction_.getCount();
    int num = 0;
    for (int i = 0; i < count; i++) {
        if (status::UseAction::isBattleUse(info.haveAction_.getAction(i))) {
            num++;
        }
        if (num == 1) {
            index = i;
        }
    }
    return num;
}

THUMB void BattleMenu_ACTIONMENU::selectAttack()
{
    int groupCount = status::g_Monster.getGroupCount();
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    int weapon = MenuStatusInfo::getHaveStatusInfo(chara).haveEquipment_.getEquipment(ITEM_WEAPON, 0);
    if (groupCount > 1 && !isWeaponAll(weapon)) {
        close();
        status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(chara);
        battleStatus.setSelectCommand(status::HaveBattleStatus::Attack, 0);
        battleStatus.selectedGroup_ = -1;
        BattleMenuPlayerControl::getSingleton()->setTargetChara(BattleMenuPlayerControl::getSingleton()->getTargetGroup());
        gBattleMenu_ATTACK.open();
        gUnkBattleMenuAttackCancel.open();
        return;
    }
    close();
    BattleMenuJudge::getSingleton()->setAttack(status::g_Monster.getMonsterGroup(0));
    BattleMenuJudge::getSingleton()->setNextPlayer();
}

THUMB void BattleMenu_ACTIONMENU::selectMagic()
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    int index = 0;
    if (getUseActionNum(index)) {
        close();
        BattleMenuPlayerControl::getSingleton()->setActiveMagic(index);
        MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::UseAction, -1);
        gBattleMenu_MAGIC.open();
        return;
    }
    if (MenuStatusInfo::getHaveStatusInfo(chara).getHaveStatus().isFriendMonster()) {
        close();
        gBattleMenu_NGMESSAGE.open();
        gBattleMenu_NGMESSAGE.messageID_ = 0xc3d61;
        gBattleMenu_NGMESSAGE.returnPos_ = 1;
        gBattleMenu_NGMESSAGE.returnMenu_ = BattleMenu_NGMESSAGE::MENU_ACTIONMENU;
        return;
    }
    close();
    gBattleMenu_NGMESSAGE.open();
    gBattleMenu_NGMESSAGE.messageID_ = 0xc3b75;
    gBattleMenu_NGMESSAGE.returnPos_ = 1;
    gBattleMenu_NGMESSAGE.returnMenu_ = BattleMenu_NGMESSAGE::MENU_ACTIONMENU;
}

THUMB void BattleMenu_ACTIONMENU::selectItem()
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (MenuStatusInfo::getHaveStatusInfo(chara).haveItem_.getCount() > 0) {
        close();
        BattleMenuPlayerControl::getSingleton()->setActiveItem(-1);
        MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::UseItem, -1);
        gBattleMenu_ITEM.open();
        return;
    }
    close();
    gBattleMenu_NGMESSAGE.open();
    gBattleMenu_NGMESSAGE.messageID_ = 0xc3b7b;
    gBattleMenu_NGMESSAGE.returnPos_ = 2;
    gBattleMenu_NGMESSAGE.returnMenu_ = BattleMenu_NGMESSAGE::MENU_ACTIONMENU;
}

THUMB void BattleMenu_ACTIONMENU::selectDefence()
{
    close();
    MenuStatusInfo::getHaveBattleStatus(BattleMenuPlayerControl::getSingleton()->activeChara_).setSelectCommand(status::HaveBattleStatus::Defence, 0);
    BattleMenuJudge::getSingleton()->setNextPlayer();
}

THUMB bool BattleMenu_ACTIONMENU::isWeaponAll(int weapon)
{
    switch (weapon) {
    case 0x17:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x3d:
        return true;
    }
    return false;
}

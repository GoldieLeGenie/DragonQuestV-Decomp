#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_ITEM::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    pageItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    int i;
    activeChara_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    navigator_.setupBase();
    navigator_.setup(2, 3, info.haveItem_.getCount());
    int pos = 0;
    for (i = 0; i < info.haveItem_.getCount(); i++) {
        if (info.haveItem_.isEquipment(i) == 0) {
            pos = i;
            break;
        }
    }
    if (BattleMenuPlayerControl::getSingleton()->activeItem_ != -1) {
        pos = BattleMenuPlayerControl::getSingleton()->activeItem_;
    } else {
        BattleMenuPlayerControl::getSingleton()->activeItem_ = pos;
    }
    int page = pos / 6;
    pos = pos % 6;
    menuItem_.active_ = pos;
    navigator_.setPageNo(page);
    btl::BattleMonsterMask::getSingleton()->select(-1);
}

THUMB void BattleMenu_ITEM::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    int count = info.haveItem_.getCount();
    navigator_.setup(2, 3, info.haveItem_.getCount());
    int num = (count - 1) % 6 + 1;
    int page;
    int last = navigator_.getPageMaxCount() - 1;
    page = navigator_.getPageNo();
    if (page != last) {
        num = 6;
    }
    unkfunc_0201c8e8(&menuItem_, num, menuItem_.active_);
    unkfunc_02175a5c(&cancelItem_);
    int max = navigator_.getPageMaxCount() - 1;
    unkfunc_02175c0c(&pageItem_, pageItem_.active_, max, 0xd8, 0x78);
}

THUMB void BattleMenu_ITEM::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (!gTownMenu_MESSAGE.isOpen()) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
        int count = info.haveItem_.getCount();
        int items[12] = {0};
        for (int i = 0; i < 12; i++) items[i] = 0;
        for (int i = 0; i < count; i++) {
            items[i] = info.haveItem_.getItem(i);
        }
        drawItemMenu(items, count, navigator_.getPageNo());
        menuItem_.drawActive();
    }
}

THUMB void BattleMenu_ITEM::menuUpdate()
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
        BattleMenuJudge::getSingleton()->backActionMenu(2);
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 2) {
            if (unkfunc_02172ba8()) {
                close();
                gUnkBattleMenuEquipItem.open();
            } else {
                selectUseItem();
            }
            int item = navigator_.getIndex(menuItem_.active_);
            BattleMenuPlayerControl::getSingleton()->activeItem_ = item;
            return;
        }
        int item = navigator_.getIndex(menuItem_.active_);
        BattleMenuPlayerControl::getSingleton()->activeItem_ = item;
    }
    int active = menuItem_.active_;
    if (MenuUpdate_Assist::isPageFlipOne(pageItem_, navigator_, active) == 2) {
        menuItem_.active_ = active;
        int item = navigator_.getIndex(menuItem_.active_);
        BattleMenuPlayerControl::getSingleton()->activeItem_ = item;
        redraw_ = 1;
    }
}

THUMB void BattleMenu_ITEM::selectUseItem()
{
    int index = navigator_.getIndex(menuItem_.active_);
    int action = status::UseItem::getBattleUseAction(MenuStatusInfo::getPlayerItemID(activeChara_, index));
    status::UseAction::UseArea area = status::UseAction::getUseArea(action);
    switch (status::UseAction::getUseType(action)) {
    case status::UseAction::Myself:
        BattleMenuJudge::getSingleton()->setItemParty(index, activeChara_);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    case status::UseAction::Friend:
        if (area == status::UseAction::One) {
            BattleMenuPlayerControl::getSingleton()->targetChara_ = 0;
            gBattleMenu_ITEMUSE2PARTY.open();
            gBattleMenu_ITEMUSE2PARTY.unk_e4 = activeChara_;
            gBattleMenu_ITEMUSE2PARTY.unk_e8 = index;
            BattleMenuJudge::getSingleton()->setItemParty(index, -1);
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemPartyAll(index);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    case status::UseAction::Enemy:
        if (area != status::UseAction::All) {
            if (status::g_Monster.getGroupCount() == 1) {
                int group = 0;
                for (int i = 0; i < status::g_Monster.getCount(); i++) {
                    if (status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
                        group = status::g_Monster.getMonsterGroup(i);
                        break;
                    }
                }
                BattleMenuJudge::getSingleton()->setItemEnemy(index, group);
                BattleMenuJudge::getSingleton()->setNextPlayer();
            } else {
                BattleMonsterNamePlate::getSingleton().init();
                BattleMonsterNamePlate::getSingleton().setMonster();
                int target = BattleMenuJudge::getSingleton()->getLiveMonsterID();
                BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
                gBattleMenu_ITEMUSE2ENEMY.open();
                gBattleMenu_ATTACK.open();
                gBattleMenu_ITEMUSE2ENEMY.unkfunc_0217316c(activeChara_, index);
            }
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemEnemyAll(index);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    default:
        MenuStatusInfo::getHaveStatusInfo(activeChara_);
        MenuStatusInfo::getHaveBattleStatus(activeChara_);
        BattleMenuJudge::getSingleton()->setItemPartyAll(index);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    }
}

THUMB bool BattleMenu_ITEM::unkfunc_02172ba8()
{
    return MenuStatusInfo::isPlayerEquipEnable(activeChara_, MenuStatusInfo::getPlayerItemID(activeChara_, BattleMenuPlayerControl::getSingleton()->activeItem_));
}

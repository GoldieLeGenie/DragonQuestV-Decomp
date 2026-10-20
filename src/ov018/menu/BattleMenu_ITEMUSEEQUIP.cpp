#pragma ipa file
#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuStatusInfo;

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

THUMB void BattleMenu_ITEMUSEEQUIP::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    useEquipItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    btl::BattleMonsterMask::getSingleton()->select(-1);
    activeItem_ = BattleMenuPlayerControl::getSingleton()->activeItem_;
    activeChara_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
    unk_154 = 0;
}

THUMB void BattleMenu_ITEMUSEEQUIP::menuExecute()
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x48, 0xa8, 0x38, 0x10},
        {1, 2, 0x90, 0xa8, 0x38, 0x10},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    setupItemIcon32Layout2x3(&menuItem_, 6, (activeItem_ - 1) % 6 + 1);
    unkfunc_0217300c();
    useEquipItem_.setMenuItem(menu, 2, 1, 2);
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void BattleMenu_ITEMUSEEQUIP::menuDraw()
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
        unkfunc_02170010(items, count, BattleMenuPlayerControl::getSingleton()->activeItem_ / 6);
        useEquipItem_.drawActive();
    }
}

THUMB void BattleMenu_ITEMUSEEQUIP::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (cmn::g_cmnSoundManager.isPlaySound() == 1) {
        cmn::g_cmnSoundManager.execSound();
        unk_154 = 1;
    } else if (unk_154 == 1) {
        close();
        gBattleMenu_ITEM.open();
        gBattleMenuSub_HISTORY.update_ = 1;
    }
    if (unkfunc_02172d4c() == 0) {
        unkfunc_02172d78();
    }
    unkfunc_0217300c();
}

THUMB int BattleMenu_ITEMUSEEQUIP::unkfunc_02172d4c()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        redraw_ = 1;
        close();
        gBattleMenu_ITEM.open();
        return 1;
    }
    return 0;
}

THUMB void BattleMenu_ITEMUSEEQUIP::unkfunc_02172d78()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    useEquipItem_.execInput();
    switch (useEquipItem_.result_) {
    case menu::MenuItem::MENUITEM_RESULT_CHANGE:
        redraw_ = 1;
        return;
    case menu::MenuItem::MENUITEM_RESULT_OK:
        useEquipItem_.result_ = 0;
        useEquipItem_.lastresult_ = 0;
        redraw_ = 1;
        if (useEquipItem_.active_ == 0) {
            selectUseItem();
            return;
        }
        unkfunc_02172fc8();
        redraw_ = 1;
        if (unk_154 == 0) {
            close();
            gBattleMenu_ITEM.open();
        }
        return;
    case menu::MenuItem::MENUITEM_RESULT_LEFT:
        useEquipItem_.active_ = 1;
        return;
    case menu::MenuItem::MENUITEM_RESULT_RIGHT:
        useEquipItem_.active_ = 0;
        return;
    }
}

THUMB void BattleMenu_ITEMUSEEQUIP::selectUseItem()
{
    int action = status::UseItem::getBattleUseAction(MenuStatusInfo::getPlayerItemID(activeChara_, activeItem_));
    status::UseAction::UseArea area = status::UseAction::getUseArea(action);
    switch (status::UseAction::getUseType(action)) {
    case status::UseAction::Myself:
        BattleMenuJudge::getSingleton()->setItemParty(activeItem_, activeChara_);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    case status::UseAction::Friend:
        if (area == status::UseAction::One) {
            BattleMenuPlayerControl::getSingleton()->targetChara_ = 0;
            gBattleMenu_ITEMUSE2PARTY.open();
            int item = activeItem_;
            int chara = activeChara_;
            gBattleMenu_ITEMUSE2PARTY.activeChara_ = chara;
            gBattleMenu_ITEMUSE2PARTY.activeItem_ = item;
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemPartyAll(activeItem_);
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
                BattleMenuJudge::getSingleton()->setItemEnemy(activeItem_, group);
                BattleMenuJudge::getSingleton()->setNextPlayer();
            } else {
                BattleMonsterNamePlate::getSingleton().init();
                BattleMonsterNamePlate::getSingleton().setMonster();
                int target = BattleMenuJudge::getSingleton()->getLiveMonsterID();
                BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
                gBattleMenu_ITEMUSE2ENEMY.open();
                gBattleMenu_ATTACK.open();
                gBattleMenu_ITEMUSE2ENEMY.unkfunc_0217316c(activeChara_, activeItem_);
            }
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemEnemyAll(activeItem_);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    default:
        MenuStatusInfo::getHaveStatusInfo(activeChara_);
        MenuStatusInfo::getHaveBattleStatus(activeChara_).setSelectCommand(status::HaveBattleStatus::UseItem, activeItem_);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    }
}

THUMB void BattleMenu_ITEMUSEEQUIP::unkfunc_02172fc8()
{
    MenuStatusInfo::getHaveStatusInfo(activeChara_);
    if (!MenuStatusInfo::isPlayerEquipItem(activeChara_, MenuStatusInfo::getPlayerItemID(activeChara_, activeItem_))) {
        MenuStatusInfo::getHaveStatusInfo(activeChara_).setEquipment(activeItem_);
    }
}

THUMB void BattleMenu_ITEMUSEEQUIP::unkfunc_0217300c()
{
    equipEnable_ = MenuStatusInfo::isPlayerEquipEnable(activeChara_, MenuStatusInfo::getPlayerItemID(activeChara_, BattleMenuPlayerControl::getSingleton()->activeItem_));
}

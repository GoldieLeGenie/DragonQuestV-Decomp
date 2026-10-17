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

THUMB void UnkBattleMenuEquipItem::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    unk_e4.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    btl::BattleMonsterMask::getSingleton()->select(-1);
    unk_14c = BattleMenuPlayerControl::getSingleton()->activeItem_;
    unk_148 = BattleMenuPlayerControl::getSingleton()->activeChara_;
    unk_154 = 0;
}

THUMB void UnkBattleMenuEquipItem::menuExecute()
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x48, 0xa8, 0x38, 0x10},
        {1, 2, 0x90, 0xa8, 0x38, 0x10},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_0201c8e8(&menuItem_, 6, (unk_14c - 1) % 6 + 1);
    unkfunc_0217300c();
    unk_e4.setMenuItem(menu, 2, 1, 2);
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void UnkBattleMenuEquipItem::menuDraw()
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
        unk_e4.drawActive();
    }
}

THUMB void UnkBattleMenuEquipItem::menuUpdate()
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

THUMB int UnkBattleMenuEquipItem::unkfunc_02172d4c()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        redraw_ = 1;
        close();
        gBattleMenu_ITEM.open();
        return 1;
    }
    return 0;
}

THUMB void UnkBattleMenuEquipItem::unkfunc_02172d78()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    unk_e4.execInput();
    switch (unk_e4.result_) {
    case menu::MenuItem::MENUITEM_RESULT_CHANGE:
        redraw_ = 1;
        return;
    case menu::MenuItem::MENUITEM_RESULT_OK:
        unk_e4.result_ = 0;
        unk_e4.lastresult_ = 0;
        redraw_ = 1;
        if (unk_e4.active_ == 0) {
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
        unk_e4.active_ = 1;
        return;
    case menu::MenuItem::MENUITEM_RESULT_RIGHT:
        unk_e4.active_ = 0;
        return;
    }
}

THUMB void UnkBattleMenuEquipItem::selectUseItem()
{
    int action = status::UseItem::getBattleUseAction(MenuStatusInfo::getPlayerItemID(unk_148, unk_14c));
    status::UseAction::UseArea area = status::UseAction::getUseArea(action);
    switch (status::UseAction::getUseType(action)) {
    case status::UseAction::Myself:
        BattleMenuJudge::getSingleton()->setItemParty(unk_14c, unk_148);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    case status::UseAction::Friend:
        if (area == status::UseAction::One) {
            BattleMenuPlayerControl::getSingleton()->targetChara_ = 0;
            gBattleMenu_ITEMUSE2PARTY.open();
            int item = unk_14c;
            int chara = unk_148;
            gBattleMenu_ITEMUSE2PARTY.unk_e4 = chara;
            gBattleMenu_ITEMUSE2PARTY.unk_e8 = item;
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemPartyAll(unk_14c);
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
                BattleMenuJudge::getSingleton()->setItemEnemy(unk_14c, group);
                BattleMenuJudge::getSingleton()->setNextPlayer();
            } else {
                BattleMonsterNamePlate::getSingleton().init();
                BattleMonsterNamePlate::getSingleton().setMonster();
                int target = BattleMenuJudge::getSingleton()->getLiveMonsterID();
                BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
                gBattleMenu_ITEMUSE2ENEMY.open();
                gBattleMenu_ATTACK.open();
                gBattleMenu_ITEMUSE2ENEMY.unkfunc_0217316c(unk_148, unk_14c);
            }
            close();
            return;
        }
        BattleMenuJudge::getSingleton()->setItemEnemyAll(unk_14c);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    default:
        MenuStatusInfo::getHaveStatusInfo(unk_148);
        MenuStatusInfo::getHaveBattleStatus(unk_148).setSelectCommand(status::HaveBattleStatus::UseItem, unk_14c);
        BattleMenuJudge::getSingleton()->setNextPlayer();
        close();
        return;
    }
}

THUMB void UnkBattleMenuEquipItem::unkfunc_02172fc8()
{
    MenuStatusInfo::getHaveStatusInfo(unk_148);
    if (!MenuStatusInfo::isPlayerEquipItem(unk_148, MenuStatusInfo::getPlayerItemID(unk_148, unk_14c))) {
        MenuStatusInfo::getHaveStatusInfo(unk_148).setEquipment(unk_14c);
    }
}

THUMB void UnkBattleMenuEquipItem::unkfunc_0217300c()
{
    unk_150 = MenuStatusInfo::isPlayerEquipEnable(unk_148, MenuStatusInfo::getPlayerItemID(unk_148, BattleMenuPlayerControl::getSingleton()->activeItem_));
}

#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SHIFT_PARTY.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"

using menu::MenuStatusInfo;

THUMB void TownMenu_OPERATION_SHIFT_PARTY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    carriageEnable_ = MenuStatusInfo::isCarriageEnable();
    shiftPartyCharaCount_ = 0;
    enableEnter_ = 0;
    navigator_.setupBase();
    selectCharaMaxCount_ = 0;
    npcPosition_ = -1;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < 8; i++) {
        selectChara_[i] = -1;
    }
    for (int i = 0; i < count; i++) {
        if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_BATTLE_NPC) && !MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_NORMAL_NPC)) {
            selectChara_[selectCharaMaxCount_] = i;
            selectCharaMaxCount_++;
        } else {
            npcPosition_ = i;
        }
    }
    for (int i = 0; i < 4; i++) {
        selectCharaAllocation_[i] = -1;
    }
}

THUMB void TownMenu_OPERATION_SHIFT_PARTY::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    int count = selectCharaMaxCount_ - shiftPartyCharaCount_;
    if (count == 0 && carriageEnable_ == 0) {
        count = 1;
    }
    if (shiftPartyCharaCount_ != 0 && carriageEnable_ == 1) {
        count++;
    }
    unkfunc_02171354(&menuItem_, menuItem_.active_, count);
}

THUMB void TownMenu_OPERATION_SHIFT_PARTY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        return;
    }
    char list[8] = {-1};
    for (int i = 0; i < 8; i++) {
        list[i] = -1;
    }
    int found = 0;
    int count = 0;
    for (char i = 0; i < selectCharaMaxCount_; i++) {
        for (char j = 0; j < shiftPartyCharaCount_; j++) {
            if (selectChara_[i] == selectCharaAllocation_[j]) {
                found = 1;
            }
        }
        if (found == 0) {
            list[count] = selectChara_[i];
            count++;
        }
        found = 0;
    }
    unkfunc_021737e4(selectCharaAllocation_, list, menuItem_.active_, count);
    menuItem_.drawActive();
}

THUMB void TownMenu_OPERATION_SHIFT_PARTY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            menuItem_.active_ = 0;
            enableEnter_ = 0;
            shiftPartyCharaCount_ = 0;
            for (int i = 0; i < 4; i++) {
                selectCharaAllocation_[i] = -1;
            }
        }
        return;
    }
    if (enableEnter_ == 1) {
        chengeChara();
        return;
    }
    int count = selectCharaMaxCount_ - shiftPartyCharaCount_;
    if (shiftPartyCharaCount_ != 0 && carriageEnable_ == 1) {
        count++;
    }
    navigator_.setup(5, 2, count);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 2) {
            unkfunc_02176b1c();
        }
        if (result == 3) {
            if (shiftPartyCharaCount_ == 0) {
                close();
                gTownMenu_OPERATION_ROOT.open();
            } else {
                shiftPartyCharaCount_--;
                selectCharaAllocation_[shiftPartyCharaCount_] = -1;
            }
        }
        redraw_ = 1;
    }
}

THUMB void TownMenu_OPERATION_SHIFT_PARTY::unkfunc_02176b1c()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    int found = 0;
    char list[8] = {0};
    for (int i = 0; i < 8; i++) {
        list[i] = 0;
    }
    int active = menuItem_.active_;
    if (active == selectCharaMaxCount_ - shiftPartyCharaCount_ && shiftPartyCharaCount_ != 0) {
        enableEnter_ = 1;
        return;
    }
    if (shiftPartyCharaCount_ == 4 || selectCharaMaxCount_ - shiftPartyCharaCount_ == 0) {
        return;
    }
    int count = 0;
    for (char i = 0; i < selectCharaMaxCount_; i++) {
        for (int j = 0; j < shiftPartyCharaCount_; j++) {
            if (selectCharaAllocation_[j] == selectChara_[i]) {
                found = 1;
            }
        }
        if (found == 0) {
            list[count] = selectChara_[i];
            count++;
        }
        found = 0;
    }
    if (active == selectCharaMaxCount_ - shiftPartyCharaCount_ && shiftPartyCharaCount_ != 0) {
        enableEnter_ = 1;
        return;
    }
    selectCharaAllocation_[shiftPartyCharaCount_] = list[active];
    shiftPartyCharaCount_++;
    if (shiftPartyCharaCount_ == 4 || selectCharaMaxCount_ - shiftPartyCharaCount_ == 0) {
        if (carriageEnable_ == 1) {
            menuItem_.active_ = selectCharaMaxCount_ - shiftPartyCharaCount_;
        } else {
            menuItem_.active_ = 0;
        }
        return;
    }
    if (active == selectCharaMaxCount_ - shiftPartyCharaCount_) {
        menuItem_.active_ = active - 1;
    }
}

THUMB void TownMenu_OPERATION_SHIFT_PARTY::chengeChara()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    bool allDeath = true;
    for (int i = 0; i < shiftPartyCharaCount_; i++) {
        if (MenuStatusInfo::isPlayerCondition(selectCharaAllocation_[i], MenuStatusInfo::CONDITION_ALIVE) == true) {
            allDeath = false;
        }
    }
    if (allDeath == true) {
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc42a5);
        return;
    }
    if (npcPosition_ != -1) {
        for (int i = 0; i < 4; i++) {
            if (selectCharaAllocation_[i] == -1) {
                selectCharaAllocation_[i] = npcPosition_;
                break;
            }
        }
    }
    MenuStatusInfo::reorder(selectCharaAllocation_[0], selectCharaAllocation_[1], selectCharaAllocation_[2], selectCharaAllocation_[3]);
    close();
    gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
    if (data_02101c88.isCurrentPart(6) == true) {
        SoundManager::fieldPlay(fld::FieldSystem::getFloorBgmIndex());
    }
    status::PartyStatusUtility::resetForceReorderMember();
}

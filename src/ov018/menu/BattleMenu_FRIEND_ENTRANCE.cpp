#include "ov018/menu/BattleMenu.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void btl::BattleEffectManager::setSpecialTarget(int index, int ctrlId, int anim) { unit_[index].setSpecialTarget(ctrlId, anim); }
inline unsigned char dq5::level::MonsterData::getParty() { return party; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }

THUMB void BattleMenu_FRIEND_ENTRANCE::menuSetup()
{
    monster_ = -1;
    monsterCtrl_ = -1;
    friend_ = status::g_Monster.getPartyMonster();
    friendIndex_ = dq5::level::MonsterData::getRecord(friend_)->getParty();
    friendCtrl_ = status::PlayerDataAll::getNextAddFriendMonster(friendIndex_);
    bashaFlag_ = false;
    partyFlag_ = false;
    oldLeaveFlag_ = true;
    mode_ = MODE_START;
    btl::BattleMonsterDraw2::getSingleton().cleanup();
    btl::BattleMonsterDraw2::getSingleton().setup(0, friend_, true);
    dss::Fix32Vector3 pos(0, 0, 0);
    btl::BattleMonsterDraw2::getSingleton().getMonster(0).setPosition(pos);
    btl::BattleMonsterDraw2::getSingleton().getMonster(0).startAnimation(0x21);
}

THUMB void BattleMenu_FRIEND_ENTRANCE::menuExecute()
{
}

THUMB void BattleMenu_FRIEND_ENTRANCE::menuDraw()
{
}

THUMB void BattleMenu_FRIEND_ENTRANCE::menuUpdate()
{
    if (!messageUpdate()) {
        commandUpdate();
    }
}

THUMB bool BattleMenu_FRIEND_ENTRANCE::messageUpdate()
{
    switch (mode_) {
    case MODE_START:
        if (!gTownMenu_MESSAGE.isOpen()) {
            TextAPI::setMACRO0(0xd, 0x60000000, friend_);
            gTownMenu_MESSAGE.openMessageForBATTLE();
            gTownMenu_MESSAGE.addMessage(0xc3d21);
            gTownMenu_MESSAGE.addMessage(0xc3d22);
            gTownMenu_MESSAGE.setMessageLastCursor(false);
            gTownMenu_MESSAGE.setYesNo();
            int ctrl = btl::BattleEffectManager::getSingleton()->setupEffect(0xea);
            if (ctrl >= 0) {
                btl::BattleEffectManager::getSingleton()->setSpecialTarget(ctrl, 0, 1);
            }
            btl::BattleMonsterDraw2::getSingleton().getMonster(0).startAnimation(0x20);
        } else {
            int stat = gTownMenu_MESSAGE.stat_;
            if (stat == 1) {
                gTownMenu_MESSAGE.close();
                return false;
            }
            if (stat == 2) {
                mode_ = MODE_GOOD_BYE;
                gTownMenu_MESSAGE.close();
            }
        }
        break;
    case MODE_GOOD_BYE:
        TextAPI::setMACRO0(0xd, 0x60000000, friend_);
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3cb6);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        mode_ = MODE_EXEC;
        btl::BattleMonsterDraw2::getSingleton().getMonster(0).startAnimation(0x1f);
        break;
    case MODE_IN_PARTY:
        TextAPI::setMACRO0(0xd, 0x60000000, friend_);
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3cb9);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        mode_ = MODE_LEAVE_NEW;
        if (!partyFlag_) {
            TextAPI::setMACRO0(0xd, 0x60000000, friend_);
            gTownMenu_MESSAGE.addMessage(0xc3cbc);
            if (!bashaFlag_) {
                gTownMenu_MESSAGE.addMessage(0xc3cbf);
                gTownMenu_MESSAGE.addMessage(0xc3cc0);
                mode_ = MODE_SELECT;
            }
        }
        break;
    case MODE_SELECT:
    case MODE_LEAVE_NEW:
    case MODE_EXEC:
        if (gTownMenu_MESSAGE.isOpen()) {
            if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
                gTownMenu_MESSAGE.close();
            }
        } else {
            return false;
        }
        break;
    case MODE_IS_CANCEL:
        if (!gTownMenu_MESSAGE.isOpen()) {
            TextAPI::setMACRO0(0x81, 0x50000000, friendCtrl_);
            gTownMenu_MESSAGE.openMessageForBATTLE();
            gTownMenu_MESSAGE.addMessage(0xc3cc3);
            gTownMenu_MESSAGE.setMessageLastCursor(false);
            gTownMenu_MESSAGE.setYesNo();
        } else {
            int stat = gTownMenu_MESSAGE.stat_;
            if (stat == 1) {
                mode_ = MODE_GOOD_BYE;
                gTownMenu_MESSAGE.close();
            }
            if (stat == 2) {
                mode_ = MODE_SELECT;
                gTownMenu_MESSAGE.close();
            }
        }
        break;
    case MODE_IS_LAST:
        if (!gTownMenu_MESSAGE.isOpen()) {
            TextAPI::setMACRO0(0x12, 0x50000000, monster_);
            gTownMenu_MESSAGE.openMessageForBATTLE();
            gTownMenu_MESSAGE.addMessage(0xc3cc6);
            gTownMenu_MESSAGE.setMessageLastCursor(false);
            gTownMenu_MESSAGE.setYesNo();
        } else {
            int stat = gTownMenu_MESSAGE.stat_;
            if (stat == 1) {
                gTownMenu_MESSAGE.close();
                return false;
            }
            if (stat == 2) {
                mode_ = MODE_SELECT;
                gTownMenu_MESSAGE.close();
            }
        }
        break;
    case MODE_IS_LEAVE:
        TextAPI::setMACRO0(0x12, 0x50000000, monster_);
        TextAPI::setMACRO0(0x81, 0x50000000, friendCtrl_);
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3ccc);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        mode_ = MODE_LEAVE_NEW;
        break;
    case MODE_LEAVE_OLD:
        TextAPI::setMACRO0(0x81, 0x50000000, friendCtrl_);
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3cc9);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        mode_ = MODE_LEAVE_NEW;
        break;
    }
    return true;
}

THUMB void BattleMenu_FRIEND_ENTRANCE::commandUpdate()
{
    switch (mode_) {
    case MODE_START:
        status::g_Party.setBattleModeAndCarriage();
        if (status::g_Party.getCarriageOutCount() + status::g_Party.getCarriageCount() < 8) {
            if (status::g_Party.getCarriageOutCount() == 4) {
                bashaFlag_ = true;
            } else {
                partyFlag_ = true;
            }
        }
        mode_ = MODE_IN_PARTY;
        break;
    case MODE_SELECT:
        unkfunc_02171178();
        break;
    case MODE_IS_LAST:
        if (monster_ == friendCtrl_) {
            mode_ = MODE_LEAVE_OLD;
            oldLeaveFlag_ = false;
        } else {
            mode_ = MODE_IS_LEAVE;
            oldLeaveFlag_ = true;
        }
        break;
    case MODE_LEAVE_NEW:
        mode_ = MODE_EXEC;
        if (partyFlag_ || bashaFlag_) {
            status::g_Party.add(status::PlayerDataAll::addFriendMonster(friendIndex_), true);
        } else {
            int ctrl = status::PlayerDataAll::addFriendMonster(friendIndex_);
            if (oldLeaveFlag_) {
                int maxItem = MenuStatusInfo::getPlayerItemCount(monsterArray_);
                int equipCount = 0;
                for (int i = 0; i < maxItem; i++) {
                    if (MenuStatusInfo::isPlayerEquipItemIndex(monsterArray_, i)) {
                        equipCount++;
                    }
                }
                for (int i = equipCount; i < maxItem; i++) {
                    MenuStatusInfo::changeItemPlayertoSack(monsterArray_, equipCount);
                }
                status::g_Party.del(status::g_Party.getSortIndex(monster_));
                status::g_Party.add(ctrl, true);
            }
            status::PlayerDataAll::setMonsterOldManFlag(monster_, true);
        }
        break;
    case MODE_EXEC:
        close();
        stat_ = MENUBASE_STAT_OK;
        btl::BattleMonsterDraw2::getSingleton().cleanup();
        break;
    }
}

THUMB void BattleMenu_FRIEND_ENTRANCE::unkfunc_02171178()
{
    if (!gUnkBattleMenuFriendSelect.isOpen()) {
        gUnkBattleMenuFriendSelect.open();
    }
    if (gUnkBattleMenuFriendSelect.isDecide_) {
        gUnkBattleMenuFriendSelect.close();
        monster_ = gUnkBattleMenuFriendSelect.select_;
        if (monster_ == 0) {
            monster_ = status::PlayerDataAll::playerData_[friendCtrl_].index_;
        } else {
            monsterArray_ = getFriendPartyIndex(monster_);
            monster_ = getFriendPlayerIndex(monster_);
            monsterCtrl_ = status::PlayerDataAll::getFriendMonsterCtrl(monster_);
        }
        mode_ = MODE_IS_LAST;
    }
    if (gUnkBattleMenuFriendSelect.isCancel_) {
        gUnkBattleMenuFriendSelect.close();
        mode_ = MODE_IS_CANCEL;
    }
}

THUMB int BattleMenu_FRIEND_ENTRANCE::getFriendPlayerIndex(int num)
{
    status::g_Party.setBattleModeAndCarriage();
    int count = status::g_Party.getCarriageOutCount() + status::g_Party.getCarriageCount();
    int friendCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().playerType_ == status::HaveStatus::TYPE_FRIENDMONSTER) {
            friendCount++;
            if (friendCount == num) {
                return status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex();
            }
        }
    }
    return monster_;
}

THUMB int BattleMenu_FRIEND_ENTRANCE::getFriendPartyIndex(int num)
{
    status::g_Party.setBattleModeAndCarriage();
    int count = status::g_Party.getCarriageOutCount() + status::g_Party.getCarriageCount();
    int friendCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().playerType_ == status::HaveStatus::TYPE_FRIENDMONSTER) {
            friendCount++;
            if (friendCount == num) {
                return i;
            }
        }
    }
    return monster_;
}

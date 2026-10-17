#pragma ipa file
#include "ov000/btl/BattleRoundStart.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/text/TextAPI.hpp"

inline ExecTaskManager2::ExecTaskManager2() { flag_.clear(); }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline int status::MonsterStatus::getSortIndexInGroup() { return sortIndex_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

THUMB void btl::BattleTaskCallFriend::setup()
{
    int monsterGroup = status::UseActionFlag::getCallFriendMonsterGroup();
    int monsterIndex = status::UseActionFlag::getCallFriendMonsterIndex();
    if (!BattleMonsterDraw2::getSingleton().isCallFriend(monsterIndex)) {
        status::UseActionFlag::setCallFriend(false, 0, 0);
        return;
    }
    bool ret = false;
    if (status::g_Monster.getMonsterCountInGroupAlive(0) == 0) {
        monsterGroup = 0;
        ret = true;
    }
    else if (status::g_Monster.getMonsterCountInGroupAlive(1) == 0) {
        monsterGroup = 1;
        ret = true;
    }
    else if (status::g_Monster.getMonsterCountInGroupAlive(2) == 0) {
        monsterGroup = 2;
        ret = true;
    }
    else if (status::g_Monster.getMonsterCountInGroupAlive(3) == 0) {
        monsterGroup = 3;
        ret = true;
    }
    if (!ret) {
        return;
    }
    status::UseActionFlag::setCallFriend(false, 0, 0);
    int ctrlId = status::g_Monster.add(monsterGroup, monsterIndex, false);
    unsigned short hpMax = status::g_Monster.getMonsterStatus(ctrlId).getHaveStatusInfo().getHpMax();
    unsigned short rate = UnkDssRand::rand(25) + 76;
    hpMax = hpMax * rate / 100;
    if (hpMax == 0) {
        hpMax = 1;
    }
    status::g_Monster.getMonsterStatus(ctrlId).getHaveStatusInfo().setHp(hpMax);
    int ctrlDraw = status::g_Monster.getMonsterStatus(ctrlId).getHaveStatusInfo().getDrawCtrlId();
    BattleMonsterDraw2::getSingleton().getMonster(ctrlDraw).startAnimation(0x20);
    if (status::g_Monster.getMonsterCountDeadOrAlive(monsterIndex) == 1 && !btl::Encount::getSingleton()->getMonsterCountName(monsterIndex)) {
        TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex);
    }
    else {
        int sortIndex = status::g_Monster.getMonsterStatus(ctrlId).getSortIndexInGroup();
        TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex, sortIndex);
    }
    BattleMessage::setMessage(0xC3A14, 0, 0, 0);
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
}

THUMB void btl::BattleTaskCallFriend::cleanup()
{
}

THUMB bool btl::BattleTaskCallFriend::isEnd()
{
    return BattleAutoFeed::isEndResultMessage();
}

THUMB void btl::BattleExecRoundStart::initialize_user()
{
    if (status::UseActionFlag::isCallFriend()) {
        resister(0, &battleTaskCallFriend_);
    }
}

THUMB void btl::BattleExecRoundStart::terminate_user()
{
}

btl::BattleExecRoundStart btl::g_BattleExecRoundStart;

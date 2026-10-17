#pragma ipa file
#include "ov001/town/stage/effect/TownStageWireTrap.hpp"
#include "ov001/leveldata/BoobyTrap.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"

inline int twn::TownPlayerManager::getPartyDrawCount()
{
    return partyDraw_.countReal_;
}

#pragma thumb on

inline dss::Fix32::Fix32(fx32 v)
{
    value = v;
}

inline void dss::Fix32::operator+=(const Fix32& o)
{
    value += o.value;
}

inline void dss::Fix32::operator-=(const Fix32& o)
{
    value -= o.value;
}

inline dss::Fix32 dss::Fix32::operator*(int v) const
{
    return Fix32(value * v);
}

inline bool dss::Fix32::operator<(const Fix32& o) const
{
    return value < o.value;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::BoobyTrap* dq5::level::BoobyTrap::getRecord(int index)
{
    return (BoobyTrap*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::BoobyTrap::getArraySize()
{
    return binary_.getRecordCount();
}

inline int dq5::level::BoobyTrap::getIndex()
{
    return index;
}

inline int dq5::level::BoobyTrap::getPlaceRight()
{
    return placeRight;
}

inline int dq5::level::BoobyTrap::getPlaceLeft()
{
    return placeLeft;
}

inline int FldCollision::getFloorMapUid()
{
    return floorMapUid_;
}

inline int twn::TownStageManager::getFloorMapUid()
{
    return coll_.getFloorMapUid();
}

inline void twn::TownPartyDraw::setMemberColor(int index, unsigned short color)
{
    partyCharacter_[index].setColor(color);
}

inline void twn::TownPlayerManager::setMemberColor(int index, unsigned short color)
{
    partyDraw_.setMemberColor(index, color);
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

dss::Fix32 twn::TownStageWireTrap::distance_(0.3f);
dss::Fix32 twn::TownStageWireTrap::distanceSq_ = dss::Fix32(0.6f) * dss::Fix32(0.6f);
int twn::TownStageWireTrap::distanceSq2_ = dss::Fix32(0.6f).value * dss::Fix32(0.6f).value / 4096 + 0xa00;

twn::TownStageWireTrap::TownStageWireTrap()
{
    enable_ = false;
}

twn::TownStageWireTrap::~TownStageWireTrap()
{
}

void twn::TownStageWireTrap::cleanup()
{
    enable_ = false;
}

bool twn::TownStageWireTrap::isTrap()
{
    if (phase_ == 2) {
        if (prevIndex != TownStageManager::getSingleton()->getFloorMapUid()) {
            phase_ = 0;
        }
    }
    if (phase_ == 0) {
        int index = checkTrap();
        if (index >= 0) {
            phase_ = 1;
            TownPlayerManager::getSingleton().setRemote(true);
            setTrapSide(index);
            prevIndex = TownStageManager::getSingleton()->getFloorMapUid();
            if (damage_) {
                calcPlayerDamage();
            }
            counter_ = 0;
            return true;
        }
    }
    return false;
}

void twn::TownStageWireTrap::execute()
{
    if (!enable_) {
        return;
    }
    switch (phase_) {
    case 0:
        break;
    case 1:
        counter_++;
        if (damage_) {
            if (damage_ == counter_) {
                for (int i = 0; i < TownPlayerManager::getSingleton().getPartyDrawCount(); i++) {
                    TownPlayerManager::getSingleton().setMemberColor(i, TownPlayerManager::getSingleton().getDamageColor(2));
                }
            }
            if (damage_ + 4 == counter_) {
                for (int i = 0; i < TownPlayerManager::getSingleton().getPartyDrawCount(); i++) {
                    TownPlayerManager::getSingleton().setMemberColor(i, TownPlayerManager::getSingleton().getDamageColor(3));
                }
            }
        }
        if (TownRiseupManager::getSingleton().isFinish(lastFire_)) {
            for (int i = 0; i < TownPlayerManager::getSingleton().getPartyDrawCount(); i++) {
                TownPlayerManager::getSingleton().setMemberColor(i, TownPlayerManager::getSingleton().getDamageColor(3));
            }
            if (checkPlayerDemolition()) {
                phase_ = 3;
            } else {
                phase_ = 2;
                TownPlayerManager::getSingleton().setRemote(false);
            }
        }
        break;
    case 2:
        break;
    case 3:
        if (status::g_Party.getCount() == 1) {
            TownWindowSystem::getSingleton().openSystemMessage(0xc3c7a, 1);
        } else {
            TownWindowSystem::getSingleton().openSystemMessage(0xc3c7d, 1);
        }
        phase_ = 4;
        break;
    case 4:
        if (!TownWindowSystem::getSingleton().isMessageOpen()) {
            g_AreaFlag.set(0x140);
            status::g_StageInfo.returnChurch();
            status::g_Party.setGold(status::g_Party.getGold() / 2);
            phase_ = 2;
        }
        break;
    }
}

int twn::TownStageWireTrap::checkTrap()
{
    if (TownStageManager::getSingleton()->getFloorMapUid() == 0) {
        return -1;
    }
    for (int i = 0; i < dq5::level::BoobyTrap::getArraySize(); i++) {
        if (dq5::level::BoobyTrap::getRecord(i)->getIndex() == TownStageManager::getSingleton()->getFloorMapUid()) {
            return i;
        }
    }
    return -1;
}

void twn::TownStageWireTrap::setTrapSide(int index)
{
    dss::Fix32Vector3 pos;
    if (dq5::level::BoobyTrap::getRecord(index)->getPlaceLeft() != 0) {
        pos = TownStageManager::getSingleton()->getMapUidPos(dq5::level::BoobyTrap::getRecord(index)->getPlaceLeft());
        lastFire_ = setDrawFire(pos, 1);
    }
    if (dq5::level::BoobyTrap::getRecord(index)->getPlaceRight() != 0) {
        pos = TownStageManager::getSingleton()->getMapUidPos(dq5::level::BoobyTrap::getRecord(index)->getPlaceRight());
        lastFire_ = setDrawFire(pos, 2);
    }
}

int twn::TownStageWireTrap::setDrawFire(dss::Fix32Vector3& pos, int side)
{
    int time = 0;
    bool hit = false;
    dss::Fix32 height(0.32f);
    pos.vy = height;
    dss::Fix32Vector3 start(pos);
    if (side == 1) {
        pos.vx += distance_;
    } else {
        pos.vx -= distance_;
    }
    for (int i = 0; i < MAX_FIRE_DRAW; i++) {
        if (side == 1) {
            pos.vx += distance_;
        } else {
            pos.vx -= distance_;
        }
        time += 2;
        damage_ = time;
        dss::Fix32Vector3 diff = pos - TownPlayerManager::getSingleton().getPosition();
        dss::Fix32 len = diff.lengthsq();
        if (len < distanceSq2_) {
            if (hit) {
                break;
            }
            hit = true;
        }
        if (TownCharacterManager::getSingleton()->checkCollision(pos, distanceSq_)) {
            if (!hit) {
                damage_ = 0;
            }
            break;
        }
    }
    if (side == 1) {
        start.vx += distance_ * 2;
    } else {
        start.vx -= distance_ * 2;
    }
    int riseIndex;
    for (int i = 0, frame = 0; i < MAX_FIRE_DRAW; i++, frame += 2) {
        riseIndex = TownRiseupManager::getSingleton().setupSpriteMove(FIRE_EFFECT_INDEX, start, pos, 0x10, frame);
    }
    return riseIndex;
}

void twn::TownStageWireTrap::calcPlayerDamage()
{
    status::g_Party.setPlayerMode();
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        int hp = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp() - 25;
        if (hp <= 0) {
            hp = 0;
        }
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setHp(hp);
    }
}

bool twn::TownStageWireTrap::checkPlayerDemolition()
{
    status::g_Party.setPlayerMode();
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp() == 0) {
            TownPlayerManager::getSingleton().resetParty();
            break;
        }
    }
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp() != 0) {
            return false;
        }
    }
    return true;
}

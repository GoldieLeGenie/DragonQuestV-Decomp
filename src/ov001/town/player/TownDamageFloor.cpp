#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/sound/SoundManager.hpp"

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline twn::TownPartyAction& twn::TownPlayerManager::getPartyAction()
{
    return party_;
}

inline void twn::TownPartyDraw::setMemberColor(int index, unsigned short color)
{
    partyCharacter_[index].setColor(color);
}

inline void twn::TownPlayerManager::setMemberColor(int index, unsigned short color)
{
    partyDraw_.setMemberColor(index, color);
}

inline int twn::TownRiseupStorage::getSpriteNum()
{
    return spriteCounter_;
}

inline int twn::TownRiseupManager::getSpriteNum()
{
    return riseupStorage_.getSpriteNum();
}

THUMB TownDamageFloor& TownDamageFloor::getSingleton()
{
    static TownDamageFloor townDamageFloor;
    return townDamageFloor;
}

THUMB void TownDamageFloor::setup()
{
    topStride_ = 16;
    partyStride_ = 8;
    check_ = false;
    CommonWalkDamage::setup();
}

THUMB bool TownDamageFloor::checkBarrier()
{
    return twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(3) != -1;
}

THUMB bool TownDamageFloor::checkPoison()
{
    return twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(2) != -1;
}

THUMB bool TownDamageFloor::checkYogan()
{
    return twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(15) != -1;
}

THUMB bool TownDamageFloor::checkPuddle()
{
    return twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(9) != -1;
}

THUMB void TownDamageFloor::setPuddleEffect(int index)
{
    dss::Fix32Vector3 pos = twn::TownPlayerManager::getSingleton().getPartyAction().getMemberPos(index);
    short idx = twn::TownPlayerManager::getSingleton().getPartyAction().getMemberDir(index);
    dss::Fix32Vector3 vec;
    twn::TownActionCalculate::getDirByIdx(idx, vec);
    dss::Fix32 fix((fx32)0x4cd);
    pos += vec * fix;
    pos.vy += 0x19a;
    if (twn::TownRiseupManager::getSingleton().getSpriteNum() < 6) {
        twn::TownRiseupManager::getSingleton().setupSprite2(0x38e, pos, 2, 0);
    }
    if (watCounter_ == -1) {
        watCounter_ = 0;
        nextWatSe_ = 0;
        SoundManager::playSe2(0x72, 0);
    } else {
        nextWatSe_ = 1;
    }
}

THUMB void TownDamageFloor::setPartyMemberColor(int index, int type)
{
    unsigned short rgb = twn::TownPlayerManager::getSingleton().getDamageColor(type);
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCount();
    int temp = -1;
    for (int i = 0; i < count; i++) {
        if (index == status::g_Party.getPlayerIndex(i)) {
            temp = i;
            break;
        }
    }
    if (status::g_StageAttribute.isCarriageEnter() && status::g_Party.isCarriage()) {
        if (temp > 0) {
            temp += 2;
        }
    }
    twn::TownPlayerManager::getSingleton().setMemberColor(temp, rgb);
    if (isPlaySe() == true) {
        nextSe_ = 0;
        if (type == 0) {
            SoundManager::playSe(0x13c, 0);
        } else if (type == 1) {
            SoundManager::playSe(0x13b, 0);
        } else if (type == 2) {
            SoundManager::playSe(0x13c, 0);
        } else if (type == 10) {
            SoundManager::playSe2(0x72, 0);
        }
        seCounter_ = 0;
    } else {
        setNextSe(type);
    }
    status::g_Party.setBattleMode();
}

THUMB void TownDamageFloor::checkDamageFloor(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos)
{
    check_ = true;
    nowPos_ = nowPos;
    nextPos_ = nextPos;
}

THUMB void TownDamageFloor::checkEncount()
{
    if (check_ == true) {
        checkWalk(nowPos_, nextPos_);
    }
    check_ = false;
}

static const dss::Fix32 DAMAGE_DISTANCE(0.5f);

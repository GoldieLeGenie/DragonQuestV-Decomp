#include "ov005/fld/FieldPlayerDoku.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline void fld::FieldPartyDraw::setMemberColor(int index, unsigned short color)
{
    partyCharacter_[index].setColor(color);
}

inline void fld::FieldPlayerManager::setMemberColor(int index, unsigned short color)
{
    partyDraw_.setMemberColor(index, color);
}

THUMB fld::FieldPlayerDoku& fld::FieldPlayerDoku::getSingleton()
{
    static FieldPlayerDoku FieldPlayerDoku;
    return FieldPlayerDoku;
}

THUMB void fld::FieldPlayerDoku::setup()
{
    CommonWalkDamage::setup();
    topStride_ = 0x10;
    partyStride_ = 0xd;
}

THUMB bool fld::FieldPlayerDoku::checkBarrier()
{
    return false;
}

THUMB bool fld::FieldPlayerDoku::checkPoison()
{
    return blockAttr_ == 10;
}

THUMB void fld::FieldPlayerDoku::setPartyMemberColor(int index, int type)
{
    unsigned short rgb = FieldPlayerManager::getSingleton().getDamageColor(type);
    status::g_Party.setDisplayMode();
    int count = status::g_Party.getCount();
    int temp = 0;
    for (int i = 0; i < count; i++) {
        if (index == status::g_Party.getPlayerIndex(i)) {
            temp = i;
            break;
        }
    }
    if (status::g_Party.isCarriage() == true && temp > 0) {
        temp += 2;
    }
    FieldPlayerManager::getSingleton().setMemberColor(temp, rgb);
    if (isPlaySe() == true) {
        nextSe_ = 0;
        if (type == 1) {
            SoundManager::playSe(0x13b, 0);
        }
        seCounter_ = 0;
    } else {
        setNextSe(type);
    }
    status::g_Party.isBattleMode();
}

THUMB void fld::FieldPlayerDoku::checkDokuDamage(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos)
{
    checkWalk(nowPos, nextPos);
}

THUMB void fld::FieldPlayerDoku::setBlockAttr(int blockAttr)
{
    blockAttr_ = blockAttr;
}

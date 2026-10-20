#pragma ipa file
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/btl/Encount.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/status/CharacterStatus.hpp"

#define FX32_CONST_INT(x) ((fx32)(((x) > 0) ? ((x) * 4096 + 0.5f) : ((x) * 4096 - 0.5f)))

inline PaletteAnimation::~PaletteAnimation() {}
inline bool btl::BattleMonster::isEnable() { return flag_.check(FLAG_ENABLE); }
inline bool btl::BattleMonster::isAirMonster() { return flag_.check(FLAG_AIR_MONSTER); }
inline void btl::BattleMonster::setAirMonster(bool flag)
{
    if (flag) {
        flag_.set(FLAG_AIR_MONSTER);
    } else {
        flag_.remove(FLAG_AIR_MONSTER);
    }
}
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::MonsterData::getPosition() { return byte_1 & 1; }


int btl::BattleMonsterDraw2::airMonsterHeight_ = 0x40;

THUMB btl::BattleMonsterDraw2::BattleMonsterDraw2() : enable_(1)
{
}

THUMB btl::BattleMonsterDraw2::~BattleMonsterDraw2()
{
}

THUMB btl::BattleMonsterDraw2& btl::BattleMonsterDraw2::getSingleton()
{
    static BattleMonsterDraw2 m_singleton;
    return m_singleton;
}

static dss::Fix32 defaultWidth(1.5f);

THUMB void btl::BattleMonsterDraw2::setup()
{
    int monsterIndex[4] = {0};
    int monsterCount[4] = {0};
    for (int i = 0; i < 4; i++) {
        monsterIndex[i] = Encount::getSingleton()->monsterIndex_[i];
        monsterCount[i] = Encount::getSingleton()->monsterCount_[i];
    }
    battleArray_.setup(monsterIndex, monsterCount);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < monsterCount[i]; j++) {
            int index = status::g_Monster.add(i, monsterIndex[i], true);
            setupBattleArray(status::g_Monster.getMonsterStatus(index).getHaveStatusInfo().getDrawCtrlId(), true);
        }
    }
}

THUMB void btl::BattleMonsterDraw2::cleanup()
{
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monsters_[i].isEnable()) {
            monsters_[i].cleanup();
            battleArray_.del(i);
        }
    }
}

THUMB void btl::BattleMonsterDraw2::setupBattleArray(int ctrl, int air)
{
    if (monsters_[ctrl].isEnable()) {
        dss::Fix32Vector3 position(0, 0, 0);
        if (monsters_[ctrl].isAirMonster() && air) {
            int pos = battleArray_.getMonsterPositionAir(ctrl);
            position.vx = FX32_CONST_INT(pos);
            position.vy = FX32_CONST_INT(airMonsterHeight_);
        } else {
            int pos = battleArray_.getMonsterPositionGround(ctrl);
            position.vx = FX32_CONST_INT(pos);
        }
        position *= DSSAObject::getDefaultScale();
        monsters_[ctrl].setPosition(position);
    }
}

THUMB int btl::BattleMonsterDraw2::setup(int monsterGroup, int monsterIndex, bool flag)
{
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (!monsters_[i].isEnable()) {
            monsters_[i].setup(monsterGroup, monsterIndex);
            if (dq5::level::MonsterData::getRecord(monsterIndex)->getPosition() == 0) {
                monsters_[i].setAirMonster(false);
            } else {
                monsters_[i].setAirMonster(true);
            }
            if (!flag) {
                addBattleArray(i, monsterGroup, monsterIndex);
            }
            return i;
        }
    }
    return -1;
}

THUMB void btl::BattleMonsterDraw2::cleanup(int ctrl)
{
    if (monsters_[ctrl].isEnable()) {
        monsters_[ctrl].cleanup();
        delBattleArray(ctrl);
    }
}

THUMB void btl::BattleMonsterDraw2::addBattleArray(int ctrl, int monsterGroup, int monsterIndex)
{
    if (monsters_[ctrl].isEnable()) {
        battleArray_.add(ctrl, monsterGroup, monsterIndex);
        dss::Fix32Vector3 position(0, 0, 0);
        if (monsters_[ctrl].isAirMonster()) {
            int pos = battleArray_.getMonsterPositionAir(ctrl);
            position.vx = FX32_CONST_INT(pos);
            position.vy = FX32_CONST_INT(airMonsterHeight_);
        } else {
            int pos = battleArray_.getMonsterPositionGround(ctrl);
            position.vx = FX32_CONST_INT(pos);
        }
        position *= DSSAObject::getDefaultScale();
        monsters_[ctrl].setPosition(position);
    }
}

THUMB void btl::BattleMonsterDraw2::delBattleArray(int ctrl)
{
    if (monsters_[ctrl].isEnable()) {
        battleArray_.del(ctrl);
    }
}

THUMB void btl::BattleMonsterDraw2::draw()
{
    if (enable_) {
        for (int i = 0; i < MONSTER_MAX; i++) {
            if (monsters_[i].isEnable()) {
                monsters_[i].draw();
            }
        }
    }
}

THUMB bool btl::BattleMonsterDraw2::isCallFriend(int monsterIndex)
{
    return battleArray_.isAdd(monsterIndex);
}

THUMB bool btl::BattleMonsterDraw2::isAppearKingSlime2()
{
    bool ret = false;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monsters_[i].isAppearKingSlime2()) {
            ret = true;
        }
    }
    return ret;
}

THUMB void btl::BattleMonsterDraw2::startAnimationWithLoop(int ctrl, int animIndex, int flag)
{
    monsters_[ctrl].startAnimationWithLoop(animIndex, flag);
}

THUMB void btl::BattleMonsterDraw2::changeArrayCtrl(int oldCtrl, int newCtrl)
{
    battleArray_.changeCtrlId(oldCtrl, newCtrl);
}

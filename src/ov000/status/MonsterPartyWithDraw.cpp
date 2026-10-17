#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"

inline unsigned char dq5::level::MonsterData::getRatio()
{
    return ratio;
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline void status::HaveStatusInfo::setNoDamageEnable(int flag) { noDamage_ = flag; }
inline char dq5::level::MonsterData::getItemRatio() { return byte_11 & 0xF; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getDrawCtrlId() { return haveStatusInfo_.getDrawCtrlId(); }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

inline status::MonsterPartyWithDraw::MonsterPartyWithDraw() {}

int status::MonsterParty::sortCount_[4];

status::MonsterPartyWithDraw status::g_Monster;

THUMB int status::MonsterPartyWithDraw::add(int monsterGroup, int monsterIndex, bool flag)
{
    int ctrlId = MonsterParty::add(monsterGroup, monsterIndex, true);
    int ctrlIdDraw = btl::BattleMonsterDraw2::getSingleton().setup(monsterGroup, monsterIndex, flag);
    monster_[ctrlId].getHaveStatusInfo().setDrawCtrlId(ctrlIdDraw);
    if (!flag) {
        if (monsterIndex == 0x6b) {
            dss::Fix32Vector3 position(0, 0, 0);
            btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw).setPosition(position);
        } else {
            btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlIdDraw).startAnimation(0x21);
        }
    }
    return ctrlId;
}

THUMB void status::MonsterPartyWithDraw::del(int ctrl)
{
    int ctrlIdDraw = monster_[ctrl].getDrawCtrlId();
    if (ctrlIdDraw != -1) {
        btl::BattleMonsterDraw2::getSingleton().cleanup(ctrlIdDraw);
    }
    MonsterParty::del(ctrl);
}

THUMB void status::MonsterParty::checkDropItemMonster(int index)
{
    MonsterStatus& monster = getMonsterStatus(index);
    if (monster.getHaveStatusInfo().isDeath() && !monster.getHaveStatusInfo().isEscapeFlag() && !monster.getHaveStatusInfo().isDisappearFlag()) {
        for (int i = 0; i < getCount(); i++) {
            if (&getMonsterStatus(i) == &monster) {
                checkDropItem(i);
            }
        }
    }
}

THUMB void status::MonsterParty::checkDropItem(int ctrl)
{
    int monsterIndex = getMonsterStatus(ctrl).getMonsterIndex();
    if (getMonsterStatus(ctrl).getHaveStatusInfo().isEscapeFlag() || getMonsterStatus(ctrl).getHaveStatusInfo().isDisappearFlag()) {
        return;
    }
    if (dq5::level::MonsterData::getRecord(monsterIndex)->getRatio()) {
        partyMonster_ = getMonsterStatus(ctrl).getMonsterIndex();
    }
    if (getMonsterStatus(ctrl).getHaveDropItem() && !dropFlag_) {
        dropItem_ = getMonsterStatus(ctrl).getDropItem();
        dropItemMonster_ = monsterIndex;
        if (dq5::level::MonsterData::getRecord(dropItemMonster_)->getItemRatio() == 1) {
            dropFlag_ = 1;
        }
    }
}

THUMB void status::MonsterParty::setDropItem(int itemIndex)
{
    dropItem_ = itemIndex;
}

THUMB int status::MonsterParty::getDropItem()
{
    return dropItem_;
}

THUMB void status::MonsterParty::setDropItemMonster(int monsterIndex)
{
    dropItemMonster_ = monsterIndex;
}

THUMB int status::MonsterParty::getDropItemMonster()
{
    return dropItemMonster_;
}

THUMB int status::MonsterParty::getPartyMonster()
{
    return partyMonster_;
}

THUMB int status::MonsterParty::isAddParty(int count)
{
    return MonsterStatus::isAddParty(partyMonster_, count);
}

THUMB void status::MonsterParty::setNoDamageEnable(int flag)
{
    int count = getCount();
    for (int i = 0; i < count; i++) {
        getMonsterStatus(i).getHaveStatusInfo().setNoDamageEnable(flag);
    }
}

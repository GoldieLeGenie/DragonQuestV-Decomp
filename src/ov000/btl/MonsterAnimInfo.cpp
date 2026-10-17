#include "ov000/btl/MonsterAnimInfo.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "main/leveldata/MonsterData.hpp"

inline unsigned int ExcelBinaryData::getRecordCount() { return record_; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::MonsterData::getAnimIndex() { return animIndex; }
inline dq5::level::MonsterAnim* dq5::level::MonsterAnim::getRecord(int index) { return (MonsterAnim*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::MonsterAnim::getArraySize() { return binary_.getRecordCount(); }
inline unsigned short dq5::level::MonsterAnim::getIndex() { return index; }
inline unsigned short dq5::level::MonsterAnim::getAction() { return action; }
inline unsigned char dq5::level::MonsterAnim::getAnim() { return anim; }

THUMB int btl::getMonsterAnimIndex(unsigned short monsterId, unsigned short actionId, unsigned short animId)
{
    if (monsterId == 0xE8) {
        switch (actionId) {
        case 3:
        case 0x68:
            monsterId = 0xE9;
            break;
        case 0xA0:
            monsterId = 0xEA;
            break;
        }
    }
    int index = dq5::level::MonsterData::getRecord(monsterId)->getAnimIndex();
    for (int i = index; i < dq5::level::MonsterAnim::getArraySize(); i++) {
        if (dq5::level::MonsterAnim::getRecord(i)->getAction() == actionId && dq5::level::MonsterAnim::getRecord(i)->getAnim() == animId) {
            return i;
        }
        if (dq5::level::MonsterAnim::getRecord(i)->getIndex() != monsterId && dq5::level::MonsterAnim::getRecord(i)->getIndex() != 0) {
            return 0;
        }
    }
    return 0;
}

THUMB int btl::getMonsterAnimIndex(unsigned short monsterId, unsigned short actionId)
{
    int index = dq5::level::MonsterData::getRecord(monsterId)->getAnimIndex();
    for (int i = index; i < dq5::level::MonsterAnim::getArraySize(); i++) {
        if (dq5::level::MonsterAnim::getRecord(i)->getAction() == actionId) {
            return i;
        }
        if (dq5::level::MonsterAnim::getRecord(i)->getIndex() != monsterId && dq5::level::MonsterAnim::getRecord(i)->getIndex() != 0) {
            return 0;
        }
    }
    return 0;
}

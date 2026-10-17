#include "main/btl/EncountSpecial.hpp"
#include "main/leveldata/EncountSpecial.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned char dq5::level::EncountSpecial::getMonsterID1()
{
    return monsterID1;
}

inline unsigned char dq5::level::EncountSpecial::getMonsterID2()
{
    return monsterID2;
}

inline unsigned char dq5::level::EncountSpecial::getMonsterID3()
{
    return monsterID3;
}

inline unsigned char dq5::level::EncountSpecial::getMonsterID4()
{
    return monsterID4;
}

inline char dq5::level::EncountSpecial::getGroup_count1()
{
    return byte_1 & 7;
}

inline char dq5::level::EncountSpecial::getGroup_count2()
{
    return (byte_1 & 0x38) >> 3;
}

inline char dq5::level::EncountSpecial::getGroup_count3()
{
    return byte_2 & 7;
}

inline char dq5::level::EncountSpecial::getGroup_count4()
{
    return (byte_2 & 0x38) >> 3;
}

inline dq5::level::EncountSpecial* dq5::level::EncountSpecial::getRecord(int index)
{
    return (EncountSpecial*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB btl::EncountSpecial::EncountSpecial()
{
}

THUMB btl::EncountSpecial::~EncountSpecial()
{
}

THUMB void btl::EncountSpecial::setup(int index)
{
    dq5::level::EncountSpecial* encountSpecial = dq5::level::EncountSpecial::getRecord(index);
    monsterIndex_[0] = encountSpecial->getMonsterID1();
    monsterCount_[0] = getAppearCount(encountSpecial->getGroup_count1());
    monsterCount_[0] = encountSpecial->getGroup_count1();
    monsterIndex_[1] = encountSpecial->getMonsterID2();
    monsterCount_[1] = getAppearCount(encountSpecial->getGroup_count2());
    monsterCount_[1] = encountSpecial->getGroup_count2();
    monsterIndex_[2] = encountSpecial->getMonsterID3();
    monsterCount_[2] = getAppearCount(encountSpecial->getGroup_count3());
    monsterCount_[2] = encountSpecial->getGroup_count3();
    monsterIndex_[3] = encountSpecial->getMonsterID4();
    monsterCount_[3] = getAppearCount(encountSpecial->getGroup_count4());
    monsterCount_[3] = encountSpecial->getGroup_count4();
}

THUMB int btl::getAppearCount(int index)
{
    switch (index) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return UnkDssRand::rand(2) + 1;
    case 5:
        return UnkDssRand::rand(2) + 2;
    case 6:
        return UnkDssRand::rand(3) + 2;
    case 7:
        return UnkDssRand::rand(4) + 4;
    case 8:
        return 8;
    }
    return 0;
}

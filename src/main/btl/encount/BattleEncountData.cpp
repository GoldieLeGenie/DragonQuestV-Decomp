#include "main/btl/EncountData.hpp"
#include "main/leveldata/EncountData.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/DssUtils.hpp"

inline unsigned short dq5::level::EncountData::getBgm()
{
    return bgm;
}

inline unsigned char dq5::level::EncountData::getMonsterA()
{
    return monsterA;
}

inline unsigned char dq5::level::EncountData::getMonsterB()
{
    return monsterB;
}

inline unsigned char dq5::level::EncountData::getMonsterC()
{
    return monsterC;
}

inline unsigned char dq5::level::EncountData::getMonsterD()
{
    return monsterD;
}

inline unsigned char dq5::level::EncountData::getMonsterE()
{
    return monsterE;
}

inline unsigned char dq5::level::EncountData::getMonsterF()
{
    return monsterF;
}

inline unsigned char dq5::level::EncountData::getMonsterG()
{
    return monsterG;
}

inline unsigned char dq5::level::EncountData::getMonsterH()
{
    return monsterH;
}

inline unsigned char dq5::level::EncountData::getMonsterI()
{
    return monsterI;
}

inline unsigned char dq5::level::EncountData::getMonsterJ()
{
    return monsterJ;
}

inline unsigned char dq5::level::EncountData::getParticulParty()
{
    return particulParty;
}

inline unsigned char dq5::level::EncountData::getTileLevel()
{
    return tileLevel;
}

inline char dq5::level::EncountData::getEscape()
{
    return byte_1 & 1;
}

inline char dq5::level::EncountData::getParticulNight()
{
    return (byte_1 & 2) >> 1;
}

inline char dq5::level::EncountData::getInvite()
{
    return (byte_1 & 4) >> 2;
}

inline char dq5::level::EncountData::getEvent()
{
    return (byte_1 & 8) >> 3;
}

inline char dq5::level::EncountData::getFirstattack()
{
    return (byte_1 & 0x30) >> 4;
}

inline char dq5::level::EncountData::getGroup2()
{
    return (byte_1 & 0xc0) >> 6;
}

inline char dq5::level::EncountData::getGroup3()
{
    return byte_2 & 3;
}

inline char dq5::level::EncountData::getGroup4()
{
    return (byte_2 & 0xc) >> 2;
}

inline char dq5::level::EncountData::getStandard()
{
    return (byte_2 & 0x70) >> 4;
}

inline char dq5::level::EncountData::getRatioA()
{
    return byte_3 & 7;
}

inline char dq5::level::EncountData::getRatioB()
{
    return (byte_3 & 0x38) >> 3;
}

inline char dq5::level::EncountData::getRatioC()
{
    return byte_4 & 7;
}

inline char dq5::level::EncountData::getRatioD()
{
    return (byte_4 & 0x38) >> 3;
}

inline char dq5::level::EncountData::getRatioE()
{
    return byte_5 & 7;
}

inline char dq5::level::EncountData::getRatioF()
{
    return (byte_5 & 0x38) >> 3;
}

inline char dq5::level::EncountData::getRatioG()
{
    return byte_6 & 7;
}

inline char dq5::level::EncountData::getRatioH()
{
    return (byte_6 & 0x38) >> 3;
}

inline char dq5::level::EncountData::getRatioI()
{
    return byte_7 & 7;
}

inline char dq5::level::EncountData::getRatioJ()
{
    return (byte_7 & 0x38) >> 3;
}

inline char dq5::level::EncountData::getRatioParticul()
{
    return byte_8 & 7;
}

inline char dq5::level::EncountData::getMaxA()
{
    return (byte_8 & 0x78) >> 3;
}

inline char dq5::level::EncountData::getMaxB()
{
    return byte_9 & 0xf;
}

inline char dq5::level::EncountData::getMaxC()
{
    return (byte_9 & 0xf0) >> 4;
}

inline char dq5::level::EncountData::getMaxD()
{
    return byte_10 & 0xf;
}

inline char dq5::level::EncountData::getMaxE()
{
    return (byte_10 & 0xf0) >> 4;
}

inline char dq5::level::EncountData::getMaxF()
{
    return byte_11 & 0xf;
}

inline char dq5::level::EncountData::getMaxG()
{
    return (byte_11 & 0xf0) >> 4;
}

inline char dq5::level::EncountData::getMaxH()
{
    return byte_12 & 0xf;
}

inline char dq5::level::EncountData::getMaxI()
{
    return (byte_12 & 0xf0) >> 4;
}

inline char dq5::level::EncountData::getMaxJ()
{
    return byte_13 & 0xf;
}

inline dq5::level::EncountData* dq5::level::EncountData::getRecord(int index)
{
    return (EncountData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int btl::EncountSpecial::getMonsterIndex(int group)
{
    return monsterIndex_[group];
}

inline int btl::EncountSpecial::getMonsterCount(int group)
{
    return monsterCount_[group];
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::EncountData::getArraySize()
{
    return binary_.getRecordCount();
}

THUMB btl::EncountData::EncountData()
{
}

THUMB btl::EncountData::~EncountData()
{
}

THUMB void btl::EncountData::setup(int tileId, bool flag)
{
    clear();
    if (tileId == -1) {
        tileId = 0;
    }
    tileId_ = tileId;
    setupData(flag);
    selectGroup();
    if (flag) {
        selectSpecialParty();
        selectOneGroup();
        selectMultiGroup();
    }
}

THUMB void btl::EncountData::setup(int tileId, TIME_ZONE timeZone, bool flag)
{
    clear();
    if (tileId == -1) {
        tileId = 0;
    }
    tileId_ = tileId;
    timeZone_ = timeZone;
    setupData(flag);
    selectGroup();
    if (flag) {
        selectSpecialParty();
        selectOneGroup();
        selectMultiGroup();
    }
}

THUMB void btl::EncountData::clear()
{
    for (int i = 0; i < 4; i++) {
        monsterIndex_[i] = 0;
        monsterCount_[i] = 0;
        monsterGroup_[i] = 0;
    }
}

THUMB unsigned char btl::getRandArrayIndex(unsigned char* ary, unsigned char count)
{
    unsigned char temp[256];
    int idx = 0;
    for (unsigned char i = 0; i < count; i++) {
        for (unsigned char j = 0; j < ary[i]; j++) {
            temp[idx] = i;
            idx++;
        }
    }
    return temp[UnkDssRand::rand(idx)];
}

THUMB void btl::EncountData::setupData(int flag)
{
    dq5::level::EncountData* encountData = dq5::level::EncountData::getRecord(tileId_);
    tileLevel_ = encountData->getTileLevel();
    stdTileRate_ = encountData->getStandard();
    teamAddEnable_ = encountData->getInvite();
    escapeDisable_ = encountData->getEscape();
    eventEncount_ = encountData->getEvent();
    sound_ = encountData->getBgm();
    setupFirstAttack();
    monsterInfo_[0].rate_ = encountData->getRatioA();
    monsterInfo_[0].monsterIndex_ = encountData->getMonsterA();
    monsterInfo_[0].countMax_ = encountData->getMaxA();
    monsterInfo_[1].rate_ = encountData->getRatioB();
    monsterInfo_[1].monsterIndex_ = encountData->getMonsterB();
    monsterInfo_[1].countMax_ = encountData->getMaxB();
    monsterInfo_[2].rate_ = encountData->getRatioC();
    monsterInfo_[2].monsterIndex_ = encountData->getMonsterC();
    monsterInfo_[2].countMax_ = encountData->getMaxC();
    monsterInfo_[3].rate_ = encountData->getRatioD();
    monsterInfo_[3].monsterIndex_ = encountData->getMonsterD();
    monsterInfo_[3].countMax_ = encountData->getMaxD();
    monsterInfo_[4].rate_ = encountData->getRatioE();
    monsterInfo_[4].monsterIndex_ = encountData->getMonsterE();
    monsterInfo_[4].countMax_ = encountData->getMaxE();
    monsterInfo_[5].rate_ = encountData->getRatioF();
    monsterInfo_[5].monsterIndex_ = encountData->getMonsterF();
    monsterInfo_[5].countMax_ = encountData->getMaxF();
    monsterInfo_[6].rate_ = encountData->getRatioG();
    monsterInfo_[6].monsterIndex_ = encountData->getMonsterG();
    monsterInfo_[6].countMax_ = encountData->getMaxG();
    monsterInfo_[7].rate_ = encountData->getRatioH();
    monsterInfo_[7].monsterIndex_ = encountData->getMonsterH();
    monsterInfo_[7].countMax_ = encountData->getMaxH();
    monsterInfo_[8].rate_ = encountData->getRatioI();
    monsterInfo_[8].monsterIndex_ = encountData->getMonsterI();
    monsterInfo_[8].countMax_ = encountData->getMaxI();
    monsterInfo_[9].rate_ = encountData->getRatioJ();
    monsterInfo_[9].monsterIndex_ = encountData->getMonsterJ();
    monsterInfo_[9].countMax_ = encountData->getMaxJ();
    specialRate_ = encountData->getRatioParticul();
    specialGroupIndex_ = encountData->getParticulParty();
    specialNightOnly_ = encountData->getParticulNight();
    if (flag) {
        monsterInfo_[0].countMax_ = getAppearCount(monsterInfo_[0].countMax_);
        monsterInfo_[1].countMax_ = getAppearCount(monsterInfo_[1].countMax_);
        monsterInfo_[2].countMax_ = getAppearCount(monsterInfo_[2].countMax_);
        monsterInfo_[3].countMax_ = getAppearCount(monsterInfo_[3].countMax_);
        monsterInfo_[4].countMax_ = getAppearCount(monsterInfo_[4].countMax_);
        monsterInfo_[5].countMax_ = getAppearCount(monsterInfo_[5].countMax_);
        monsterInfo_[6].countMax_ = getAppearCount(monsterInfo_[6].countMax_);
        monsterInfo_[7].countMax_ = getAppearCount(monsterInfo_[7].countMax_);
        monsterInfo_[8].countMax_ = getAppearCount(monsterInfo_[8].countMax_);
        monsterInfo_[9].countMax_ = getAppearCount(monsterInfo_[9].countMax_);
    }
}

THUMB void btl::EncountData::setTileId(int tileId)
{
    tileId_ = tileId;
    dq5::level::EncountData* encountData = dq5::level::EncountData::getRecord(tileId_);
    tileLevel_ = encountData->getTileLevel();
    stdTileRate_ = encountData->getStandard();
    teamAddEnable_ = encountData->getInvite();
    escapeDisable_ = encountData->getEscape();
    eventEncount_ = encountData->getEvent();
    sound_ = encountData->getBgm();
}

THUMB void btl::EncountData::setupFirstAttack()
{
    dq5::level::EncountData* encountData = dq5::level::EncountData::getRecord(tileId_);
    int type = encountData->getFirstattack();
    switch (type) {
    case 0:
        if (UnkDssRand::rand(32) == 0) {
            firstAttack_ = FirstAttackPlayer;
        }
        else if (UnkDssRand::rand(32) == 0) {
            firstAttack_ = FirstAttackMonster;
        }
        else {
            firstAttack_ = FirstAttackNone;
        }
        break;
    case 1:
        if (UnkDssRand::rand(32) == 0) {
            firstAttack_ = FirstAttackPlayer;
        }
        else if (UnkDssRand::rand(4) == 7) {
            firstAttack_ = FirstAttackMonster;
        }
        else {
            firstAttack_ = FirstAttackNone;
        }
        break;
    case 2:
        if (UnkDssRand::rand(4) == 0) {
            firstAttack_ = FirstAttackPlayer;
        }
        else if (UnkDssRand::rand(32) == 0) {
            firstAttack_ = FirstAttackMonster;
        }
        else {
            firstAttack_ = FirstAttackNone;
        }
        break;
    case 3:
        if (UnkDssRand::rand(4) == 0) {
            firstAttack_ = FirstAttackPlayer;
        }
        else if (UnkDssRand::rand(4) == 0) {
            firstAttack_ = FirstAttackMonster;
        }
        else {
            firstAttack_ = FirstAttackNone;
        }
        break;
    case 6:
        firstAttack_ = FirstAttackNone;
        break;
    }
}

THUMB void btl::EncountData::selectGroup()
{
    unsigned char temp[11] = {0};
    for (int i = 0; i < 11; i++) {
        temp[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        temp[i] = monsterInfo_[i].rate_;
    }
    temp[10] = specialRate_;
    selectGroup_ = getRandArrayIndex(temp, 11);
}

THUMB void btl::EncountData::selectSpecialParty()
{
    if (selectGroup_ == TYPE_K) {
        if (specialNightOnly_ != 0 && (timeZone_ == TIME_ZONE_EVENING || timeZone_ == TIME_ZONE_NIGHT)) {
            specialGroupIndex_ = specialNightOnly_;
        }
        encountSpecial_.setup(specialGroupIndex_);
        monsterIndex_[0] = encountSpecial_.getMonsterIndex(0);
        monsterCount_[0] = encountSpecial_.getMonsterCount(0);
        monsterIndex_[1] = encountSpecial_.getMonsterIndex(1);
        monsterCount_[1] = encountSpecial_.getMonsterCount(1);
        monsterIndex_[2] = encountSpecial_.getMonsterIndex(2);
        monsterCount_[2] = encountSpecial_.getMonsterCount(2);
        monsterIndex_[3] = encountSpecial_.getMonsterIndex(3);
        monsterCount_[3] = encountSpecial_.getMonsterCount(3);
    }
}

THUMB void btl::EncountData::selectOneGroup()
{
    if (selectGroup_ >= TYPE_F && selectGroup_ <= TYPE_J) {
        monsterIndex_[0] = monsterInfo_[selectGroup_].monsterIndex_;
        monsterCount_[0] = monsterInfo_[selectGroup_].countMax_;
        monsterIndex_[1] = 0;
        monsterCount_[1] = 0;
        monsterIndex_[2] = 0;
        monsterCount_[2] = 0;
        monsterIndex_[3] = 0;
        monsterCount_[3] = 0;
    }
}

THUMB void btl::EncountData::selectMultiGroup()
{
    if (selectGroup_ <= TYPE_E) {
        int groupCount = selectAE_GroupCount();
        int group = selectGroup_;
        while (true) {
            bool ret = selectAE_Add(group, groupCount + 1);
            if (!ret) {
                break;
            }
            group = selectA_E();
        }
    }
}

THUMB int btl::EncountData::selectAE_GroupCount()
{
    dq5::level::EncountData* encountData = dq5::level::EncountData::getRecord(tileId_);
    unsigned char temp[3];
    temp[0] = encountData->getGroup2();
    temp[1] = encountData->getGroup3();
    temp[2] = encountData->getGroup4();
    int index = getRandArrayIndex(temp, 3);
    return index + 1;
}

THUMB int btl::EncountData::selectA_E()
{
    unsigned char temp[5] = {0};
    for (int i = 0; i < 5; i++) {
        temp[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        temp[i] = monsterInfo_[i].rate_;
    }
    int group = getRandArrayIndex(temp, 5);
    return group;
}

THUMB bool btl::EncountData::selectAE_Add(int group, int groupMax)
{
    for (int i = 0; i < 4; i++) {
        if (i < groupMax) {
            if (monsterCount_[i] == 0) {
                monsterIndex_[i] = monsterInfo_[group].monsterIndex_;
                monsterCount_[i]++;
                monsterGroup_[i] = group;
                return true;
            }
            if (monsterCount_[i] != 0 && monsterGroup_[i] == group && monsterCount_[i] < (unsigned short)monsterInfo_[group].countMax_) {
                monsterCount_[i]++;
                return true;
            }
        }
    }
    return false;
}

THUMB int btl::EncountData::getEncountTileIdForPlayerLevel(int level)
{
    const unsigned int encountDataSize = dq5::level::EncountData::getArraySize();
    int tileID[128] = {0};
    for (int i = 0; i < 128; i++) {
        tileID[i] = 0;
    }
    int count = 0;
    int maxLevel = dss::clamp<int>(level - UnkDssRand::rand(3) - 4, 7, 45);
    for (int i = 0; i < encountDataSize; i++) {
        int tileLevel = dq5::level::EncountData::getRecord(i)->getTileLevel();
        if (tileLevel >= 7 && tileLevel <= maxLevel) {
            tileID[count] = i;
            count++;
        }
    }
    return tileID[UnkDssRand::rand(count)];
}

THUMB int btl::EncountData::getRandomTileID(int min, int max)
{
    unsigned int encountDataSize = dq5::level::EncountData::getArraySize();
    int tileID[128] = {0};
    for (int i = 0; i < 128; i++) {
        tileID[i] = 0;
    }
    int count = 0;
    int* p = tileID;
    do {
        for (int i = 0; i < encountDataSize; i++) {
            if (dq5::level::EncountData::getRecord(i)->getEvent() == 1) {
                continue;
            }
            int tileLevel = dq5::level::EncountData::getRecord(i)->getTileLevel();
            if (tileLevel >= min && tileLevel <= max) {
                *p++ = i;
                count++;
            }
        }
        min--;
        max--;
    } while (count == 0);
    return tileID[UnkDssRand::rand(count)];
}

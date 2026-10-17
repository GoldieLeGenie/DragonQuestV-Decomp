#include "main/status/PlayerData.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/text/TextAPI.hpp"

inline unsigned long dq5::level::CharacterInitData::getExp()
{
    return exp;
}

inline unsigned short dq5::level::CharacterInitData::getFriendID()
{
    return friendID;
}

inline unsigned short dq5::level::CharacterInitData::getStrength()
{
    return strength;
}

inline unsigned short dq5::level::CharacterInitData::getAgility()
{
    return agility;
}

inline unsigned short dq5::level::CharacterInitData::getVitality()
{
    return vitality;
}

inline unsigned short dq5::level::CharacterInitData::getIntelligence()
{
    return intelligence;
}

inline unsigned short dq5::level::CharacterInitData::getLuck()
{
    return luck;
}

inline unsigned short dq5::level::CharacterInitData::getHP()
{
    return HP;
}

inline unsigned short dq5::level::CharacterInitData::getMP()
{
    return MP;
}

inline unsigned short dq5::level::CharacterInitData::getWeapon()
{
    return weapon;
}

inline unsigned short dq5::level::CharacterInitData::getArmor()
{
    return armor;
}

inline unsigned short dq5::level::CharacterInitData::getShield()
{
    return shield;
}

inline unsigned short dq5::level::CharacterInitData::getHat()
{
    return hat;
}

inline unsigned short dq5::level::CharacterInitData::getBattle1()
{
    return battle1;
}

inline unsigned short dq5::level::CharacterInitData::getBattle2()
{
    return battle2;
}

inline unsigned short dq5::level::CharacterInitData::getBattle3()
{
    return battle3;
}

inline unsigned short dq5::level::CharacterInitData::getNormal1()
{
    return normal1;
}

inline unsigned short dq5::level::CharacterInitData::getNormal2()
{
    return normal2;
}

inline unsigned short dq5::level::CharacterInitData::getNormal3()
{
    return normal3;
}

inline unsigned short dq5::level::CharacterInitData::getCGNumber()
{
    return CGNumber;
}

inline unsigned short dq5::level::CharacterInitData::getJob()
{
    return job;
}

inline unsigned short dq5::level::CharacterInitData::getSex()
{
    return sex;
}

inline unsigned short dq5::level::CharacterInitData::getActionMonsterID()
{
    return actionMonsterID;
}

inline unsigned short dq5::level::CharacterInitData::getMonsterID()
{
    return monsterID;
}

inline unsigned short dq5::level::CharacterInitData::getBattle4()
{
    return battle4;
}

inline unsigned short dq5::level::CharacterInitData::getBattle5()
{
    return battle5;
}

inline unsigned short dq5::level::CharacterInitData::getBattle6()
{
    return battle6;
}

inline unsigned short dq5::level::CharacterInitData::getBattle7()
{
    return battle7;
}

inline unsigned short dq5::level::CharacterInitData::getBattle8()
{
    return battle8;
}

inline unsigned short dq5::level::CharacterInitData::getNormal4()
{
    return normal4;
}

inline unsigned short dq5::level::CharacterInitData::getNormal5()
{
    return normal5;
}

inline unsigned short dq5::level::CharacterInitData::getNormal6()
{
    return normal6;
}

inline unsigned short dq5::level::CharacterInitData::getNormal7()
{
    return normal7;
}

inline unsigned short dq5::level::CharacterInitData::getNormal8()
{
    return normal8;
}

inline unsigned char dq5::level::CharacterInitData::getEquipment()
{
    return equipment;
}

inline unsigned char dq5::level::CharacterInitData::getIcon()
{
    return icon;
}

inline unsigned char dq5::level::CharacterInitData::getMostLv()
{
    return mostLv;
}

inline unsigned char dq5::level::CharacterInitData::getLevel()
{
    return level;
}

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline char dq5::level::CharacterInitData::getCharacter() { return (byte_1 & 0x38) >> 3; }

THUMB status::PlayerData::PlayerData()
{
}

THUMB status::PlayerData::~PlayerData()
{
}

THUMB void status::PlayerData::setup(bool flag, int kind, int index, int offset)
{
    if (kind == 0) {
        return;
    }
    flag_.clear();
    index_ = index;
    kindIndex_ = kind;
    dq5::level::CharacterInitData* charaInitData = dq5::level::CharacterInitData::getRecord(kindIndex_);
    baseStatus_.clear();
    if (charaInitData->getFriendID() != 0) {
        nameId_ = (unsigned char)(offset + charaInitData->getFriendID());
        if (flag) {
            setupNameId(kindIndex_, offset);
        }
    } else {
        nameId_ = (unsigned char)index;
        if (flag) {
            if (index != kind && (kind == 0x3a || kind == 0x3b || kind == 0x52)) {
                nameId_ = kind;
            }
            TextAPI::extractText(name_, 0x200, 0x50000000, nameId_ + 500);
            int mst = TextAPI::getMacroStat();
            if (mst & MST_MALE) {
                nameBasedSex_ = SEX_MALE;
            }
            if (mst & MST_FEMALE) {
                nameBasedSex_ = SEX_FEMALE;
            }
        }
    }
    int level = charaInitData->getLevel();
    baseStatus_.level_ = level;
    baseStatus_.setStrength(charaInitData->getStrength());
    baseStatus_.setAgility(charaInitData->getAgility());
    baseStatus_.setProtection(charaInitData->getVitality());
    baseStatus_.setWisdom(charaInitData->getIntelligence());
    baseStatus_.setLuck(charaInitData->getLuck());
    int hp = charaInitData->getHP();
    baseStatus_.setHpMax(hp);
    baseStatus_.setHp(hp);
    int mp = charaInitData->getMP();
    baseStatus_.setMpMax(mp);
    baseStatus_.setMp(mp);
    baseStatus_.exp_ = charaInitData->getExp();
    haveItem_.clear();
    if (charaInitData->getWeapon() != 0) {
        int ctrl = haveItem_.add(charaInitData->getWeapon());
        haveItem_.setEquipment(ctrl);
    }
    if (charaInitData->getArmor() != 0) {
        int ctrl = haveItem_.add(charaInitData->getArmor());
        haveItem_.setEquipment(ctrl);
    }
    if (charaInitData->getShield() != 0) {
        int ctrl = haveItem_.add(charaInitData->getShield());
        haveItem_.setEquipment(ctrl);
    }
    if (charaInitData->getHat() != 0) {
        int ctrl = haveItem_.add(charaInitData->getHat());
        haveItem_.setEquipment(ctrl);
    }
    haveAction_.clear();
    haveAction_.setup(index_, 1);
    haveAction_.level_ = level;
    int battleAction = charaInitData->getBattle1();
    int usuallyAction = charaInitData->getNormal1();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle2();
    usuallyAction = charaInitData->getNormal2();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle3();
    usuallyAction = charaInitData->getNormal3();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle4();
    usuallyAction = charaInitData->getNormal4();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle5();
    usuallyAction = charaInitData->getNormal5();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle6();
    usuallyAction = charaInitData->getNormal6();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle7();
    usuallyAction = charaInitData->getNormal7();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    battleAction = charaInitData->getBattle8();
    usuallyAction = charaInitData->getNormal8();
    if (battleAction != 0 || usuallyAction != 0) {
        haveAction_.add(battleAction, usuallyAction, true);
    }
    haveEquipment_.setup(&haveItem_);
    command_ = 5;
}

THUMB void status::PlayerData::setupNameId(int kindIndex, int offset)
{
    if (kindIndex == 0x3a || kindIndex == 0x3b || kindIndex == 0x52) {
        return;
    }
    dq5::level::CharacterInitData* charaInitData = dq5::level::CharacterInitData::getRecord(kindIndex);
    nameId_ = offset + charaInitData->getFriendID();
    TextAPI::extractText(name_, 0x200, 0x50000000, nameId_ + 600);
    int mst = TextAPI::getMacroStat();
    if (mst & MST_MALE) {
        nameBasedSex_ = SEX_MALE;
    }
    if (mst & MST_FEMALE) {
        nameBasedSex_ = SEX_FEMALE;
    }
}

THUMB void status::PlayerData::setNameString(char* name)
{
    dss::strcpy(name_, name);
}

THUMB int status::PlayerData::getAttack()
{
    haveEquipment_.calcEffect();
    int attack = baseStatus_.strength_ + haveEquipment_.attack_;
    if (haveEquipment_.isEquipment(0x42)) {
        attack = 0x45;
    }
    return attack;
}

THUMB int status::PlayerData::getDefence()
{
    haveEquipment_.calcEffect();
    int defence = baseStatus_.protection_ + haveEquipment_.defence_;
    if (haveEquipment_.isEquipment(0x17)) {
        defence = 0;
    }
    if (haveEquipment_.isEquipment(0x75)) {
        defence = 0;
    }
    if (haveEquipment_.isEquipment(0x42)) {
        defence = 0x36;
    }
    return defence;
}

THUMB int status::PlayerData::getEquipStrength()
{
    haveEquipment_.calcEffect();
    int strength = baseStatus_.strength_ + haveEquipment_.strength_;
    return dss::clamp<int>(0, strength, 0xff);
}

THUMB int status::PlayerData::getEquipAgility()
{
    haveEquipment_.calcEffect();
    int agility = baseStatus_.agility_ + haveEquipment_.agility_;
    if (haveEquipment_.isEquipment(0x71)) {
        agility = 0;
    }
    if (haveEquipment_.isEquipment(0x42)) {
        agility = 0x2b;
    }
    if (haveEquipment_.isEquipment(0x9b)) {
        int base = baseStatus_.agility_;
        haveEquipment_.calcEffect();
        agility = haveEquipment_.agility_ + base * 2;
    }
    return dss::clamp<int>(0, agility, 0xff);
}

THUMB int status::PlayerData::getEquipProtection()
{
    int protection = baseStatus_.protection_;
    return dss::clamp<int>(0, protection, 0xff);
}

THUMB int status::PlayerData::getEquipWisdom()
{
    haveEquipment_.calcEffect();
    int wisdom = baseStatus_.wisdom_ + haveEquipment_.wisdom_;
    if (haveEquipment_.isEquipment(0x94)) {
        haveEquipment_.calcEffect();
        wisdom = baseStatus_.wisdom_ + haveEquipment_.wisdom_ + 15;
    }
    return dss::clamp<int>(0, wisdom, 0xff);
}

THUMB int status::PlayerData::getEquipLuck()
{
    haveEquipment_.calcEffect();
    int luck = baseStatus_.luck_ + haveEquipment_.luck_;
    return dss::clamp<int>(0, luck, 0xff);
}

THUMB int status::PlayerData::getCgIndex()
{
    dq5::level::CharacterInitData* charaInitData = dq5::level::CharacterInitData::getRecord(kindIndex_);
    if (kindIndex_ == 1) {
        if (g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
            return 200;
        }
        return 201;
    }
    if (kindIndex_ == 7 && haveEquipment_.isEquipment(0x45)) {
        return 0xdd;
    }
    if (kindIndex_ == 0xd) {
        return HaveStatusInfo::getSonCharaIndex();
    }
    if (kindIndex_ == 0xe) {
        return HaveStatusInfo::getDaughterCharaIndex();
    }
    return charaInitData->getCGNumber();
}

THUMB int status::PlayerData::getIconIndex()
{
    dq5::level::CharacterInitData* charaInitData = dq5::level::CharacterInitData::getRecord(kindIndex_);
    if (kindIndex_ == 0xd) {
        return HaveStatusInfo::getSonIconIndex();
    }
    if (kindIndex_ == 0xe) {
        return HaveStatusInfo::getDaughterIconIndex();
    }
    return charaInitData->getIcon();
}

THUMB int status::PlayerData::getEquipAttrIndex()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getEquipment();
}

THUMB int status::PlayerData::getCharacterKind()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getCharacter();
}

THUMB unsigned char status::PlayerData::getLevelMax()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getMostLv();
}

THUMB unsigned short status::PlayerData::getActionMonsterIndex()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getActionMonsterID();
}

THUMB unsigned short status::PlayerData::getJob()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getJob();
}

THUMB unsigned short status::PlayerData::getMonsterIndex()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getMonsterID();
}

THUMB unsigned short status::PlayerData::getSexId()
{
    return dq5::level::CharacterInitData::getRecord(kindIndex_)->getSex();
}

THUMB void status::PlayerData::setCurse4(bool flag)
{
    if (flag) {
        flag_.set(FLAG_STATUS_CHANGE_CURSE4);
    } else {
        flag_.remove(FLAG_STATUS_CHANGE_CURSE4);
    }
}

THUMB bool status::PlayerData::isCurse4()
{
    return flag_.check(FLAG_STATUS_CHANGE_CURSE4);
}

THUMB void status::PlayerData::setCurse5(bool flag)
{
    if (flag) {
        flag_.set(FLAG_STATUS_CHANGE_CURSE5);
    } else {
        flag_.remove(FLAG_STATUS_CHANGE_CURSE5);
    }
}

THUMB bool status::PlayerData::isCurse5()
{
    return flag_.check(FLAG_STATUS_CHANGE_CURSE5);
}

THUMB void status::PlayerData::setPoison(bool flag)
{
    if (flag) {
        flag_.set(FLAG_STATUS_CHANGE_POISON);
    } else {
        flag_.remove(FLAG_STATUS_CHANGE_POISON);
    }
}

THUMB bool status::PlayerData::isPoison()
{
    return flag_.check(FLAG_STATUS_CHANGE_POISON);
}

THUMB void status::PlayerData::setVenom(bool flag)
{
    if (flag) {
        flag_.set(FLAG_STATUS_CHANGE_VENOM);
    } else {
        flag_.remove(FLAG_STATUS_CHANGE_VENOM);
    }
}

THUMB bool status::PlayerData::isVenom()
{
    return flag_.check(FLAG_STATUS_CHANGE_VENOM);
}

THUMB void status::PlayerData::setFriendMonsterNameIndex(int index, bool flag)
{
    if (flag) {
        switch (index) {
        case 0:
            flag_.set(FLAG_NAME_INDEX_001);
            break;
        case 1:
            flag_.set(FLAG_NAME_INDEX_002);
            break;
        case 2:
            flag_.set(FLAG_NAME_INDEX_003);
            break;
        case 3:
            flag_.set(FLAG_NAME_INDEX_004);
            break;
        }
    } else {
        switch (getFriendMonsterNameIndex()) {
        case 0:
            flag_.remove(FLAG_NAME_INDEX_001);
            break;
        case 1:
            flag_.remove(FLAG_NAME_INDEX_002);
            break;
        case 2:
            flag_.remove(FLAG_NAME_INDEX_003);
            break;
        case 3:
            flag_.remove(FLAG_NAME_INDEX_004);
            break;
        }
    }
}

THUMB int status::PlayerData::getFriendMonsterNameIndex()
{
    if (flag_.check(FLAG_NAME_INDEX_001)) {
        return 0;
    }
    if (flag_.check(FLAG_NAME_INDEX_002)) {
        return 1;
    }
    if (flag_.check(FLAG_NAME_INDEX_003)) {
        return 2;
    }
    if (flag_.check(FLAG_NAME_INDEX_004)) {
        return 3;
    }
    return 0;
}

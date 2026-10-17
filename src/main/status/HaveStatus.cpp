#pragma ipa file
#include "main/status/HaveStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/leveldata/CharacterData.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned short dq5::level::MonsterData::getHP()
{
    return HP;
}

inline unsigned short dq5::level::MonsterData::getMP()
{
    return MP;
}

inline unsigned short dq5::level::MonsterData::getAttack()
{
    return attack;
}

inline unsigned short dq5::level::MonsterData::getDefence()
{
    return defence;
}

inline unsigned short dq5::level::MonsterData::getMoney()
{
    return money;
}

inline unsigned short dq5::level::MonsterData::getExp()
{
    return exp;
}

inline unsigned char dq5::level::MonsterData::getAgility()
{
    return agility;
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::PlayerData1::getExp()
{
    return exp;
}

inline unsigned short dq5::level::PlayerData1::getStrength()
{
    return strength;
}

inline unsigned short dq5::level::PlayerData1::getAgility()
{
    return agility;
}

inline unsigned short dq5::level::PlayerData1::getIntelligence()
{
    return intelligence;
}

inline unsigned short dq5::level::PlayerData1::getLuck()
{
    return luck;
}

inline unsigned short dq5::level::PlayerData1::getHP()
{
    return HP;
}

inline unsigned short dq5::level::PlayerData1::getMP()
{
    return MP;
}

inline unsigned short dq5::level::PlayerData1::getVitality()
{
    return vitality;
}

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline unsigned short status::PlayerData::getStrength()
{
    return baseStatus_.strength_;
}

inline void status::PlayerData::setStrength(unsigned short strength)
{
    baseStatus_.setStrength(strength);
}

inline unsigned char status::PlayerData::getAgility()
{
    return baseStatus_.agility_;
}

inline void status::PlayerData::setAgility(unsigned short agility)
{
    baseStatus_.setAgility(agility);
}

inline unsigned short status::PlayerData::getProtection()
{
    return baseStatus_.protection_;
}

inline void status::PlayerData::setProtection(unsigned short protection)
{
    baseStatus_.setProtection(protection);
}

inline unsigned char status::PlayerData::getWisdom()
{
    return baseStatus_.wisdom_;
}

inline void status::PlayerData::setWisdom(unsigned char wisdom)
{
    baseStatus_.setWisdom(wisdom);
}

inline unsigned char status::PlayerData::getLuck()
{
    return baseStatus_.luck_;
}

inline void status::PlayerData::setLuck(unsigned char luck)
{
    baseStatus_.setLuck(luck);
}

inline unsigned short status::PlayerData::getHp()
{
    return baseStatus_.hp_;
}

inline void status::PlayerData::setHp(unsigned short hp)
{
    baseStatus_.setHp(hp);
}

inline unsigned short status::PlayerData::getHpMax()
{
    return baseStatus_.hpMax_;
}

inline void status::PlayerData::setHpMax(unsigned short hpMax)
{
    baseStatus_.setHpMax(hpMax);
}

inline unsigned short status::PlayerData::getMp()
{
    return baseStatus_.mp_;
}

inline void status::PlayerData::setMp(unsigned short mp)
{
    baseStatus_.setMp(mp);
}

inline unsigned short status::PlayerData::getMpMax()
{
    return baseStatus_.mpMax_;
}

inline void status::PlayerData::setMpMax(unsigned short mpMax)
{
    baseStatus_.setMpMax(mpMax);
}

inline int status::PlayerData::getExp()
{
    return baseStatus_.exp_;
}

inline void status::PlayerData::setExp(int exp)
{
    baseStatus_.exp_ = exp;
}

inline unsigned char status::PlayerData::getLevel()
{
    return baseStatus_.level_;
}

inline void status::PlayerData::setLevel(unsigned char lvl)
{
    baseStatus_.level_ = lvl;
}

inline unsigned char status::PlayerData::getCommand()
{
    return command_;
}

inline void status::PlayerData::setCommand(unsigned char val)
{
    command_ = val;
}

inline unsigned char status::PlayerData::getActionCursorIndex()
{
    return actionCursorIndex_;
}

inline void status::PlayerData::setActionCursorIndex(unsigned char idx)
{
    actionCursorIndex_ = idx;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

// hero, friend or friend monster: bit test on playerType_ - 1
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline bool status::HaveStatus::isNoBattleNpc() const
{
    return playerType_ == TYPE_NOBATTLENPC;
}

// the short instances of the dss header templates are in this file
namespace dss {
    template <> short max<short>(short a, short b);
    template <> short min<short>(short a, short b);
}

int status::HaveStatus::seinenki_;
status::BaseStatus status::HaveStatus::diffStatus_;

THUMB status::HaveStatus::HaveStatus()
{
}

THUMB status::HaveStatus::~HaveStatus()
{
}

THUMB void status::HaveStatus::setup(unsigned short index, int flag)
{
    if (flag == 1) {
        setupPlayer(index);
    } else {
        setupMonster(index, true);
    }
}

THUMB void status::HaveStatus::setupPlayer(unsigned short index)
{
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);

    playerIndex_ = index;
    playerKindIndex_ = playerData.getKindIndex();
    baseStatus_.strength_ = (unsigned char)playerData.getStrength();
    baseStatus_.agility_ = playerData.getAgility();
    baseStatus_.protection_ = (unsigned char)playerData.getProtection();
    baseStatus_.wisdom_ = playerData.getWisdom();
    baseStatus_.luck_ = playerData.getLuck();
    baseStatus_.hp_ = playerData.getHp();
    baseStatus_.hpMax_ = playerData.getHpMax();
    baseStatus_.mp_ = playerData.getMp();
    baseStatus_.mpMax_ = playerData.getMpMax();
    charaIndex_ = playerData.getCgIndex();
    monsterIndex_ = playerData.getActionMonsterIndex();
    iconIndex_ = playerData.getIconIndex();
    equipAttrIndex_ = playerData.getEquipAttrIndex();
    exp_ = playerData.getExp();
    level_ = playerData.getLevel();
    levelMax_ = playerData.getLevelMax();
    jobId_ = playerData.getJob();
    monsterId_ = playerData.getMonsterIndex();
    sexId_ = playerData.getSexId();
    command_ = playerData.getCommand();
    actionCursorIndex_ = playerData.getActionCursorIndex();

    if (level_ < levelMax_) {
        dq5::level::PlayerData1* playerLevelData = getLevelupData(playerKindIndex_, level_ + 1);
        baseStatus_.exp_ = playerLevelData->getExp();
    }

    switch (playerData.getCharacterKind()) {
        case 1:
            playerType_ = TYPE_HERO;
            break;
        case 2:
            playerType_ = TYPE_FRIEND;
            break;
        case 3:
            playerType_ = TYPE_BATTLENPC;
            break;
        case 4:
            playerType_ = TYPE_NOBATTLENPC;
            break;
        case 5:
            playerType_ = TYPE_FRIENDMONSTER;
            break;
    }

    if (isNoBattleNpc()) {
        baseStatus_.hp_ = 10;
        baseStatus_.hpMax_ = 10;
    }
}

THUMB void status::HaveStatus::setupMonster(unsigned short index, bool flag)
{
    dq5::level::MonsterData* monsterData2_ = dq5::level::MonsterData::getRecord(index);

    baseStatus_.strength_ = monsterData2_->getAttack();
    baseStatus_.agility_ = monsterData2_->getAgility();
    baseStatus_.protection_ = monsterData2_->getDefence();
    baseStatus_.wisdom_ = 0;
    baseStatus_.luck_ = 0;
    baseStatus_.hp_ = monsterData2_->getHP();
    baseStatus_.hpMax_ = monsterData2_->getHP();
    baseStatus_.mp_ = monsterData2_->getMP();
    baseStatus_.mpMax_ = monsterData2_->getMP();
    if (baseStatus_.mpMax_ == 0xff) {
        baseStatus_.mp_ = 1000;
        baseStatus_.mpMax_ = 1000;
    }

    if (flag) {
        playerIndex_ = index;
        playerKindIndex_ = index;
        charaIndex_ = 0;
        iconIndex_ = 0;
        level_ = 0;
        exp_ = monsterData2_->getExp();
        gold_ = monsterData2_->getMoney();
        playerType_ = TYPE_MONSTER;
        isPlayer_ = 0;
        isBattleNpc_ = 0;
        isNoBattleNpc_ = 0;
        isSpecialNpc_ = 0;
        isMonster_ = 0;
    }
}

THUMB void status::HaveStatus::cleanup()
{
    if (playerType_ != TYPE_MONSTER) {
        cleanupPlayer();
    }
}

THUMB void status::HaveStatus::cleanupPlayer()
{
    PlayerData& playerData = PlayerDataAll::getPlayerData(playerIndex_);

    playerData.setStrength(baseStatus_.strength_);
    playerData.setAgility(baseStatus_.agility_);
    playerData.setProtection(baseStatus_.protection_);
    playerData.setWisdom(baseStatus_.wisdom_);
    playerData.setLuck(baseStatus_.luck_);
    playerData.setHp(baseStatus_.hp_);
    playerData.setHpMax(baseStatus_.hpMax_);
    playerData.setMp(baseStatus_.mp_);
    playerData.setMpMax(baseStatus_.mpMax_);
    playerData.setExp(exp_);
    playerData.setLevel(level_);
    playerData.setCommand(command_);
    playerData.setActionCursorIndex(actionCursorIndex_);
}

THUMB void status::HaveStatus::resetExpGold()
{
    dq5::level::MonsterData* monsterData2_ = dq5::level::MonsterData::getRecord(playerIndex_);
    exp_ = monsterData2_->getExp();
    gold_ = monsterData2_->getMoney();
}

THUMB bool status::HaveStatus::isLevelup()
{
    if (!isPlayer()) {
        return false;
    }
    if (level_ == levelMax_) {
        return false;
    }
    if (exp_ >= baseStatus_.exp_) {
        return true;
    }
    return false;
}

THUMB void status::HaveStatus::debugLevelup(int level)
{
    if (levelMax_ == 0) {
        return;
    }
    if (level >= levelMax_) {
        level = levelMax_;
    }

    dq5::level::PlayerData1 playerData = *getLevelupData(playerKindIndex_, level);
    baseStatus_.strength_ = (unsigned char)playerData.getStrength();
    baseStatus_.agility_ = playerData.getAgility();
    baseStatus_.protection_ = (unsigned char)playerData.getVitality();
    baseStatus_.wisdom_ = playerData.getIntelligence();
    baseStatus_.luck_ = playerData.getLuck();
    baseStatus_.hp_ = playerData.getHP();
    baseStatus_.hpMax_ = playerData.getHP();
    baseStatus_.mp_ = playerData.getMP();
    baseStatus_.mpMax_ = playerData.getMP();
    level_ = level;
    exp_ = playerData.getExp();

    if (level < levelMax_) {
        dq5::level::PlayerData1 playerData2 = *getLevelupData(playerKindIndex_, level + 1);
        baseStatus_.exp_ = playerData2.getExp();
    } else {
        baseStatus_.exp_ = playerData.getExp();
    }
}

THUMB void status::HaveStatus::levelup(bool flag)
{
    if (level_ >= levelMax_) {
        return;
    }

    level_++;
    if (flag) {
        exp_ = baseStatus_.exp_;
    }

    BaseStatus tempStatus;
    dq5::level::PlayerData1 playerData0 = *getLevelupData(playerKindIndex_, level_ - 1);
    dq5::level::PlayerData1 playerData1 = *getLevelupData(playerKindIndex_, level_);

    unsigned short nextStrength = playerData1.getStrength();
    tempStatus.strength_ = (unsigned char)(nextStrength - playerData0.getStrength());
    unsigned short nextAgility = playerData1.getAgility();
    tempStatus.agility_ = nextAgility - playerData0.getAgility();
    unsigned short nextProtection = playerData1.getVitality();
    tempStatus.protection_ = (unsigned char)(nextProtection - playerData0.getVitality());
    unsigned short nextWisdom = playerData1.getIntelligence();
    tempStatus.wisdom_ = nextWisdom - playerData0.getIntelligence();
    unsigned short nextLuck = playerData1.getLuck();
    tempStatus.luck_ = nextLuck - playerData0.getLuck();
    unsigned short nextHpMax = playerData1.getHP();
    tempStatus.hpMax_ = (unsigned char)(nextHpMax - playerData0.getHP());
    unsigned short nextMpMax = playerData1.getMP();
    tempStatus.mpMax_ = (unsigned char)(nextMpMax - playerData0.getMP());

    if (level_ < levelMax_) {
        dq5::level::PlayerData1 playerData2 = *getLevelupData(playerKindIndex_, level_ + 1);
        baseStatus_.exp_ = playerData2.getExp();
    }

    diffStatus_.strength_ = (unsigned char)levelupAdd(tempStatus.strength_);
    tempStatus.strength_ = baseStatus_.strength_;
    baseStatus_.strength_ = (unsigned char)dss::clamp<unsigned short>(levelupAjustSpecial(baseStatus_.strength_, diffStatus_.strength_, nextStrength), 0, 0xff);
    diffStatus_.strength_ = (unsigned char)(baseStatus_.strength_ - tempStatus.strength_);

    diffStatus_.agility_ = levelupAdd(tempStatus.agility_);
    tempStatus.agility_ = baseStatus_.agility_;
    baseStatus_.agility_ = dss::clamp<unsigned short>(levelupAjust(baseStatus_.agility_, diffStatus_.agility_, nextAgility), 0, 0xff);
    diffStatus_.agility_ = baseStatus_.agility_ - tempStatus.agility_;

    diffStatus_.protection_ = (unsigned char)levelupAdd(tempStatus.protection_);
    tempStatus.protection_ = baseStatus_.protection_;
    baseStatus_.protection_ = (unsigned char)dss::clamp<unsigned short>(levelupAjust(baseStatus_.protection_, diffStatus_.protection_, nextProtection), 0, 0xff);
    diffStatus_.protection_ = (unsigned char)(baseStatus_.protection_ - tempStatus.protection_);

    diffStatus_.wisdom_ = levelupAdd(tempStatus.wisdom_);
    tempStatus.wisdom_ = baseStatus_.wisdom_;
    baseStatus_.wisdom_ = dss::clamp<unsigned short>(levelupAjust(baseStatus_.wisdom_, diffStatus_.wisdom_, nextWisdom), 0, 0xff);
    diffStatus_.wisdom_ = baseStatus_.wisdom_ - tempStatus.wisdom_;

    diffStatus_.luck_ = levelupAdd(tempStatus.luck_);
    tempStatus.luck_ = baseStatus_.luck_;
    baseStatus_.luck_ = dss::clamp<unsigned short>(levelupAjust(baseStatus_.luck_, diffStatus_.luck_, nextLuck), 0, 0xff);
    diffStatus_.luck_ = baseStatus_.luck_ - tempStatus.luck_;

    diffStatus_.hpMax_ = (unsigned char)levelupAdd(tempStatus.hpMax_);
    tempStatus.hpMax_ = baseStatus_.hpMax_;
    baseStatus_.hpMax_ = dss::clamp<unsigned short>(levelupAjustSpecial(baseStatus_.hpMax_, diffStatus_.hpMax_, nextHpMax), 0, 999);
    diffStatus_.hpMax_ = baseStatus_.hpMax_ - tempStatus.hpMax_;

    diffStatus_.mpMax_ = (unsigned char)levelupAdd(tempStatus.mpMax_);
    tempStatus.mpMax_ = baseStatus_.mpMax_;
    baseStatus_.mpMax_ = dss::clamp<unsigned short>(levelupAjust(baseStatus_.mpMax_, diffStatus_.mpMax_, nextMpMax), 0, 999);
    diffStatus_.mpMax_ = baseStatus_.mpMax_ - tempStatus.mpMax_;

    if (flag) {
        baseStatus_.hp_ = baseStatus_.hpMax_;
        baseStatus_.mp_ = baseStatus_.mpMax_;
    }
}

THUMB unsigned short status::HaveStatus::levelupAdd(unsigned short value)
{
    unsigned short rand = UnkDssRand::rand(50) + 75;
    unsigned short result = (unsigned short)(value * rand + 50) / 100;
    if (result < value) {
        result = value;
    }
    return result;
}

THUMB unsigned short status::HaveStatus::levelupAjust(unsigned short value, unsigned short diff, unsigned short normal)
{
    unsigned short upper = normal * 150 / 100;
    unsigned short lower = normal * 75 / 100;
    if (value > upper) {
        return value + UnkDssRand::rand(2);
    }
    if (value + diff > upper) {
        return value + UnkDssRand::rand(2);
    }
    if (value + diff < lower) {
        return lower;
    }
    return value + diff;
}

THUMB unsigned short status::HaveStatus::levelupAjustSpecial(unsigned short value, unsigned short diff, unsigned short normal)
{
    unsigned short upper0 = normal * 130 / 100 + 15;
    unsigned short upper1 = normal + 60;
    unsigned short upper = (upper0 < upper1) ? upper0 : upper1;
    short lower0 = normal * 86 / 100;
    lower0 = dss::clamp<int>(lower0, 0, 1000);
    short lower1 = normal - 30;
    lower1 = dss::clamp<int>(lower1, 0, 1000);
    unsigned short lower = (lower0 > lower1) ? lower0 : lower1;
    if (value > upper) {
        return value + UnkDssRand::rand(2);
    }
    if (value + diff > upper) {
        return value + UnkDssRand::rand(2);
    }
    if (value + diff < lower) {
        return lower;
    }
    return value + diff;
}

THUMB void status::HaveStatus::setCharaIndex(int index)
{
    charaIndex_ = index;
}

THUMB int status::HaveStatus::getCharaIndex() const
{
    if (playerIndex_ == 1 && seinenki_) {
        return 201;
    }
    return charaIndex_;
}

THUMB int status::HaveStatus::getIconIndex() const
{
    if (playerIndex_ == 1 && seinenki_) {
        return 2;
    }
    return iconIndex_;
}

THUMB void status::HaveStatus::addExp(int exp)
{
    if (exp_ != -1) {
        exp_ = exp_ + exp;
        exp_ = dss::clamp<int>(exp_, 0, 0xffffff);
    }
}

THUMB void status::HaveStatus::setExp(int exp)
{
    if (exp_ != -1) {
        exp_ = exp;
        exp_ = dss::clamp<int>(exp, 0, 0xffffff);
    }
}

THUMB int status::HaveStatus::getLevelupExp() const
{
    return baseStatus_.exp_ - exp_;
}

THUMB Sex status::HaveStatus::getSex() const
{
    if (sexId_ == 0x114) {
        return SEX_MALE;
    }
    if (sexId_ == 0x115) {
        return SEX_FEMALE;
    }
    return SEX_NONE;
}

THUMB void status::HaveStatus::addStrength(char value)
{
    baseStatus_.addStrength(value);
}

THUMB unsigned char status::HaveStatus::getAgility() const
{
    return dss::clamp<unsigned short>(baseStatus_.agility_, 0, 0xff);
}

THUMB void status::HaveStatus::addAgility(char value)
{
    baseStatus_.addAgility(value);
}

THUMB void status::HaveStatus::addProtection(char value)
{
    baseStatus_.addProtection(value);
}

THUMB unsigned char status::HaveStatus::getWisdom() const
{
    return dss::clamp<unsigned short>(baseStatus_.wisdom_, 0, 0xff);
}

THUMB void status::HaveStatus::addWisdom(char value)
{
    baseStatus_.addWisdom(value);
}

THUMB void status::HaveStatus::addLuck(char value)
{
    baseStatus_.luck_ = dss::clamp<short>(baseStatus_.luck_ + value, 0, 0xff);
}

template <> THUMB short dss::clamp<short>(short a, short b, short c)
{
    return min(max(a, b), c);
}

template <> THUMB short dss::max<short>(short a, short b)
{
    return (a > b) ? a : b;
}

template <> THUMB short dss::min<short>(short a, short b)
{
    return (a < b) ? a : b;
}

THUMB unsigned char status::HaveStatus::getLuck() const
{
    return dss::clamp<unsigned short>(baseStatus_.luck_, 0, 0xff);
}

THUMB void status::HaveStatus::setHp(unsigned short hp)
{
    baseStatus_.hp_ = dss::clamp<unsigned short>(hp, 0, baseStatus_.hpMax_);
}

THUMB unsigned short status::HaveStatus::getHp() const
{
    return dss::clamp<unsigned short>(baseStatus_.hp_, 0, 9999);
}

THUMB void status::HaveStatus::setHpMax(unsigned short hpMax)
{
    baseStatus_.setHpMax(hpMax);
    baseStatus_.hp_ = dss::clamp<unsigned short>(baseStatus_.hp_, 1, baseStatus_.hpMax_);
}

THUMB unsigned short status::HaveStatus::getHpMax() const
{
    return dss::clamp<unsigned short>(baseStatus_.hpMax_, 0, 9999);
}

THUMB void status::HaveStatus::addHpMax(char value)
{
    if (baseStatus_.mp_ != 1000) {
        baseStatus_.addHpMax(value);
    }
}

THUMB void status::HaveStatus::setMp(unsigned short mp)
{
    baseStatus_.mp_ = dss::clamp<unsigned short>(mp, 0, baseStatus_.mpMax_);
}

THUMB unsigned short status::HaveStatus::getMp() const
{
    return dss::clamp<unsigned short>(baseStatus_.mp_, 0, 999);
}

THUMB void status::HaveStatus::setMpMax(unsigned short mpMax)
{
    baseStatus_.setMpMax(mpMax);
    baseStatus_.mp_ = dss::clamp<unsigned short>(baseStatus_.mp_, 0, baseStatus_.mpMax_);
}

THUMB unsigned short status::HaveStatus::getMpMax() const
{
    return dss::clamp<unsigned short>(baseStatus_.mpMax_, 0, 999);
}

THUMB void status::HaveStatus::addMpMax(char value)
{
    baseStatus_.addMpMax(value);
}

THUMB unsigned short status::HaveStatus::getDefence() const
{
    return dss::clamp<unsigned short>(baseStatus_.protection_, 0, 9999);
}

THUMB void status::HaveStatus::addBaseHp(int value)
{
    baseStatus_.hp_ = dss::clamp<int>(baseStatus_.hp_ + value, 0, baseStatus_.hpMax_);
}

THUMB void status::HaveStatus::addBaseMp(int value)
{
    if (baseStatus_.mp_ != 1000) {
        baseStatus_.mp_ = dss::clamp<int>(baseStatus_.mp_ + value, 0, baseStatus_.mpMax_);
    }
}

THUMB dq5::level::PlayerData1* status::HaveStatus::getLevelupData(int playerIndex, int level)
{
    switch (playerIndex) {
        case 7:
            playerIndex = 6;
            break;
        case 8:
            return 0;
        case 15:
            return 0;
    }
    return dq5::level::CharacterData::getRecord(playerIndex, level);
}

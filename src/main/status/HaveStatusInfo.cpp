#include "main/status/HaveStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseItem.hpp"

inline void status::ActionDefence::setNifram(unsigned char nif)
{
    nifram_ = nif;
}

inline void status::HaveEquipment::calcEquipment(int itemIndex)
{
    calcEquipmentItemIndex_ = itemIndex;
}

inline unsigned short status::HaveEquipment::getAttack()
{
    return attack_;
}

inline unsigned short status::HaveEquipment::getDefence()
{
    return defence_;
}

inline unsigned char status::HaveEquipment::getStrength()
{
    return strength_;
}

inline unsigned char status::HaveEquipment::getAgility()
{
    return agility_;
}

inline unsigned char status::HaveEquipment::getWisdom()
{
    return wisdom_;
}

inline unsigned char status::HaveEquipment::getLuck()
{
    return luck_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline unsigned short status::HaveStatus::getMonsterIndex() const
{
    return monsterIndex_;
}

inline int status::HaveStatus::getMonsterKind() const
{
    return monsterId_;
}

inline bool status::HaveStatus::isBattleNpc() const
{
    return playerType_ == TYPE_BATTLENPC;
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline int status::HaveStatus::getEquipAttrIndex() const
{
    return equipAttrIndex_;
}

inline int status::HaveStatus::getExp() const
{
    return exp_;
}

inline int status::HaveStatus::getGold() const
{
    return gold_;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline int status::HaveStatus::getLevelMax() const
{
    return levelMax_;
}

inline unsigned short status::HaveStatus::getStrength() const
{
    return baseStatus_.strength_;
}

inline unsigned short status::HaveStatus::getProtection() const
{
    return baseStatus_.protection_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline void status::HaveStatusInfo::allFlagClear()
{
    flag_.clear();
    flag2_.clear();
    testFlag_.clear();
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

dss::BitFlag<unsigned int> status::HaveStatusInfo::globalFlag_;


THUMB status::HaveStatusInfo::HaveStatusInfo()
    : noDamage_(0), allEquipment_(0), defenceChange_(0), agilityChange_(0)
{
    commandTypeDebug_ = 0;
}

THUMB status::HaveStatusInfo::~HaveStatusInfo()
{
}

THUMB void status::HaveStatusInfo::setup(int index, bool flag)
{
    index_ = index;
    haveBattleStatus_ = 0;
    effectValue_ = 0;
    effectValueMax_ = 0;
    effectValueMin_ = 0;
    allFlagClear();
    if (flag) {
        characterType_ = PLAYER;
        haveStatus_.setup(index_, true);
        haveItem_.setup(index_);
        haveAction_.setup(index_, 1);
        haveEquipment_.setup(&haveItem_);
        setupActionDefence();
        statusChange_.restore(index_);
    } else {
        characterType_ = MONSTER;
        haveStatus_.setup(index_, false);
        haveItem_.setup(1);
        haveItem_.clear();
        haveEquipment_.setup(&haveItem_);
        actionDefence_.setup(index_, MONSTER);
        statusChange_.clear();
    }
}

THUMB void status::HaveStatusInfo::setupMonster(int index)
{
    index_ = index;
    characterType_ = MONSTER;
    haveStatus_.setup(index_, false);
    haveItem_.setup(1);
    haveItem_.clear();
    haveEquipment_.setup(&haveItem_);
    actionDefence_.setup(index_, MONSTER);
}

THUMB void status::HaveStatusInfo::cleanup()
{
    if (characterType_ == PLAYER) {
        haveStatus_.cleanup();
        haveItem_.cleanup(index_);
        haveAction_.cleanup(index_);
        statusChange_.store(index_);
    }
}

THUMB void status::HaveStatusInfo::setupStatus(int index, bool flag)
{
    index_ = index;
    if (flag == true) {
        characterType_ = PLAYER;
        haveStatus_.setup(index_, (unsigned short)index_);
        actionDefence_.setup(index_, PLAYER);
        return;
    }
    if (flag == false) {
        characterType_ = MONSTER;
        haveStatus_.setup(index_, false);
        actionDefence_.setup(index_, MONSTER);
    }
}

THUMB void status::HaveStatusInfo::setupActionDefence()
{
    actionDefence_.setup(index_, PLAYER);
    if (haveStatus_.isBattleNpc()) {
        int monsterIndex_ = haveStatus_.getMonsterIndex();
        actionDefence_.setup(monsterIndex_, MONSTER);
    } else if (haveStatus_.isFriendMonster()) {
        int monsterIndex_ = haveStatus_.getMonsterKind();
        actionDefence_.setup(monsterIndex_, MONSTER);
        actionDefence_.setNifram(3);
        if (haveStatus_.getPlayerKindIndex() == 0x3a || haveStatus_.getPlayerKindIndex() == 0x3b) {
            actionDefence_.setup(monsterIndex_, PLAYER);
        }
    }
}

THUMB void status::HaveStatusInfo::setupActionDefence(int index, bool flag)
{
    if (flag == true) {
        actionDefence_.setup(index, PLAYER);
    } else if (flag == false) {
        actionDefence_.setup(index, MONSTER);
    }
}

THUMB int status::HaveStatusInfo::getCharaIndex()
{
    int playerIndex = getPlayerIndex();
    if (playerIndex == 1) {
        if (g_Story.getChapter() == 1) {
            return 0xc8;
        }
        return 0xc9;
    }
    if (playerIndex == 7) {
        if (getHaveEquipment().isEquipment(0x45)) {
            return 0xdd;
        }
        return 0xde;
    }
    if (playerIndex == 0xd) {
        return getSonCharaIndex();
    }
    if (playerIndex == 0xe) {
        return getDaughterCharaIndex();
    }
    return haveStatus_.getCharaIndex();
}

THUMB int status::HaveStatusInfo::getIconIndex()
{
    if (getPlayerIndex() == 7 && getHaveEquipment().isEquipment(0x45)) {
        return 0x5f;
    }
    int playerIndex = getPlayerIndex();
    if (playerIndex == 0xd) {
        return getSonIconIndex();
    }
    if (playerIndex == 0xe) {
        return getDaughterIconIndex();
    }
    return haveStatus_.getIconIndex();
}

THUMB int status::HaveStatusInfo::getSonIconIndex()
{
    if (g_AreaFlag.check(0xeb)) {
        return 0xd;
    }
    if (g_AreaFlag.check(0xec)) {
        return 0xe;
    }
    if (g_AreaFlag.check(0x259)) {
        return 0xf;
    }
    return 0xd;
}

THUMB int status::HaveStatusInfo::getDaughterIconIndex()
{
    if (g_AreaFlag.check(0xeb)) {
        return 0x10;
    }
    if (g_AreaFlag.check(0xec)) {
        return 0x11;
    }
    if (g_AreaFlag.check(0x259)) {
        return 0x12;
    }
    return 0x10;
}

THUMB int status::HaveStatusInfo::getSonCharaIndex()
{
    if (g_AreaFlag.check(0xeb)) {
        return 0xd6;
    }
    if (g_AreaFlag.check(0xec)) {
        return 0xd7;
    }
    if (g_AreaFlag.check(0x259)) {
        return 0xe9;
    }
    return 0xd6;
}

THUMB int status::HaveStatusInfo::getDaughterCharaIndex()
{
    if (g_AreaFlag.check(0xeb)) {
        return 0xd8;
    }
    if (g_AreaFlag.check(0xec)) {
        return 0xd9;
    }
    if (g_AreaFlag.check(0x259)) {
        return 0xea;
    }
    return 0xd8;
}

THUMB void status::HaveStatusInfo::levelup(int level)
{
    if (level == 0) {
        haveStatus_.levelup(false);
        haveAction_.levelup(index_, haveStatus_.getLevel(), true);
        return;
    }
    if (level > haveStatus_.getLevelMax()) {
        level = haveStatus_.getLevelMax();
    }
    haveStatus_.debugLevelup(level);
    haveAction_.debugLevelup(level);
}

THUMB unsigned short status::HaveStatusInfo::getStrength(int effect)
{
    if (effect & 1) {
        return haveStatus_.getStrength();
    }
    haveEquipment_.calcEffect();
    unsigned short strength = haveStatus_.getStrength() + haveEquipment_.getStrength();
    if (characterType_ == PLAYER) {
        strength = (unsigned char)dss::clamp<unsigned short>(strength, 0, 0xff);
    }
    return strength;
}

THUMB unsigned char status::HaveStatusInfo::getAgility(int effect)
{
    if (effect & 1) {
        return haveStatus_.getAgility();
    }
    haveEquipment_.calcEffect();
    unsigned short agility = haveStatus_.getAgility() + haveEquipment_.getAgility();
    if (haveEquipment_.isEquipment(0x9b)) {
        haveEquipment_.calcEffect();
        agility = getAgilityChange() + (haveEquipment_.getAgility() + haveStatus_.getAgility() * 2);
    } else {
        haveEquipment_.calcEffect();
        agility = getAgilityChange() + (haveStatus_.getAgility() + haveEquipment_.getAgility());
    }
    if (haveEquipment_.isEquipment(0x71)) {
        agility = 0;
    }
    if (haveEquipment_.isEquipment(0x42)) {
        agility = 0x2b;
    }
    return dss::clamp<unsigned short>(agility, 0, 0xff);
}

THUMB short status::HaveStatusInfo::getAgilityChange()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_SPD_PLUS)) {
        return agilityChange_;
    }
    return 0;
}

THUMB void status::HaveStatusInfo::clearAgilityChange()
{
    agilityChange_ = 0;
}

THUMB unsigned short status::HaveStatusInfo::getProtection(int effect)
{
    if (effect & 1) {
        return haveStatus_.getProtection();
    }
    unsigned short protection = haveStatus_.getProtection();
    if (characterType_ == PLAYER) {
        protection = dss::clamp<unsigned short>(protection, 0, 0xff);
    }
    return protection;
}

THUMB unsigned char status::HaveStatusInfo::getWisdom(int effect)
{
    if (effect & 1) {
        return haveStatus_.getWisdom();
    }
    haveEquipment_.calcEffect();
    unsigned short wisdom = haveStatus_.getWisdom() + haveEquipment_.getWisdom();
    if (haveEquipment_.isEquipment(0x94)) {
        haveEquipment_.calcEffect();
        wisdom = haveStatus_.getWisdom() + haveEquipment_.getWisdom() + 15;
    } else {
        haveEquipment_.calcEffect();
        wisdom = haveStatus_.getWisdom() + haveEquipment_.getWisdom();
    }
    return dss::clamp<unsigned short>(wisdom, 0, 0xff);
}

THUMB unsigned char status::HaveStatusInfo::getLuck(int effect)
{
    if (effect & 1) {
        return haveStatus_.getLuck();
    }
    haveEquipment_.calcEffect();
    unsigned short luck = haveStatus_.getLuck() + haveEquipment_.getLuck();
    return dss::clamp<unsigned short>(luck, 0, 0xff);
}

THUMB int status::HaveStatusInfo::getExp() const
{
    return haveStatus_.getExp();
}

THUMB void status::HaveStatusInfo::addExp(int exp)
{
    haveStatus_.addExp(exp);
}

THUMB int status::HaveStatusInfo::getLevelupExp() const
{
    return haveStatus_.getLevelupExp();
}

THUMB int status::HaveStatusInfo::getGold() const
{
    return haveStatus_.getGold();
}

THUMB void status::HaveStatusInfo::setHp(unsigned short hp)
{
    if (noDamage_ == 0) {
        haveStatus_.setHp(hp);
        execDeath();
    }
}

THUMB short status::HaveStatusInfo::getHp() const
{
    return haveStatus_.getHp();
}

THUMB void status::HaveStatusInfo::addHp(int hp)
{
    if (noDamage_ == 0) {
        haveStatus_.addBaseHp(hp);
        if (getHp() == 0) {
            if (haveEquipment_.isEquipment(0x9c)) {
                setMeganteRing(true);
                setInvokeMeganteRing(true);
            }
            if (haveItem_.isItem(0xb8)) {
                setInvokeRebirthStone(true);
            }
            setDeathFlag(true);
            if (isDeathLessly()) {
                haveStatus_.addBaseHp(1);
            }
        }
        execDeath();
    }
}

THUMB void status::HaveStatusInfo::execDeath()
{
    if (getHp() == 0) {
        statusChange_.release(dq5::level::ActionParam::ACTIONTYPE_NEMURI);
        statusChange_.release(dq5::level::ActionParam::ACTIONTYPE_KONRAN);
        statusChange_.release(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA);
        if (haveBattleStatus_ != 0) {
            haveBattleStatus_->changeMonsterReverse();
        }
    }
}

THUMB void status::HaveStatusInfo::setHpMax(unsigned short hp)
{
    haveStatus_.setHpMax(hp);
}

THUMB unsigned short status::HaveStatusInfo::getHpMax() const
{
    if (characterType_ == PLAYER) {
        return dss::clamp<unsigned short>(haveStatus_.getHpMax(), 0, 999);
    }
    return haveStatus_.getHpMax();
}

THUMB void status::HaveStatusInfo::addHpMax(unsigned short hp)
{
    haveStatus_.addHpMax(hp);
    if (characterType_ == PLAYER && haveStatus_.getHpMax() > 999) {
        haveStatus_.setHpMax(999);
    }
}

THUMB void status::HaveStatusInfo::setMp(unsigned short mp)
{
    if (noDamage_ == 0) {
        haveStatus_.setMp(mp);
    }
}

THUMB unsigned short status::HaveStatusInfo::getMp() const
{
    return haveStatus_.getMp();
}

THUMB void status::HaveStatusInfo::addMp(int mp)
{
    if (noDamage_ == 0) {
        haveStatus_.addBaseMp(mp);
    }
}

THUMB void status::HaveStatusInfo::setMpMax(unsigned short mp)
{
    haveStatus_.setMpMax(mp);
}

THUMB unsigned short status::HaveStatusInfo::getMpMax() const
{
    if (characterType_ == PLAYER) {
        return dss::clamp<unsigned short>(haveStatus_.getMpMax(), 0, 999);
    }
    return haveStatus_.getMpMax();
}

THUMB void status::HaveStatusInfo::clearHpInBattle()
{
    hp_[BeforeAction] = getHp();
    hp_[ExecuteAction] = getHp();
    hp_[ResultAction] = getHp();
    hp_[SpecialAction] = getHp();
}

THUMB void status::HaveStatusInfo::addHpInBattle(DiffStatus status, int hp)
{
    addHp(hp);
}

THUMB void status::HaveStatusInfo::clearMpInBattle()
{
    mp_[BeforeAction] = 0;
    mp_[ExecuteAction] = 0;
    mp_[ResultAction] = 0;
    mp_[SpecialAction] = 0;
    addMpInBattle(BeforeAction, 0);
    addMpInBattle(ExecuteAction, 0);
    addMpInBattle(ResultAction, 0);
    addMpInBattle(SpecialAction, 0);
}

THUMB void status::HaveStatusInfo::addMpInBattle(DiffStatus status, int mp)
{
    addMp(mp);
}

THUMB void status::HaveStatusInfo::clearStatusChangeInBattle()
{
    status_[BeforeAction].clear();
    status_[ExecuteAction].clear();
    status_[ResultAction].clear();
    status_[SpecialAction].clear();
    setStatusChangeInBattle(BeforeAction);
    setStatusChangeInBattle(ExecuteAction);
    setStatusChangeInBattle(ResultAction);
    setStatusChangeInBattle(SpecialAction);
}

THUMB void status::HaveStatusInfo::setStatusChangeInBattle(DiffStatus status)
{
    status_[status].remove(1 << Manusa);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MANUSA)) {
        status_[status].set(1 << Manusa);
    }
    status_[status].remove(1 << Mahoton);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
        status_[status].set(1 << Mahoton);
    }
    status_[status].remove(1 << Sleep);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        status_[status].set(1 << Sleep);
    }
    status_[status].remove(1 << Confusion);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        status_[status].set(1 << Confusion);
    }
    status_[status].remove(1 << Spazz);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        status_[status].set(1 << Spazz);
    }
    status_[status].remove(1 << 5);
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
        status_[status].set(1 << 5);
    }
}

THUMB unsigned short status::HaveStatusInfo::getAttack(int effect)
{
    if (effect & 1) {
        return haveStatus_.getStrength();
    }
    unsigned short attack;
    if (haveEquipment_.isEquipment(0x42)) {
        attack = 0x45;
    } else {
        haveEquipment_.calcEffect();
        attack = getAttackChange() + (getStrength(0) + haveEquipment_.getAttack());
    }
    return dss::clamp<unsigned short>(attack, 0, 9999);
}

THUMB unsigned short status::HaveStatusInfo::getBaseAttack()
{
    unsigned short attack;
    if (haveEquipment_.isEquipment(0x42)) {
        attack = 0x45;
    } else {
        haveEquipment_.calcEffect();
        attack = getStrength(0) + haveEquipment_.getAttack();
    }
    return dss::clamp<unsigned short>(attack, 0, 9999);
}

THUMB short status::HaveStatusInfo::setAttackChange()
{
    short value = getBaseAttack();
    if (getAttack(0) == 9999) {
        value = 0;
    } else if (value + getAttack(0) > 9999) {
        value = 9999 - getAttack(0);
    }
    if (attackChange_ == 0) {
        attackChange_ += value;
    }
    return value;
}

THUMB short status::HaveStatusInfo::getAttackChange()
{
    return 0;
}

THUMB unsigned short status::HaveStatusInfo::getBaseDefence()
{
    haveEquipment_.calcEffect();
    short defence = getProtection(0) + haveEquipment_.getDefence();
    if (haveEquipment_.isEquipment(0x17)) {
        defence = 0;
    }
    if (haveEquipment_.isEquipment(0x75)) {
        defence = 0;
    }
    if (haveEquipment_.isEquipment(0x42)) {
        defence = 0x36;
    }
    return dss::clamp<short>(defence, 0, 9999);
}

THUMB unsigned short status::HaveStatusInfo::getDefence(int effect)
{
    if (effect & 1) {
        return haveStatus_.getProtection();
    }
    short defence;
    if (haveEquipment_.isEquipment(0x17)) {
        defence = 0;
    } else if (haveEquipment_.isEquipment(0x75)) {
        defence = 0;
    } else if (haveEquipment_.isEquipment(0x42)) {
        defence = 0x36;
    } else {
        haveEquipment_.calcEffect();
        defence = getDefenceChange() + (getProtection(0) + haveEquipment_.getDefence());
    }
    return dss::clamp<short>(defence, 0, 9999);
}

THUMB short status::HaveStatusInfo::setDefenceChange(int actionIndex)
{
    short value = 0;
    short baseDefence = getBaseDefence();
    switch (actionIndex) {
    case 0x26:
        value = -baseDefence;
        break;
    case 0x27:
    case 0x28:
        value = -baseDefence / 2;
        break;
    case 0x29:
    case 0xe6:
        value = baseDefence * 4 / 10;
        break;
    case 0x2a:
    case 0x2b:
        value = baseDefence;
        break;
    case 0x2c:
        if (characterType_ == PLAYER) {
            value = baseDefence * 2 / 10;
        }
        if (characterType_ == MONSTER) {
            value = baseDefence * 5 / 10;
        }
        break;
    }
    if (value > 0) {
        if (getDefence(0) == baseDefence * 2) {
            value = 0;
        }
        if (getDefence(0) == 0x1ff) {
            value = 0;
        }
        if (value + getDefence(0) > baseDefence * 2) {
            value = baseDefence * 2 - getDefence(0);
        }
        if (value + getDefence(0) > 0x1ff) {
            value = 0x1ff - getDefence(0);
        }
    }
    if (value < 0) {
        if (getDefence(0) == 0) {
            value = 0;
        } else if (value + getDefence(0) < 0) {
            value = -getDefence(0);
        }
    }
    defenceChange_ += value;
    return value;
}

THUMB short status::HaveStatusInfo::getDefenceChange()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA)) {
        return defenceChange_;
    }
    return 0;
}

THUMB void status::HaveStatusInfo::clearDefenceChange()
{
    defenceChange_ = 0;
}

THUMB unsigned char status::HaveStatusInfo::getChangeStrength(int itemIndex) const
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    changeHaveEquipment.calcEffect();
    unsigned int strength = haveStatus_.getStrength() + changeHaveEquipment.getStrength();
    strength = dss::clamp<unsigned short>(strength, 0, 0xff);
    return strength;
}

THUMB unsigned char status::HaveStatusInfo::getChangeAgility(int itemIndex)
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    unsigned short agility;
    if (itemIndex == 0x9b) {
        agility = getAgility(0) * 2;
    } else {
        agility = getAgility(0);
    }
    if (itemIndex == 0x71) {
        agility = 0;
    }
    if (itemIndex == 0x42) {
        agility = 0x2b;
    }
    agility = dss::clamp<unsigned short>(agility, 0, 0xff);
    return agility;
}

THUMB unsigned char status::HaveStatusInfo::getChangeWisdom(int itemIndex) const
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    unsigned short wisdom;
    if (haveEquipment_.isEquipment(0x94)) {
        changeHaveEquipment.calcEffect();
        wisdom = haveStatus_.getWisdom() + changeHaveEquipment.getWisdom() + 15;
    } else {
        changeHaveEquipment.calcEffect();
        wisdom = haveStatus_.getWisdom() + changeHaveEquipment.getWisdom();
    }
    wisdom = dss::clamp<unsigned short>(wisdom, 0, 0xff);
    return wisdom;
}

THUMB unsigned char status::HaveStatusInfo::getChangeLuck(int itemIndex) const
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    changeHaveEquipment.calcEffect();
    unsigned short luck = haveStatus_.getLuck() + changeHaveEquipment.getLuck();
    luck = dss::clamp<unsigned short>(luck, 0, 0xff);
    return luck;
}

THUMB short status::HaveStatusInfo::getChangeAttack(int itemIndex) const
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    int attack;
    if (itemIndex == 0x42) {
        attack = 0x45;
    } else {
        changeHaveEquipment.calcEffect();
        attack = haveStatus_.getStrength() + changeHaveEquipment.getAttack();
    }
    attack = dss::clamp<int>(attack, 0, 9999);
    return attack;
}

THUMB short status::HaveStatusInfo::getChangeDefence(int itemIndex) const
{
    HaveEquipment changeHaveEquipment = haveEquipment_;
    changeHaveEquipment.calcEquipment(itemIndex);
    changeHaveEquipment.calcEffect();
    int defence = haveStatus_.getProtection() + changeHaveEquipment.getDefence();
    if (itemIndex == 0x17) {
        defence = 0;
    }
    if (itemIndex == 0x75) {
        defence = 0;
    }
    if (itemIndex == 0x42) {
        defence = 0x36;
    }
    defence = dss::clamp<int>(defence, 0, 9999);
    return defence;
}

THUMB bool status::HaveStatusInfo::isNearDeath() const
{
    if (getHp() == 0) {
        return false;
    }
    if (getHp() <= getHpMax() / 4 - 1) {
        return true;
    }
    return false;
}

THUMB bool status::HaveStatusInfo::isDeath() const
{
    if (getHp() == 0) {
        return true;
    }
    return false;
}

THUMB void status::HaveStatusInfo::setDeath()
{
    setHp(0);
}

THUMB void status::HaveStatusInfo::rebirth()
{
    setHp(getHpMax());
}

THUMB bool status::HaveStatusInfo::isPoison()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
        return true;
    }
    return false;
}

THUMB void status::HaveStatusInfo::setPoison()
{
    statusChange_.setup(dq5::level::ActionParam::ACTIONTYPE_DOKU, false);
}

THUMB void status::HaveStatusInfo::detoxPoison()
{
    if (isPoison()) {
        statusChange_.release(dq5::level::ActionParam::ACTIONTYPE_DOKU);
    }
}

THUMB bool status::HaveStatusInfo::isSpell()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE1)) {
        return true;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE2)) {
        return true;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE3)) {
        return true;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE4)) {
        return true;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE5)) {
        return true;
    }
    return false;
}

THUMB void status::HaveStatusInfo::breakSpell()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE1)) {
        statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_CURSE1);
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE2)) {
        statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_CURSE2);
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE3)) {
        statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_CURSE3);
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE4)) {
        statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_CURSE4);
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE5)) {
        statusChange_.cleanup(dq5::level::ActionParam::ACTIONTYPE_CURSE5);
    }
}

THUMB void status::HaveStatusInfo::setEquipment(int index)
{
    if (allEquipment_ == 0 && haveItem_.isEquipment(index)) {
        return;
    }
    switch (UseItem::getEquipItemType(haveItem_.getItem(index))) {
    case ITEM_WEAPON:
        haveItem_.resetEquipmentWithItemIndex(haveItem_.getEquipmentItem(ITEM_WEAPON, 0));
        break;
    case ITEM_ARMOR:
        haveItem_.resetEquipmentWithItemIndex(haveItem_.getEquipmentItem(ITEM_ARMOR, 0));
        break;
    case ITEM_SHIELD:
        haveItem_.resetEquipmentWithItemIndex(haveItem_.getEquipmentItem(ITEM_SHIELD, 0));
        break;
    case ITEM_HELMET:
        haveItem_.resetEquipmentWithItemIndex(haveItem_.getEquipmentItem(ITEM_HELMET, 0));
        break;
    case ITEM_ACCESSORY:
        break;
    }
    haveItem_.setEquipment(index);
}

THUMB void status::HaveStatusInfo::resetEquipment(int index)
{
    haveEquipment_.resetEquipment(haveItem_.getItem(index));
    haveItem_.resetEquipment(index);
}

THUMB void status::HaveStatusInfo::resetEquipment(ItemType itemType)
{
    int itemIndex = haveEquipment_.getEquipment(itemType, 0);
    haveEquipment_.resetEquipment(itemIndex);
    haveItem_.resetEquipmentWithItemIndex(itemIndex);
}

THUMB void status::HaveStatusInfo::clearAllItem()
{
    haveItem_.clear();
    haveEquipment_.clear();
}

THUMB int status::HaveStatusInfo::setItemEquipment(int itemIndex)
{
    if (itemIndex == 0) {
        return -1;
    }
    int index = haveItem_.add(itemIndex);
    setEquipment(index);
    return index;
}

THUMB bool status::HaveStatusInfo::isEquipEnable(int itemIndex) const
{
    if (UseItem::isEquipEnable(haveStatus_.getEquipAttrIndex(), itemIndex, 0)) {
        return true;
    }
    return false;
}

THUMB void status::HaveStatusInfo::execThrow(int index)
{
    int itemIndex = 0;
    if (haveItem_.isEquipment(index)) {
        itemIndex = haveItem_.getItem(index);
    }
    haveItem_.del(index);
    haveEquipment_.resetEquipment(itemIndex);
}

THUMB void status::HaveStatusInfo::recovery()
{
    haveStatus_.setHp(haveStatus_.getHpMax());
    haveStatus_.setMp(haveStatus_.getMpMax());
    statusChange_.clear();
}

THUMB void status::HaveStatusInfo::revival()
{
    haveStatus_.setHp(haveStatus_.getHpMax());
    haveStatus_.setMp(haveStatus_.getMpMax());
}

THUMB void status::HaveStatusInfo::setUseActionEffectValue(int value)
{
    effectValue_ = value;
    if (isDamage()) {
        if (effectValueMax_ < effectValue_) {
            effectValueMax_ = effectValue_;
        }
        if (effectValueMin_ > effectValue_) {
            effectValueMin_ = effectValue_;
        }
        effectValueCount_++;
    }
}

THUMB void status::HaveStatusInfo::setSpecialTargetDamage(int value)
{
    specialTargetDamage_ = value;
}

THUMB int status::HaveStatusInfo::getSpecialTargetDamage()
{
    return specialTargetDamage_;
}

THUMB void status::HaveStatusInfo::addSpecialTargetCount()
{
    specialTargetCount_++;
}

THUMB int status::HaveStatusInfo::getSpecialTargetCount()
{
    return specialTargetCount_;
}

#define FLAG_SET_ONLY(func, field, bit) \
    THUMB void status::HaveStatusInfo::func(bool flag) \
    { \
        if (flag) { \
            field.set(bit); \
        } \
    }

#define FLAG_SET(func, field, bit) \
    THUMB void status::HaveStatusInfo::func(bool flag) \
    { \
        if (flag) { \
            field.set(bit); \
        } else { \
            field.remove(bit); \
        } \
    }

#define FLAG_IS(func, field, bit) \
    THUMB bool status::HaveStatusInfo::func() \
    { \
        return field.check(bit); \
    }

FLAG_SET_ONLY(setFubahaFlag, flag_, FLAG_FUBAHA)
FLAG_IS(isFubahaFlag, flag_, FLAG_FUBAHA)
FLAG_SET(setDisappearFlag, flag_, FLAG_DISAPPEAR)
FLAG_IS(isDisappearFlag, flag_, FLAG_DISAPPEAR)
FLAG_SET(setRebirthFailed, flag_, FLAG_REBIRTH_FAILED)
FLAG_IS(isRebirthFailed, flag_, FLAG_REBIRTH_FAILED)
FLAG_SET(setMosyasRelease, flag_, FLAG_MOSYAS_RELEASE)
FLAG_IS(isMosyasRelease, flag_, FLAG_MOSYAS_RELEASE)
FLAG_SET(setActionDisable, flag_, FLAG_ACTION_DISABLE)
FLAG_IS(getActionDisable, flag_, FLAG_ACTION_DISABLE)
FLAG_SET(setSleepAttack, flag_, FLAG_SLEEP_ATTACK)
FLAG_IS(isSleepAttack, flag_, FLAG_SLEEP_ATTACK)
FLAG_SET(setMultiAttack, flag_, FLAG_MULTI_ATTACK)
FLAG_IS(isMultiAttack, flag_, FLAG_MULTI_ATTACK)
FLAG_SET(setCallFriend, flag_, FLAG_CALL_FRIEND)
FLAG_IS(isCallFriend, flag_, FLAG_CALL_FRIEND)
FLAG_SET(setWeaponAddDamage, flag_, FLAG_WEAPON_ADD_DAMAGE)
FLAG_IS(isWeaponAddDamage, flag_, FLAG_WEAPON_ADD_DAMAGE)
FLAG_SET(setConfuseMissAttack, flag_, FLAG_CONFUSE_MISS_ATTACK)
FLAG_IS(isConfuseMissAttack, flag_, FLAG_CONFUSE_MISS_ATTACK)
FLAG_SET(setAddEffectSleep, flag_, FLAG_ADD_EFFECT_SLEEP)
FLAG_SET(setAddEffectSpazz, flag_, FLAG_ADD_EFFECT_SPAZZ)
FLAG_SET(setAddEffectPoison, flag_, FLAG_ADD_EFFECT_POISON)
FLAG_SET(setAddEffectRecovery, flag_, FLAG_ADD_EFFECT_RECOVERY)
FLAG_IS(isAddEffectRecovery, flag_, FLAG_ADD_EFFECT_RECOVERY)
FLAG_SET(setAddEffectMahotora, flag_, FLAG_ADD_EFFECT_MAHOTORA)
FLAG_IS(isAddEffectMahotora, flag_, FLAG_ADD_EFFECT_MAHOTORA)
FLAG_SET(setAddEffectDamage, flag_, FLAG_ADD_EFFECT_DAMAGE)
FLAG_IS(isAddEffectDamage, flag_, FLAG_ADD_EFFECT_DAMAGE)
FLAG_SET(setTargetJouk, flag_, FLAG_TARGET_JOUK)
FLAG_IS(isTargetJouk, flag_, FLAG_TARGET_JOUK)
FLAG_SET(setTargetJoukForTest, testFlag_, FLAG_TEST_TARGET_JOUK)
FLAG_SET(setKillMyself, flag_, FLAG_KILL_MYSELF)
FLAG_IS(isKillMyself, flag_, FLAG_KILL_MYSELF)
FLAG_SET(setMonsterChange, flag_, FLAG_MONSTER_CHANGE)
FLAG_IS(isMonsterChange, flag_, FLAG_MONSTER_CHANGE)
FLAG_SET(setBaikirutoDisable, flag_, FLAG_BAIKIRUTO_DISABLE)
FLAG_SET(setFirstMosyas, flag_, FLAG_FIRST_MOSYAS)
FLAG_IS(isFirstMosyas, flag_, FLAG_FIRST_MOSYAS)
FLAG_SET(setMahokantaCounter, flag_, FLAG_MAHOKANTA_COUNTER)
FLAG_IS(isMahokantaCounter, flag_, FLAG_MAHOKANTA_COUNTER)
FLAG_SET(setCounterDamage, flag_, FLAG_COUNTER_DAMAGE)
FLAG_SET(setDamage, flag_, FLAG_DAMAGE)
FLAG_IS(isDamage, flag_, FLAG_DAMAGE)
FLAG_SET(setLastActor, flag_, FLAG_LAST_ACTOR)
FLAG_SET(setAddMahotoraExecute, flag_, FLAG_ADD_MAHOTORA_EXECUTE)
FLAG_IS(isAddMahotoraExecute, flag_, FLAG_ADD_MAHOTORA_EXECUTE)
FLAG_SET(setDamageMyself, flag_, FLAG_DAMAGE_MYSELF)
FLAG_IS(isDamageMyself, flag_, FLAG_DAMAGE_MYSELF)
FLAG_SET(setSelfImmolation, flag2_, FLAG_SELF_IMMOLATION)
FLAG_IS(isSelfImmolation, flag2_, FLAG_SELF_IMMOLATION)
FLAG_SET(setFirstKaishin, flag2_, FLAG_FIRST_KAISHIN)
FLAG_SET(setSecondKaishin, flag2_, FLAG_SECOND_KAISHIN)
FLAG_IS(isSecondKaishin, flag2_, FLAG_SECOND_KAISHIN)
FLAG_SET(setStatusChangeRelease, flag2_, FLAG_STATUS_CHANGE_RELEASE)
FLAG_IS(isStatusChangeRelease, flag2_, FLAG_STATUS_CHANGE_RELEASE)
FLAG_SET(setAstoron, flag2_, FLAG_ASTORON)
FLAG_IS(isAstoron, flag2_, FLAG_ASTORON)
FLAG_SET(setMpFailure, flag2_, FLAG_MP_FAILURE)
FLAG_IS(isMpFailure, flag2_, FLAG_MP_FAILURE)
FLAG_SET(setMahotoneFailure, flag2_, FLAG_MAHOTONE_FAILURE)
FLAG_SET(setMegazaruRebirth, flag2_, FLAG_MEGAZARU_REBIRTH)
FLAG_IS(isMegazaruRebirth, flag2_, FLAG_MEGAZARU_REBIRTH)
FLAG_SET(setMegazaruRecovery, flag2_, FLAG_MEGAZARU_RECOVERY)
FLAG_SET(setZaorikuRebirth, flag2_, FLAG_ZAORIKU_REBIRTH)
FLAG_SET(setImmidiateDeath, flag2_, FLAG_IMMIDIATE_DEATH)
FLAG_IS(isImmidiateDeath, flag2_, FLAG_IMMIDIATE_DEATH)
FLAG_SET(setExecuteMeganteRing, flag2_, FLAG_EXECUTE_MEGANTE_RING)
FLAG_IS(isExecuteMeganteRing, flag2_, FLAG_EXECUTE_MEGANTE_RING)
FLAG_SET(setVenomAction, flag2_, FLAG_VENOM_ACTION)
FLAG_SET(setDisableTextureCache, flag2_, FLAG_DISABLE_TEXTURE_CACHE)
FLAG_IS(isDisableTextureCache, flag2_, FLAG_DISABLE_TEXTURE_CACHE)
FLAG_IS(isSplit, flag2_, FLAG_SPLIT)
FLAG_IS(isJouk, flag2_, FLAG_JOUK)
FLAG_SET(setKaishin, flag2_, FLAG_KAISHIN)
FLAG_IS(isKaishin, flag2_, FLAG_KAISHIN)
FLAG_SET(setTsukon1, flag2_, FLAG_TSUKON1)
FLAG_IS(isTsukon1, flag2_, FLAG_TSUKON1)
FLAG_SET(setTsukon2, flag2_, FLAG_TSUKON2)
FLAG_IS(isTsukon2, flag2_, FLAG_TSUKON2)
FLAG_SET(setMiss, flag2_, FLAG_MISS)
FLAG_IS(isMiss, flag2_, FLAG_MISS)
FLAG_SET(setSleepTurn, flag2_, FLAG_SLEEP_TURN)
FLAG_IS(isSleepTurn, flag2_, FLAG_SLEEP_TURN)
FLAG_SET(setCurse2, flag2_, FLAG_CURSE2_TARGET_SELECT)
FLAG_IS(isCurse2, flag2_, FLAG_CURSE2_TARGET_SELECT)
FLAG_SET(setLifeStoneEnable, flag2_, FLAG_LIFE_STONE_ENABLE)
FLAG_IS(isLifeStoneEnable, flag2_, FLAG_LIFE_STONE_ENABLE)
FLAG_SET(setManusaAlready, flag2_, FLAG_MANUSA_ALREADY)
FLAG_IS(isManusaAlready, flag2_, FLAG_MANUSA_ALREADY)
FLAG_SET(setCurse1, flag2_, FLAG_CURSE1)
FLAG_IS(isCurse1, flag2_, FLAG_CURSE1)
FLAG_SET(setDeathFlag, flag2_, FLAG_DEATH)
FLAG_IS(isDeathFlag, flag2_, FLAG_DEATH)
FLAG_SET(setImmediateDeathItem, flag2_, FLAG_IMMEDIATE_DEATH_ITEM)
FLAG_IS(isImmediateDeathItem, flag2_, FLAG_IMMEDIATE_DEATH_ITEM)
FLAG_SET(setCommandRandom, flag_, FLAG_COMMAND_RANDOM)
FLAG_IS(isCommandRandom, flag_, FLAG_COMMAND_RANDOM)
FLAG_SET(setZaoraruFailed, flag_, FLAG_ZAORARU_FAILED)
FLAG_SET(setMagicDisable, flag2_, FLAG_MAGIC_DISABLE)
FLAG_IS(isMagicDisable, flag2_, FLAG_MAGIC_DISABLE)
FLAG_SET(setMosyasStart, flag2_, FLAG_MOSYAS_START)
FLAG_IS(isMosyasStart, flag2_, FLAG_MOSYAS_START)
FLAG_SET(setAllKaishin, battleFlag_, FLAG_ALL_KAISHIN)
FLAG_IS(isAllKaishin, battleFlag_, FLAG_ALL_KAISHIN)
FLAG_SET(setCloseDoor, battleFlag_, FLAG_CLOSE_DOOR)
FLAG_IS(isCloseDoor, battleFlag_, FLAG_CLOSE_DOOR)
FLAG_SET(setMosyasTarget, battleFlag_, FLAG_MOSYAS_TARGET)
FLAG_IS(isMosyasTarget, battleFlag_, FLAG_MOSYAS_TARGET)
FLAG_SET(setDeathLessly, battleFlag_, FLAG_DEATH_LESSLY)
FLAG_IS(isDeathLessly, battleFlag_, FLAG_DEATH_LESSLY)
FLAG_SET(setMosyasExec, battleFlag_, FLAG_MOSYAS_EXEC)
FLAG_IS(isMosyasExec, battleFlag_, FLAG_MOSYAS_EXEC)
FLAG_SET(setInvokeMeganteRing, battleFlag_, FLAG_INVOKE_MEGANTE_RING)
FLAG_SET(setInvokeRebirthStone, battleFlag_, FLAG_INVOKE_REBRTH_STONE)
FLAG_IS(isInvokeRebirthStone, battleFlag_, FLAG_INVOKE_REBRTH_STONE)
FLAG_SET(setRebirthForRebirthStone, battleFlag_, FLAG_REBIRTH_FOR_REBIRTH_STONE)
FLAG_IS(isRebirthForRebirthStone, battleFlag_, FLAG_REBIRTH_FOR_REBIRTH_STONE)
FLAG_SET(setEscapeFlag, battleFlag_, FLAG_ESCAPE)
FLAG_IS(isEscapeFlag, battleFlag_, FLAG_ESCAPE)
FLAG_SET(setMeganteRing, battleFlag_, FLAG_MEGANTE_RING)
FLAG_IS(isMeganteRing, battleFlag_, FLAG_MEGANTE_RING)

THUMB void status::HaveStatusInfo::setGlbMeganteRing(bool flag)
{
    if (flag) {
        globalFlag_.set(FLAG_GLB_MEGANTE_RING);
    } else {
        globalFlag_.remove(FLAG_GLB_MEGANTE_RING);
    }
}

THUMB bool status::HaveStatusInfo::isGlbMeganteRing()
{
    return globalFlag_.check(FLAG_GLB_MEGANTE_RING);
}

THUMB void status::HaveStatusInfo::setGlbRebirthStone(bool flag)
{
    if (flag) {
        globalFlag_.set(FLAG_GLB_REBIRTH_STONE);
    } else {
        globalFlag_.remove(FLAG_GLB_REBIRTH_STONE);
    }
}

THUMB bool status::HaveStatusInfo::isGlbRebirthStone()
{
    return globalFlag_.check(FLAG_GLB_REBIRTH_STONE);
}

THUMB void status::HaveStatusInfo::setDrawCtrlId(int ctrl)
{
    if (ctrl == -1) {
        haveStatus_.getHp();
    }
    drawCtrlId_ = ctrl;
}

THUMB void status::HaveStatusInfo::releaseMosyas()
{
    int hp = getHp();
    int mp = getMp();
    haveStatus_.setup(index_, false);
    setHp(hp);
    setMp(mp);
}

THUMB void status::HaveStatusInfo::execStartOfBattle()
{
    allFlagClear();
    clearHpInBattle();
    clearMpInBattle();
    clearStatusChangeInBattle();
    battleFlag_.clear();
    globalFlag_.clear();
    specialTargetCount_ = 0;
    effectValueMax_ = 0;
    effectValueMin_ = 0;
    effectValueCount_ = 0;
}

THUMB bool status::HaveStatusInfo::isActionEnable()
{
    if (isDeath()) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM)) {
        return false;
    }
    return true;
}

THUMB bool status::HaveStatusInfo::isActionEnableWithoutDragoram()
{
    if (isDeath()) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    return true;
}

THUMB bool status::HaveStatusInfo::isActionEnableForMacro()
{
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    return true;
}

THUMB bool status::HaveStatusInfo::isAttackEnable()
{
    if (isDeath()) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        return false;
    }
    if (statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    return true;
}

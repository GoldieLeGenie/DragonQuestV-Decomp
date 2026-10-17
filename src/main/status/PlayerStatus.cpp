#pragma ipa file
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageAttribute.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline bool status::CharacterStatus::isDeathDisable()
{
    return false;
}

inline void status::CharacterStatus::setMosyasRelease()
{
}

inline void status::CharacterStatus::setMosyasChange(int monsterIndex)
{
}

inline void status::CharacterStatus::setMosyasChange(CharacterStatus* target)
{
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus()
{
    return haveBattleStatus_;
}

inline void status::CharacterStatus::setArrayIndex(int index)
{
    arrayIndex_ = index;
}

inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline int status::HaveStatus::getCommand() const
{
    return command_;
}

inline int status::HaveStatusInfo::getCommandType() const
{
    return haveStatus_.getCommand();
}

THUMB status::PlayerStatus::PlayerStatus()
{
    clearWalkDamage(true);
}

THUMB status::PlayerStatus::~PlayerStatus()
{
}

THUMB void status::PlayerStatus::setup(int index)
{
    index_ = index;
    if (index >= 16) {
        characterIndex_ = (index - 16) / 3 + 16;
    } else {
        characterIndex_ = index;
    }
    characterType_ = PLAYER;
    haveStatusInfo_.setup(index, true);
    haveStatusInfo_.haveBattleStatus_ = &haveBattleStatus_;
    haveBattleStatus_.setup(PLAYER, 0, characterIndex_);
    haveBattleStatus_.haveStatusInfo_ = &haveStatusInfo_;
    setArrayIndex(index);
}

THUMB void status::PlayerStatus::cleanup()
{
    haveStatusInfo_.cleanup();
}

THUMB void status::PlayerStatus::levelup(int level)
{
    if (haveStatusInfo_.getHaveStatus().isPlayer()) {
        haveStatusInfo_.levelup(level);
    }
}

THUMB void status::PlayerStatus::setBestCondition()
{
    haveStatusInfo_.getHaveStatus().addBaseHp(1000);
    haveStatusInfo_.getHaveStatus().addBaseMp(1000);
}

THUMB bool status::PlayerStatus::walkDamage(StageDamage damage)
{
    bool ret = false;
    if (getHaveStatusInfo().isDeath()) {
        return ret;
    }
    switch (damage) {
        case Barrier:
            if (!StageAttribute::isToramana()) {
                setWalkDamage(15);
                ret = true;
            }
            break;
        case Poison:
            if (!StageAttribute::isToramana()) {
                setWalkDamage(1);
                ret = true;
            }
            break;
        case Yogan:
            if (!StageAttribute::isToramana()) {
                setWalkDamage(1);
                ret = true;
            }
            break;
        case StageDamageNone:
            break;
    }
    return ret;
}

THUMB bool status::PlayerStatus::walkNormal()
{
    bool ret = false;
    walkCount_++;
    if (walkCount_ < WALK_COUNT) {
        return ret;
    }
    walkCount_ = 0;
    if (getHaveStatusInfo().isDeath()) {
        return ret;
    }
    if (g_StageAttribute.isEncount()) {
        if (setWalkEffectPoison()) {
            ret = true;
        }
        if (setWalkEffectVenom()) {
            ret = true;
        }
        setWalkEffectLuckHat();
        setWalkEffectLifeRing();
        if (setWalkEffectCurse4()) {
            ret = true;
        }
        if (setWalkEffectCurse5()) {
            ret = true;
        }
    }
    return ret;
}

THUMB void status::PlayerStatus::walkEnvioronment()
{
    if (walkCount_ == 0 && g_StageAttribute.isEncount()) {
        haveStatusInfo_.getStatusChange().execWalk();
    }
}

THUMB bool status::PlayerStatus::setWalkEffectPoison()
{
    bool ret = false;
    if (haveStatusInfo_.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
        if (walkCountPoison_ % 4 == 3) {
            setWalkDamage(1);
            ret = true;
        }
        walkCountPoison_++;
    }
    return ret;
}

THUMB bool status::PlayerStatus::setWalkEffectVenom()
{
    bool ret = false;
    if (haveStatusInfo_.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        if (walkCountVenom_ % 4 == 3) {
            int damage = haveStatusInfo_.getHaveStatus().getHpMax() / 6;
            if (damage == 0) {
                damage = 1;
            }
            setWalkDamage(damage);
            ret = true;
        }
        walkCountVenom_++;
    }
    return ret;
}

THUMB void status::PlayerStatus::setWalkEffectLuckHat()
{
    if (haveStatusInfo_.getHaveEquipment().isEquipment(0x93)) {
        if (walkCountLuckHat_ % 4 == 3) {
            haveStatusInfo_.addMp(1);
        }
        walkCountLuckHat_++;
    } else {
        walkCountLuckHat_ = 0;
    }
}

THUMB void status::PlayerStatus::setWalkEffectLifeRing()
{
    if (haveStatusInfo_.getHaveEquipment().isEquipment(0xa0)) {
        haveStatusInfo_.addHp(1);
        walkCountLifeRing_++;
    } else {
        walkCountLifeRing_ = 0;
    }
}

THUMB bool status::PlayerStatus::setWalkEffectCurse4()
{
    bool ret = false;
    if (haveStatusInfo_.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE4)) {
        if (walkCountCurse4_ % 4 == 3) {
            if (haveStatusInfo_.getHp() > 1) {
                haveStatusInfo_.addHp(-1);
                ret = true;
            }
        }
        walkCountCurse4_++;
    } else {
        walkCountCurse4_ = 0;
    }
    return ret;
}

THUMB bool status::PlayerStatus::setWalkEffectCurse5()
{
    bool ret = false;
    if (haveStatusInfo_.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE5)) {
        if (walkCountCurse5_ % 4 == 3) {
            haveStatusInfo_.addMp(-1);
            ret = true;
        }
        walkCountCurse5_++;
    } else {
        walkCountCurse5_ = 0;
    }
    return ret;
}

THUMB void status::PlayerStatus::clearWalkDamage(bool flag)
{
    walkCount_ = 0;
    walkCountBarrier_ = 0;
    if (flag) {
        walkCountPoison_ = 0;
        walkCountVenom_ = 0;
        walkCountLuckHat_ = 0;
        walkCountLifeRing_ = 0;
        walkCountCurse4_ = 0;
        walkCountCurse5_ = 0;
    }
}

THUMB void status::PlayerStatus::setWalkDamage(int dmg)
{
    int hp = haveStatusInfo_.getHp();
    if (hp - dmg >= 1) {
        haveStatusInfo_.addHp(-dmg);
    } else {
        haveStatusInfo_.addHp(-(hp - 1));
    }
}

THUMB void status::PlayerStatus::execStartOfRound()
{
    if (haveStatusInfo_.getCommandType() != 5) {
        haveBattleStatus_.setSelectCommand(HaveBattleStatus::AISelect, 0);
    }
}

THUMB void status::PlayerStatus::execOfRound()
{
    haveStatusInfo_.getStatusChange().execStartOfTurn();
    haveStatusInfo_.getStatusChange().execEndOfTurn();
    if (haveStatusInfo_.getStatusChange().isRelease(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM)) {
        getHaveBattleStatus().changeMonsterReverse();
    }
    if (haveStatusInfo_.getStatusChange().isRelease()) {
        haveStatusInfo_.getStatusChange().getReleaseMessage();
    }
    haveStatusInfo_.getStatusChange().execEndOfRound();
}

THUMB void status::PlayerStatus::print()
{
}

THUMB void status::PlayerStatus::printAction()
{
}

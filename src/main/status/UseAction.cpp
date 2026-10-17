#pragma ipa file
#include "main/status/UseAction.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned long dq5::level::ActionParam::getMenuMes()
{
    return menuMes;
}

inline unsigned short dq5::level::ActionParam::getMonsterMin()
{
    return MonsterMin;
}

inline unsigned short dq5::level::ActionParam::getMonsterMax()
{
    return MonsterMax;
}

inline unsigned short dq5::level::ActionParam::getPlayerMin()
{
    return PlayerMin;
}

inline unsigned short dq5::level::ActionParam::getPlayerMax()
{
    return PlayerMax;
}

inline unsigned char dq5::level::ActionParam::getType()
{
    return type;
}

inline unsigned char dq5::level::ActionParam::getMagictype2()
{
    return magictype2;
}

inline unsigned char dq5::level::ActionParam::getUseMP()
{
    return useMP;
}

inline unsigned char dq5::level::ActionParam::getTypeID()
{
    return typeID;
}

inline unsigned char dq5::level::ActionParam::getMagictype()
{
    return magictype;
}

inline char dq5::level::ActionParam::getYaiba()
{
    return byte_1 & 0x1;
}

inline char dq5::level::ActionParam::getFubaha()
{
    return (byte_1 & 0x2) >> 1;
}

inline char dq5::level::ActionParam::getManusa()
{
    return (byte_1 & 0x4) >> 2;
}

inline char dq5::level::ActionParam::getMikawasi()
{
    return (byte_1 & 0x10) >> 4;
}

inline char dq5::level::ActionParam::getTikaratame()
{
    return (byte_1 & 0x20) >> 5;
}

inline char dq5::level::ActionParam::getBaikiru()
{
    return (byte_1 & 0x40) >> 6;
}

inline char dq5::level::ActionParam::getKaisin()
{
    return (byte_1 & 0x80) >> 7;
}

inline char dq5::level::ActionParam::getSyuutyuu()
{
    return byte_2 & 0x1;
}

inline char dq5::level::ActionParam::getAstron()
{
    return (byte_2 & 0x2) >> 1;
}

inline char dq5::level::ActionParam::getMahokanta()
{
    return (byte_2 & 0x4) >> 2;
}

inline char dq5::level::ActionParam::getMohokite()
{
    return (byte_2 & 0x8) >> 3;
}

inline char dq5::level::ActionParam::getKaijo()
{
    return (byte_2 & 0x10) >> 4;
}

inline char dq5::level::ActionParam::getTokusyu()
{
    return (byte_2 & 0x40) >> 6;
}

inline char dq5::level::ActionParam::getMissA()
{
    return (byte_2 & 0x80) >> 7;
}

inline char dq5::level::ActionParam::getMuchi()
{
    return byte_3 & 0x1;
}

inline char dq5::level::ActionParam::getDMC()
{
    return (byte_3 & 0x2) >> 1;
}

inline char dq5::level::ActionParam::getSaseru()
{
    return (byte_3 & 0x8) >> 3;
}

inline char dq5::level::ActionParam::getFukusuu()
{
    return (byte_3 & 0x10) >> 4;
}

inline char dq5::level::ActionParam::getHP()
{
    return (byte_3 & 0x40) >> 6;
}

inline char dq5::level::ActionParam::getSeisi()
{
    return (byte_4 & 0x2) >> 1;
}

inline char dq5::level::ActionParam::getMahotoon()
{
    return (byte_4 & 0x10) >> 4;
}

inline char dq5::level::ActionParam::getBattleID()
{
    return (byte_4 & 0x20) >> 5;
}

inline char dq5::level::ActionParam::getNormalID()
{
    return (byte_4 & 0x80) >> 7;
}

inline char dq5::level::ActionParam::getDefencetype()
{
    return (byte_5 & 0x38) >> 3;
}

inline char dq5::level::ActionParam::getDirect()
{
    return byte_6 & 0x7;
}

inline char dq5::level::ActionParam::getRange()
{
    return (byte_6 & 0x38) >> 3;
}

inline char dq5::level::ActionParam::getAI()
{
    return byte_7 & 0xF;
}

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index)
{
    return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

dq5::level::ActionParam* actionParam2_;
status::UseActionParam* status::UseAction::useActionParam_;
int status::UseAction::effectValueMax_;


static void getRecord(int index)
{
    actionParam2_ = dq5::level::ActionParam::getRecord(index);
}

THUMB void status::UseAction::initialize()
{
}

THUMB dq5::level::ActionParam::DEFENCE status::UseAction::getActionDefenceKind(int actionIndex)
{
    getRecord(actionIndex);
    return (dq5::level::ActionParam::DEFENCE)actionParam2_->getMagictype();
}

THUMB dq5::level::ActionParam::DEFENCE status::UseAction::getActionDefenceKind2(int actionIndex)
{
    getRecord(actionIndex);
    return (dq5::level::ActionParam::DEFENCE)actionParam2_->getMagictype2();
}

THUMB dq5::level::ActionParam::DEFENCETYPE status::UseAction::getActionDefenceType(int actionIndex)
{
    getRecord(actionIndex);
    return (dq5::level::ActionParam::DEFENCETYPE)actionParam2_->getDefencetype();
}

THUMB bool status::UseAction::isUsuallyUse(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getNormalID() == 1) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isBattleUse(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getBattleID() == 1) {
        return true;
    }
    return false;
}

THUMB int status::UseAction::getUseMp(int actionIndex)
{
    getRecord(actionIndex);
    return actionParam2_->getUseMP();
}

THUMB int status::UseAction::getMenuMessage(int actionIndex)
{
    getRecord(actionIndex);
    return actionParam2_->getMenuMes();
}

THUMB int status::UseAction::getWordDBIndex(int actionIndex)
{
    getRecord(actionIndex);
    return actionIndex;
}

THUMB status::UseAction::UseType status::UseAction::getUseType(int actionIndex)
{
    getRecord(actionIndex);
    switch (actionParam2_->getDirect()) {
    case dq5::level::ActionParam::DIRECT_NONE:
        return None;
    case dq5::level::ActionParam::DIRECT_ME:
        return Myself;
    case dq5::level::ActionParam::DIRECT_FRIEND:
        return Friend;
    case dq5::level::ActionParam::DIRECT_ENEMY:
        return Enemy;
    case dq5::level::ActionParam::DIRECT_BOTH:
        return Both;
    }
    return None;
}

THUMB status::UseAction::UseArea status::UseAction::getUseArea(int actionIndex)
{
    getRecord(actionIndex);
    switch (actionParam2_->getRange()) {
    case 0:
        return Zero;
    case 1:
        return One;
    case 2:
        return Group;
    case 3:
        return All;
    case 4:
        return Horse;
    case 5:
        return UsuallyHorse;
    case 6:
        return BattleHorse;
    }
    return One;
}

THUMB int status::UseAction::getEffectValueToPlayer(int actionIndex)
{
    getRecord(actionIndex);
    int min = actionParam2_->getPlayerMin();
    int max = actionParam2_->getPlayerMax();
    if (effectValueMax_) {
        return max;
    }
    return min + UnkDssRand::rand(max - min + 1);
}

THUMB int status::UseAction::getEffectValueToMonster(int actionIndex)
{
    getRecord(actionIndex);
    int min = actionParam2_->getMonsterMin();
    int max = actionParam2_->getMonsterMax();
    if (effectValueMax_) {
        return max;
    }
    return min + UnkDssRand::rand(max - min + 1);
}

THUMB int status::UseAction::getEffectValueForAvarage(int actionIndex)
{
    getRecord(actionIndex);
    int min = actionParam2_->getPlayerMin();
    int max = actionParam2_->getPlayerMax();
    return (min + max) / 2;
}

THUMB int status::UseAction::getEffectValueToPlayerMin(int actionIndex)
{
    getRecord(actionIndex);
    return actionParam2_->getPlayerMin();
}

THUMB int status::UseAction::getEffectValueToMonsterMin(int actionIndex)
{
    getRecord(actionIndex);
    return actionParam2_->getMonsterMin();
}

THUMB status::UseAction::DamageType status::UseAction::getDamageType(int actionIndex)
{
    getRecord(actionIndex);
    switch (actionParam2_->getTypeID()) {
    case dq5::level::ActionParam::ACTIONTYPE_NONE:
        return DamageTypeNone;
    case dq5::level::ActionParam::ACTIONTYPE_DAMAGE:
        return DamageTypeDamage;
    case dq5::level::ActionParam::ACTIONTYPE_KAIFUKU:
        return DamageTypeRecovery;
    case dq5::level::ActionParam::ACTIONTYPE_SOKUSHI:
        return DamageTypeInstantDeath;
    case dq5::level::ActionParam::ACTIONTYPE_FUKKATSU:
        return DamageTypeRebirth;
    case dq5::level::ActionParam::ACTIONTYPE_MP_ADD:
        return DamageTypeAddMp;
    case dq5::level::ActionParam::ACTIONTYPE_MP_SUB:
        return DamageTypeSubMp;
    case dq5::level::ActionParam::ACTIONTYPE_ST_CLR:
        return DamageTypeStatusClear;
    case dq5::level::ActionParam::ACTIONTYPE_ASTORON:
        return DamageTypeAstoron;
    case dq5::level::ActionParam::ACTIONTYPE_MAHI:
        return DamageTypeSpazz;
    case dq5::level::ActionParam::ACTIONTYPE_NEMURI:
        return DamageTypeSleep;
    case dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO:
        return DamageTypeBaikiruto;
    case dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA:
        return DamageTypeMahokanta;
    case dq5::level::ActionParam::ACTIONTYPE_MAHOTON:
        return DamageTypeMahoton;
    case dq5::level::ActionParam::ACTIONTYPE_KONRAN:
        return DamageTypeConfusion;
    case dq5::level::ActionParam::ACTIONTYPE_DOKU:
        return DamageTypePoison;
    case dq5::level::ActionParam::ACTIONTYPE_DF_HENKA:
        return DamageTypeDefenceChange;
    case dq5::level::ActionParam::ACTIONTYPE_SPD_PLUS:
        return DamageTypeAgilityChange;
    case dq5::level::ActionParam::ACTIONTYPE_DORAGORAM:
        return DamageTypeDragoram;
    case dq5::level::ActionParam::ACTIONTYPE_MANUSA:
        return DamageTypeManusa;
    case dq5::level::ActionParam::ACTIONTYPE_FUBAHA:
        return DamageTypeFubaha;
    case dq5::level::ActionParam::ACTIONTYPE_DEFENCE:
        return DamageTypeDefence;
    case dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE:
        return DamageTypeFizzleZone;
    case dq5::level::ActionParam::ACTIONTYPE_MOSYASU:
        return DamageTypeMosyasu;
    case dq5::level::ActionParam::ACTIONTYPE_PATH_1:
        return DamageTypePath1;
    case dq5::level::ActionParam::ACTIONTYPE_TAMEKEI:
        return DamageTypePowerSave;
    case dq5::level::ActionParam::ACTIONTYPE_TIMESTOP:
        return DamageTypeTimeStop;
    case dq5::level::ActionParam::ACTIONTYPE_MOUDOKU:
    case dq5::level::ActionParam::ACTIONTYPE_MAHOKITE:
        return DamageTypeNone;
    }
    return DamageTypeNone;
}

THUMB bool status::UseAction::isYaibaArmor(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getYaiba()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isFubaha(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getFubaha()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isManusa(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getManusa()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isJouk(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMikawasi()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isPowerSave(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getTikaratame()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isBaikiruto(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getBaikiru()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isKaishin(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getKaisin()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isCrossFire(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getSyuutyuu()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isAstoron(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getAstron()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isMahokanta(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMahokanta()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isMahokite(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMohokite()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isReleaseConfusion(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getKaijo()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isErrorA(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMissA()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isErrorB(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMuchi()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isDamageC(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getDMC()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isForceE(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getSaseru()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isMultiF(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getFukusuu()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isAddHp(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getHP()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isMahoton(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getMahotoon()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isTargetDeadOrAlive(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getSeisi()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isSpecialSelectTarget(int actionIndex)
{
    getRecord(actionIndex);
    if (actionParam2_->getTokusyu()) {
        return true;
    }
    return false;
}

THUMB bool status::UseAction::isUse(int actionIndex, status::HaveStatusInfo& actorStatusInfo)
{
    if (getUseMp(actionIndex) <= actorStatusInfo.getMp()) {
        return true;
    }
    if (getUseMp(actionIndex) == 0xFF && actorStatusInfo.getMp() != 0) {
        return true;
    }
    return false;
}

THUMB status::UseAction::AIType status::UseAction::getAIType(int actionIndex)
{
    getRecord(actionIndex);
    switch (actionParam2_->getAI()) {
    case 1:
        return Attack;
    case 2:
        return Defence;
    case 3:
        return Assist;
    case 4:
        return Recovery;
    case 0:
        return Invalid;
    }
    return Attack;
}

THUMB status::UseAction::ActionType status::UseAction::getActionType(int actionIndex)
{
    getRecord(actionIndex);
    switch (actionParam2_->getType()) {
    case dq5::level::ActionParam::KIND_BATTLE_MAGIC:
    case dq5::level::ActionParam::KIND_NORMAL_MAGIC:
        return ActionTypeMagic;
    case dq5::level::ActionParam::KIND_BATTLE_SKILL:
    case dq5::level::ActionParam::KIND_NORMAL_SKILL:
        return ActionTypeSkill;
    }
    return ActionTypeNone;
}

THUMB void status::UseAction::execUse(status::UseActionParam& useActionParam)
{
    useActionParam_ = &useActionParam;
    if (HaveAction::isBattleMode()) {
        BaseAction::exec(useActionParam, true);
    } else {
        BaseAction::exec(useActionParam, false);
    }
}

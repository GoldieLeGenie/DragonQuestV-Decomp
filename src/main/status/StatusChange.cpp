#include "main/status/StatusChange.hpp"
#include "main/status/PlayerData.hpp"

inline int status::StatusChangeOne::getActionIndex()
{
    return actionIndex_;
}

inline void status::StatusChangeOne::setTurn(unsigned char turn)
{
    turn_ = turn;
}

inline int status::StatusChangeOne::getTurn()
{
    return turn_;
}

inline void status::StatusChangeOne::setEndRound()
{
    astron_ = 1;
}

inline void status::StatusChangeOne::setCount(int count)
{
    count_ = count;
}

inline int status::StatusChangeOne::getCount()
{
    return count_;
}

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index)
{
    return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::ActionParam::getTypeID()
{
    return typeID;
}

using namespace dq5::level;

status::StatusChangeOne status::StatusChange::statusFizzleZone_;
status::StatusChangeOne status::StatusChange::statusCloseDoor_;
status::StatusChangeOne status::StatusChange::statusToherosu_;
status::StatusChangeOne status::StatusChange::statusSinobiasi_;
status::StatusChangeOne status::StatusChange::statusMonstersFood_;
status::StatusChangeOne status::StatusChange::statusTimeStop_;
CharacterType status::StatusChange::characterTypeForTimeStop_ = MONSTER;

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

THUMB status::StatusChange::StatusChange()
{
}

THUMB status::StatusChange::~StatusChange()
{
}

THUMB status::StatusChangeOne& status::StatusChange::getStatusChangeOne(int rel)
{
    if (rel == ActionParam::ACTIONTYPE_FIZZLEZONE) {
        return statusFizzleZone_;
    }
    if (rel == ActionParam::ACTIONTYPE_CLOSEDOOR) {
        return statusCloseDoor_;
    }
    if (rel == ActionParam::ACTIONTYPE_TOHEROSU) {
        return statusToherosu_;
    }
    if (rel == ActionParam::ACTIONTYPE_SINOBIASI) {
        return statusSinobiasi_;
    }
    if (rel == ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA) {
        return statusMonstersFood_;
    }
    StatusChangeOne* one = getStatusChangeOneForOnlyOne(rel);
    if (one == NULL) {
        one = &status_[rel];
    }
    return *one;
}

THUMB status::StatusChangeOne* status::StatusChange::getStatusChangeOneForOnlyOne(int rel)
{
    if (rel == ActionParam::ACTIONTYPE_TIMESTOP) {
        return &statusTimeStop_;
    }
    return NULL;
}

THUMB void status::StatusChange::restore(int index)
{
    clear();
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    if (playerData.isCurse4()) {
        setup(ActionParam::ACTIONTYPE_CURSE4, false);
    }
    if (playerData.isCurse5()) {
        setup(ActionParam::ACTIONTYPE_CURSE5, false);
    }
    if (playerData.isPoison()) {
        setup(ActionParam::ACTIONTYPE_DOKU, false);
    }
    if (playerData.isVenom()) {
        setup(ActionParam::ACTIONTYPE_MOUDOKU, false);
    }
}

THUMB void status::StatusChange::store(int index)
{
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    if (isEnable(ActionParam::ACTIONTYPE_CURSE4)) {
        playerData.setCurse4(true);
    } else {
        playerData.setCurse4(false);
    }
    if (isEnable(ActionParam::ACTIONTYPE_CURSE5)) {
        playerData.setCurse5(true);
    } else {
        playerData.setCurse5(false);
    }
    if (isEnable(ActionParam::ACTIONTYPE_DOKU)) {
        playerData.setPoison(true);
    } else {
        playerData.setPoison(false);
    }
    if (isEnable(ActionParam::ACTIONTYPE_MOUDOKU)) {
        playerData.setVenom(true);
    } else {
        playerData.setVenom(false);
    }
}

THUMB bool status::StatusChange::setup(int actionIndex, bool flag)
{
    ActionParam* actionParam = ActionParam::getRecord(actionIndex);
    ActionParam::ACTIONTYPE type = (ActionParam::ACTIONTYPE)actionParam->getTypeID();
    if (!isValidBefore(type)) {
        return false;
    }
    getStatusChangeOne(type).setup(type, actionIndex, flag);
    if (type == ActionParam::ACTIONTYPE_PATH_1) {
        getStatusChangeOne(type).setTurn(1);
        if (actionIndex == 0x195) {
            getStatusChangeOne(type).setTurn(2);
        }
    }
    if (type == ActionParam::ACTIONTYPE_TAMEKEI) {
        getStatusChangeOne(type).setTurn(2);
    }
    if (type == ActionParam::ACTIONTYPE_ASTORON) {
        getStatusChangeOne(type).setEndRound();
    }
    if (type == ActionParam::ACTIONTYPE_TIMESTOP) {
        getStatusChangeOne(type).setEndRound();
    }
    checkValidAfter(type);
    return true;
}

THUMB void status::StatusChange::cleanup(ActionParam::ACTIONTYPE rel)
{
    getStatusChangeOne(rel).cleanup();
}

THUMB void status::StatusChange::setup(ActionParam::ACTIONTYPE re, bool flag)
{
    if (isValidBefore(re)) {
        getStatusChangeOne(re).setup(re, 0, flag);
        checkValidAfter(re);
    }
}

THUMB void status::StatusChange::clear()
{
    for (int i = 0; i < 51; i++) {
        if (i != ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA && i != ActionParam::ACTIONTYPE_SINOBIASI &&
            i != ActionParam::ACTIONTYPE_TOHEROSU && i != ActionParam::ACTIONTYPE_CLOSEDOOR &&
            i != ActionParam::ACTIONTYPE_FIZZLEZONE) {
            getStatusChangeOne(i).clear();
        }
    }
}

THUMB bool status::StatusChange::isValidBefore(int damageType)
{
    if (isEnable(ActionParam::ACTIONTYPE_ASTORON) && !StatusChangeOne::isValidOnAstron(damageType)) {
        return false;
    }
    if (isEnable(ActionParam::ACTIONTYPE_MAHI) && !StatusChangeOne::isValidOnSpazz(damageType)) {
        return false;
    }
    return true;
}

THUMB void status::StatusChange::checkValidAfter(int damageType)
{
    if (isEnable(ActionParam::ACTIONTYPE_NEMURI) && !StatusChangeOne::isAfterOnSleep(damageType)) {
        release(ActionParam::ACTIONTYPE_NEMURI);
    }
    if (isEnable(ActionParam::ACTIONTYPE_PATH_1) && !StatusChangeOne::isAfterOnPath1(damageType)) {
        release(ActionParam::ACTIONTYPE_PATH_1);
    }
    if (isEnable(ActionParam::ACTIONTYPE_KONRAN) && !StatusChangeOne::isAfterOnConfuze(damageType)) {
        release(ActionParam::ACTIONTYPE_KONRAN);
    }
    if (isEnable(ActionParam::ACTIONTYPE_TAMEKEI) && !StatusChangeOne::isAfterOnPowerSave(damageType)) {
        release(ActionParam::ACTIONTYPE_TAMEKEI);
    }
}

THUMB int status::StatusChange::isEnable(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).isEnable();
}

THUMB void status::StatusChange::setTurn(ActionParam::ACTIONTYPE status, unsigned char turn)
{
    getStatusChangeOne(status).setTurn(turn);
}

THUMB void status::StatusChange::setCount(ActionParam::ACTIONTYPE status, unsigned char count)
{
    getStatusChangeOne(status).setCount(count);
}

THUMB int status::StatusChange::getRestTurn(ActionParam::ACTIONTYPE status)
{
    return getStatusChangeOne(status).getTurn() - getStatusChangeOne(status).getCount();
}

THUMB void status::StatusChange::execStartOfTurn()
{
    for (int i = 0; i < 51; i++) {
        getStatusChangeOne(i).execStartOfTurn();
        if (getStatusChangeOne(i).isCancel()) {
            getStatusChangeOne(i).setEnable(false);
            getStatusChangeOne(i).setRelease(true);
        }
    }
}

THUMB void status::StatusChange::execEndOfTurn()
{
    for (int i = 0; i < 51; i++) {
        getStatusChangeOne(i).execEndOfTurn();
        if (getStatusChangeOne(i).isCancel()) {
            getStatusChangeOne(i).setEnable(false);
            getStatusChangeOne(i).setRelease(true);
        }
    }
}

THUMB void status::StatusChange::execEndOfRound()
{
    for (int i = 0; i < 51; i++) {
        if (getStatusChangeOneForOnlyOne(i) == NULL) {
            getStatusChangeOne(i).execEndOfRound();
            if (getStatusChangeOne(i).isCancel()) {
                getStatusChangeOne(i).setEnable(false);
                getStatusChangeOne(i).setRelease(true);
            }
        }
    }
}

THUMB void status::StatusChange::execEndOfRoundForAll()
{
    for (int i = 0; i < 51; i++) {
        if (getStatusChangeOneForOnlyOne(i) != NULL) {
            getStatusChangeOne(i).execEndOfRound();
            if (getStatusChangeOne(i).isCancel()) {
                getStatusChangeOne(i).setEnable(false);
            }
        }
    }
}

THUMB void status::StatusChange::execEndOfBattle()
{
    for (int i = 0; i < 51; i++) {
        if (i != ActionParam::ACTIONTYPE_DOKU && i != ActionParam::ACTIONTYPE_MOUDOKU &&
            i != ActionParam::ACTIONTYPE_CURSE4 && i != ActionParam::ACTIONTYPE_CURSE5 &&
            i != ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA && i != ActionParam::ACTIONTYPE_SINOBIASI &&
            i != ActionParam::ACTIONTYPE_TOHEROSU) {
            getStatusChangeOne(i).clear();
        }
    }
    statusFizzleZone_.clear();
    statusCloseDoor_.clear();
}

THUMB void status::StatusChange::execWalk()
{
    for (int i = 0; i < 51; i++) {
        getStatusChangeOne(i).execWalk();
        if (getStatusChangeOne(i).isCancel()) {
            getStatusChangeOne(i).setEnable(false);
            getStatusChangeOne(i).setRelease(true);
        }
    }
}

THUMB ActionParam::ACTIONTYPE status::StatusChange::isRelease()
{
    for (int i = 0; i < 51; i++) {
        if (getStatusChangeOne(i).isRelease()) {
            return (ActionParam::ACTIONTYPE)i;
        }
    }
    return ActionParam::ACTIONTYPE_NONE;
}

THUMB bool status::StatusChange::isRelease(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).isRelease() != false;
}

THUMB void status::StatusChange::release(ActionParam::ACTIONTYPE rel)
{
    getStatusChangeOne(rel).clear();
}

THUMB int status::StatusChange::getActionIndex(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getActionIndex();
}

THUMB int status::StatusChange::getExecMessage(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getExecMessage();
}

THUMB int status::StatusChange::getExecMessage2(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getExecMessage2();
}

THUMB int status::StatusChange::getResultMessage(ActionParam::ACTIONTYPE rel, CharacterType type)
{
    if (getStatusChangeOne(rel).isEnable()) {
        if (type == PLAYER) {
            return getStatusChangeOne(rel).getResultPlayerMessage();
        }
        if (type == MONSTER) {
            return getStatusChangeOne(rel).getResultMonsterMessage();
        }
    }
    return 0;
}

THUMB int status::StatusChange::getResultMessage2(ActionParam::ACTIONTYPE rel, CharacterType type)
{
    if (type == PLAYER) {
        return getStatusChangeOne(rel).getResultPlayerMessage();
    }
    if (type == MONSTER) {
        return getStatusChangeOne(rel).getResultMonsterMessage();
    }
    return 0;
}

THUMB int status::StatusChange::getAgainEnableMessage(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getAgainEnableMessage();
}

THUMB int status::StatusChange::getAgainDisableMessage(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getAgainDisableMessage();
}

THUMB int status::StatusChange::getReleaseMessage()
{
    for (int i = 0; i < 51; i++) {
        if (getStatusChangeOne(i).isRelease()) {
            getStatusChangeOne(i).setRelease(false);
            return getStatusChangeOne(i).getReleaseMessage();
        }
    }
    return 0;
}

THUMB int status::StatusChange::getReleaseMessage(ActionParam::ACTIONTYPE rel)
{
    return getStatusChangeOne(rel).getReleaseMessage();
}

THUMB void status::StatusChange::setToherosInfo(unsigned short info)
{
    if (info) {
        statusToherosu_.setup(ActionParam::ACTIONTYPE_TOHEROSU, info >> 7, true);
        statusToherosu_.setCount(info & 0x7f);
    }
}

THUMB unsigned short status::StatusChange::getToherosInfo()
{
    if (statusToherosu_.isEnable()) {
        return (statusToherosu_.getActionIndex() << 7) + statusToherosu_.getCount();
    }
    return 0;
}

THUMB void status::StatusChange::setSinobiasiInfo(unsigned short info)
{
    if (info) {
        statusSinobiasi_.setup(ActionParam::ACTIONTYPE_SINOBIASI, info >> 7, true);
        statusSinobiasi_.setCount(info & 0x7f);
    }
}

THUMB unsigned short status::StatusChange::getSinobiasiInfo()
{
    if (statusSinobiasi_.isEnable()) {
        return (statusSinobiasi_.getActionIndex() << 7) + statusSinobiasi_.getCount();
    }
    return 0;
}

THUMB void status::StatusChange::setMonstersFoodInfo(unsigned short info)
{
    if (info) {
        statusMonstersFood_.setup(ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA, info >> 7, true);
        statusMonstersFood_.setCount(info & 0x7f);
    }
}

THUMB unsigned short status::StatusChange::getMonstersFoodInfo()
{
    if (statusMonstersFood_.isEnable()) {
        return (statusMonstersFood_.getActionIndex() << 7) + statusMonstersFood_.getCount();
    }
    return 0;
}

THUMB void status::StatusChange::StaticClear()
{
    statusCloseDoor_.clear();
}

THUMB void status::StatusChange::printAll()
{
    print(ActionParam::ACTIONTYPE_BAIKIRUTO, "\x83\x6f\x83\x43\x83\x4c\x83\x8b\x83\x67");
    print(ActionParam::ACTIONTYPE_FUBAHA, "\x83\x74\x83\x6f\x81\x5b\x83\x6e");
    print(ActionParam::ACTIONTYPE_MAHOKANTA, "\x83\x7d\x83\x7a\x83\x4a\x83\x93\x83\x5e");
    print(ActionParam::ACTIONTYPE_MANUSA, "\x83\x7d\x83\x6b\x81\x5b\x83\x54");
    print(ActionParam::ACTIONTYPE_MAHOTON, "\x83\x7d\x83\x7a\x83\x67\x81\x5b\x83\x93");
    print(ActionParam::ACTIONTYPE_MAHOKITE, "\x83\x7d\x83\x7a\x83\x4c\x83\x65");
    print(ActionParam::ACTIONTYPE_ASTORON, "\x83\x41\x83\x58\x83\x67\x83\x8d\x83\x93");
    print(ActionParam::ACTIONTYPE_MOSYASU, "\x83\x82\x83\x56\x83\x83\x83\x58");
    print(ActionParam::ACTIONTYPE_SPD_PLUS, "\x91\x66\x91\x81\x82\xb3\x95\xcf\x89\xbb");
    print(ActionParam::ACTIONTYPE_DF_HENKA, "\x8e\xe7\x94\xf5\x97\xcd\x95\xcf\x89\xbb");
    print(ActionParam::ACTIONTYPE_DOKU, "\x93\xc5");
    print(ActionParam::ACTIONTYPE_MOUDOKU, "\x96\xd2\x93\xc5");
    print(ActionParam::ACTIONTYPE_NEMURI, "\x96\xb0\x82\xe8");
    print(ActionParam::ACTIONTYPE_MAHI, "\x96\x83\xe1\x83");
    print(ActionParam::ACTIONTYPE_DEFENCE, "\x96\x68\x8c\xe4");
    print(ActionParam::ACTIONTYPE_PATH_1, "\x8b\x78\x82\xdd");
    print(ActionParam::ACTIONTYPE_TAMEKEI, "\x97\xad\x82\xdf");
    print(ActionParam::ACTIONTYPE_KONRAN, "\x8d\xac\x97\x90");
    print(ActionParam::ACTIONTYPE_DORAGORAM, "\x83\x68\x83\x89\x83\x53\x83\x89\x83\x80");
    print(ActionParam::ACTIONTYPE_TIMESTOP, "\x83\x5e\x83\x43\x83\x80\x83\x58\x83\x67\x83\x62\x83\x76");
    print(ActionParam::ACTIONTYPE_BUKIMINAHIKARI, "\x82\xd4\x82\xab\x82\xdd\x82\xc8\x8c\xf5");
    print(ActionParam::ACTIONTYPE_FIZZLEZONE, "\x83\x74\x83\x42\x83\x59\x83\x8b\x83\x5d\x81\x5b\x83\x93");
    print(ActionParam::ACTIONTYPE_CURSE1, "\x8e\xf4\x82\xa2\x82\x50");
    print(ActionParam::ACTIONTYPE_CURSE2, "\x8e\xf4\x82\xa2\x82\x51");
    print(ActionParam::ACTIONTYPE_CURSE3, "\x8e\xf4\x82\xa2\x82\x52");
    print(ActionParam::ACTIONTYPE_CURSE4, "\x8e\xf4\x82\xa2\x82\x53");
    print(ActionParam::ACTIONTYPE_CURSE5, "\x8e\xf4\x82\xa2\x82\x54");
}

THUMB void status::StatusChange::print(ActionParam::ACTIONTYPE type, char* name)
{
}

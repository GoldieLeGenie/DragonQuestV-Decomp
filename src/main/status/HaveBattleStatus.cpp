#pragma ipa file
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/UseItem.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/btl/Encount.hpp"
#include "main/menu/StadiumData.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned short dq5::level::CharacterInitData::getActionMonsterID()
{
    return actionMonsterID;
}

inline unsigned short dq5::level::MonsterData::getAction1()
{
    return action1;
}

inline unsigned short dq5::level::MonsterData::getAction2()
{
    return action2;
}

inline unsigned short dq5::level::MonsterData::getAction3()
{
    return action3;
}

inline unsigned short dq5::level::MonsterData::getAction4()
{
    return action4;
}

inline unsigned short dq5::level::MonsterData::getAction5()
{
    return action5;
}

inline unsigned short dq5::level::MonsterData::getAction6()
{
    return action6;
}

inline unsigned char dq5::level::MonsterData::getAnimAll()
{
    return animAll;
}

inline unsigned char dq5::level::MonsterData::getAnim1()
{
    return anim1;
}

inline unsigned char dq5::level::MonsterData::getAnim2()
{
    return anim2;
}

inline unsigned char dq5::level::MonsterData::getAnim3()
{
    return anim3;
}

inline unsigned char dq5::level::MonsterData::getAnim4()
{
    return anim4;
}

inline unsigned char dq5::level::MonsterData::getAnim5()
{
    return anim5;
}

inline unsigned char dq5::level::MonsterData::getAnim6()
{
    return anim6;
}

inline char dq5::level::MonsterData::getGroup1()
{
    return (byte_1 & 0x2) >> 1;
}

inline char dq5::level::MonsterData::getGroup2()
{
    return (byte_1 & 0x4) >> 2;
}

inline char dq5::level::MonsterData::getGroup3()
{
    return (byte_1 & 0x8) >> 3;
}

inline char dq5::level::MonsterData::getGroup4()
{
    return (byte_1 & 0x10) >> 4;
}

inline char dq5::level::MonsterData::getGroup5()
{
    return (byte_1 & 0x20) >> 5;
}

inline char dq5::level::MonsterData::getGroup6()
{
    return (byte_1 & 0x40) >> 6;
}

inline char dq5::level::MonsterData::getFocus()
{
    return (byte_1 & 0x80) >> 7;
}

inline char dq5::level::MonsterData::getInteger()
{
    return byte_2 & 0x3;
}

inline char dq5::level::MonsterData::getTimes()
{
    return (byte_2 & 0xC) >> 2;
}

inline char dq5::level::MonsterData::getAvoid()
{
    return (byte_2 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getDragon()
{
    return (byte_8 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getMetal()
{
    return byte_9 & 0x3;
}

inline char dq5::level::MonsterData::getZombi()
{
    return (byte_9 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getPattern()
{
    return (byte_10 & 0x1C) >> 2;
}

inline CharacterType status::HaveStatusInfo::getCharacterType()
{
    return characterType_;
}

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline bool StadiumData::isStadiumBattle()
{
    return stadiumFlag_;
}

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int btl::Encount::getLandType()
{
    return landType_;
}

using namespace dq5::level;

int status::HaveBattleStatus::confusionDebugIndex_;
int status::HaveBattleStatus::eventFlag_;
static MonsterData* monsterData2_;
int status::HaveBattleStatus::parupunteDebugIndex_;
static CharacterInitData* characterInitData2_;


static void getRecord(int index)
{
    monsterData2_ = MonsterData::getRecord(index);
}

static void getCharacterDataRecord(int index)
{
    characterInitData2_ = CharacterInitData::getRecord(index);
}

dss::BitFlag<unsigned int> status::HaveBattleStatus::groupControl_[4];
int status::HaveBattleStatus::groupRoopIndex_[4];

int status::actionPattern[5][6] = {
    { 0x2b, 0x2a, 0x2b, 0x2b, 0x2a, 0x2b },
    { 0x44, 0x3a, 0x30, 0x26, 0x1b, 0x11 },
    { 0xc8, 0x28, 0x08, 0x04, 0x03, 0x01 },
    { 0x46, 0x46, 0x46, 0x10, 0x0f, 0x0f },
    { 0x46, 0x46, 0x46, 0x10, 0x0f, 0x0f },
};

THUMB status::HaveBattleStatus::HaveBattleStatus() : originalIndex_(0), originalType_(PLAYER), haveStatusInfo_(NULL), selectCommand_(NoSelect)
{
}

THUMB status::HaveBattleStatus::~HaveBattleStatus()
{
}

THUMB void status::HaveBattleStatus::initialize()
{
}

THUMB void status::HaveBattleStatus::setup(CharacterType type, int group, int index)
{
    groupIndex_ = group;
    index_ = index;
    escape_ = false;
    actionIndex_ = 0;
    actionCount_ = 0;
    patternFailedFlag_.clear();
    disablePattern_.clear();
    disablePattern2nd_.clear();
    selectCommand_ = NoSelect;
    type_ = type;
    change_ = false;
    mosyasActionCount_ = 0;
    for (int i = 0; i < MOSYAS_ACTION_COUNT; i++) {
        mosyasAction_[i] = 0x47;
    }
    if (type == PLAYER) {
        getCharacterDataRecord(index);
        monsterIndexForNpc_ = characterInitData2_->getActionMonsterID();
    }
    if (monsterIndexForNpc_ != 0 && type_ == PLAYER) {
        index_ = monsterIndexForNpc_;
        type_ = MONSTER;
    }
    if (type_ == PLAYER) {
        setupPlayer();
    }
    if (type_ == MONSTER) {
        setupMonster();
    }
}

THUMB void status::HaveBattleStatus::newBaseChangeMonster(int index)
{
    multiCount2_ = 0;
    groupControl_[groupIndex_].clear();
    index_ = index;
    if (type_ == PLAYER) {
        haveStatusInfo_->setupStatus(index_, true);
        setupMonster();
    } else if (type_ == MONSTER) {
        haveStatusInfo_->setupStatus(index, false);
        setupMonster();
    }
}

THUMB void status::HaveBattleStatus::newBaseChangeMonsterFromPlayer(int index)
{
    if (!change_) {
        originalIndex_ = index_;
        originalType_ = type_;
    }
    index_ = index;
    type_ = MONSTER;
    if (type_ == PLAYER) {
        haveStatusInfo_->setupActionDefence(index_, true);
    } else if (type_ == MONSTER) {
        haveStatusInfo_->setupActionDefence(index, false);
        setupMonster();
    }
    change_ = true;
}

THUMB void status::HaveBattleStatus::newBaseChangeMonsterReverse2()
{
    change_ = false;
    index_ = originalIndex_;
    type_ = originalType_;
    if (type_ == PLAYER) {
        haveStatusInfo_->setupActionDefence();
    } else if (type_ == MONSTER) {
        haveStatusInfo_->setupActionDefence(index_, false);
        setupMonster();
    }
}

THUMB void status::HaveBattleStatus::changeMonsterFromPlayer(int index)
{
    int hp = haveStatusInfo_->getHp();
    int mp = haveStatusInfo_->getMp();
    newBaseChangeMonsterFromPlayer(index);
    haveStatusInfo_->setHp(hp);
    haveStatusInfo_->setMp(mp);
}

THUMB void status::HaveBattleStatus::changeMonsterReverse()
{
    if (change_) {
        newBaseChangeMonsterReverse2();
    }
}

THUMB void status::HaveBattleStatus::setupPlayer()
{
    brains_ = 0;
    dragon_ = 0;
    metal_ = 0;
    zombi_ = 0;
    air_ = 0;
    slime_ = 0;
    jouk_ = 1;
    multi_ = 0;
}

THUMB void status::HaveBattleStatus::setupMonster()
{
    getRecord(index_);
    brains_ = monsterData2_->getInteger();
    multi_ = monsterData2_->getTimes();
    multiCount_ = 0;
    multiCount2_ = 0;
    group_[0] = monsterData2_->getGroup1();
    group_[1] = monsterData2_->getGroup2();
    group_[2] = monsterData2_->getGroup3();
    group_[3] = monsterData2_->getGroup4();
    group_[4] = monsterData2_->getGroup5();
    group_[5] = monsterData2_->getGroup6();
    crossFire_ = monsterData2_->getFocus();
    crossFireTarget_ = -1;
    level_ = 0;
    dragon_ = monsterData2_->getDragon();
    metal_ = monsterData2_->getMetal();
    zombi_ = monsterData2_->getZombi();
    air_ = 0;
    slime_ = 0;
    jouk_ = monsterData2_->getAvoid();
    roundActionIndex_ = 0;
}

THUMB bool status::HaveBattleStatus::isJouk()
{
    switch (jouk_) {
    case 0:
        return false;
    case 1:
        if (UnkDssRand::rand(64) <= 0) {
            return true;
        }
        return false;
    case 2:
        if (UnkDssRand::rand(16) <= 0) {
            return true;
        }
        return false;
    case 3:
        if (UnkDssRand::rand(4) <= 0) {
            return true;
        }
        return false;
    case 4:
        return false;
    }
    return false;
}

THUMB void status::HaveBattleStatus::setActionIndex(int actionIndex)
{
    actionIndex_ = actionIndex;
}

THUMB void status::HaveBattleStatus::setActionSelect(CallStart callStart, bool secondCheck)
{
    if (haveStatusInfo_ == NULL) {
        return;
    }
    if (type_ == PLAYER) {
        setActionSelectForPlayer();
    } else if (type_ == MONSTER) {
        if (haveStatusInfo_ != NULL && haveStatusInfo_->isMosyasExec()) {
            patternIndex_ = 7;
        } else {
            setActionSelectForMonster(callStart, secondCheck);
        }
    }
    if (callStart == StartRound) {
        roundActionIndex_ = actionIndex_;
        switch (roundActionIndex_) {
        case 0x49:
        case 0x4a:
            return;
        }
    }
}

THUMB void status::HaveBattleStatus::setActionSelectForPlayer()
{
    switch (selectCommand_) {
    case Attack:
        actionIndex_ = 0x47;
        break;
    case Defence:
        actionIndex_ = 0x49;
        break;
    case UseAction:
        actionIndex_ = selectIndex_;
        break;
    case UseItem:
        sortIndex_ = selectIndex_;
        selectItemIndex_ = haveStatusInfo_->getHaveItem().getItem(selectIndex_);
        actionIndex_ = UseItem::getBattleUseAction(selectItemIndex_);
        break;
    case NoSelect:
        actionIndex_ = 0;
        selectedTarget_ = 0;
        break;
    }
}

THUMB void status::HaveBattleStatus::setActionSelectForMonster(CallStart callStart, bool secondCheck)
{
    if (callStart == StartTurn) {
        switch (roundActionIndex_) {
        case 0x49:
        case 0x4a:
            return;
        }
    }
    if (secondCheck) {
        setLoopCount(true);
    }
    if (brains_ == 0) {
        setActionPatternForMonster(callStart);
        setActionIndexForMonster();
        setGroupControl();
    }
    if (brains_ == 1) {
        int bakupPatternIndex = patternIndex_;
        if (isActionFailed()) {
            for (int i = 0; i < 6; i++) {
                patternIndex_ = i;
                setActionIndexForMonster();
                checkRestMP_Mahoton();
            }
        }
        if (!secondCheck && callStart == StartTurn) {
            patternIndex_ = bakupPatternIndex;
            if (!isActionDisable()) {
                setActionIndexForMonster();
                return;
            }
        }
        setActionPatternForMonster(callStart);
        setActionIndexForMonster();
        setGroupControl();
    }
    if (brains_ == 2) {
        for (int i = 0; i < 6; i++) {
            patternIndex_ = i;
            setActionIndexForMonster();
            checkRestMP_Mahoton();
        }
        if (!secondCheck && callStart == StartRound) {
            getRecord(index_);
            int pattern = monsterData2_->getPattern();
            if (pattern == 7) {
                return;
            }
        }
        setActionPatternForMonster(callStart);
        setActionIndexForMonster();
        if (callStart == StartTurn) {
            setGroupControl();
        }
    }
    if (brains_ == 3) {
        setActionPatternForMonster(callStart);
        setActionIndexForMonster();
    }
    multiGlobalCount_++;
    selectCommand_ = AISelect;
}

THUMB void status::HaveBattleStatus::setActionPatternForMonster(CallStart callStart)
{
    getRecord(index_);
    int pattern = monsterData2_->getPattern();
    patternIndex_ = 0;
    while (true) {
        switch (pattern) {
        case 0:
        case 1:
        case 2:
        case 3:
            patternIndex_ = dss::arrayToIndex(actionPattern[pattern], UnkDssRand::rand(256), 6);
            if (pattern == 2 && disablePattern_.check(1) && disablePattern_.check(2)) {
                int tmpPattern[4] = { 8, 4, 3, 1 };
                patternIndex_ = dss::arrayToIndex(tmpPattern, UnkDssRand::rand(16), 4) + 2;
            }
            break;
        case 4:
            actionCount_ = dss::loop<int>(actionCount_, 0, 5);
            patternIndex_ = actionCount_;
            break;
        case 5:
            while (true) {
                actionCount_ = dss::loop<int>(actionCount_, 0, 2);
                switch (actionCount_) {
                case 0:
                    patternIndex_ = UnkDssRand::rand(2);
                    break;
                case 1:
                    patternIndex_ = UnkDssRand::rand(2) + 2;
                    break;
                case 2:
                    patternIndex_ = UnkDssRand::rand(2) + 4;
                    break;
                }
                bool flag = false;
                switch (actionCount_) {
                case 0:
                    if (isActionDisable2nd(0) && isActionDisable2nd(1)) {
                        flag = true;
                    }
                    break;
                case 1:
                    if (isActionDisable2nd(2) && isActionDisable2nd(3)) {
                        flag = true;
                    }
                    break;
                case 2:
                    if (isActionDisable2nd(4) && isActionDisable2nd(5)) {
                        flag = true;
                    }
                    break;
                }
                if (!flag) {
                    break;
                }
                setLoopCount(false);
            }
            break;
        case 6:
            while (true) {
                patternIndex_ = (actionCount_ % 2 != 0) ? UnkDssRand::rand(5) + 1 : 0;
                bool flag = true;
                for (int i = 1; i < 6; i++) {
                    if (!isActionDisable2nd(i)) {
                        flag = false;
                    }
                }
                if (!flag) {
                    break;
                }
                setLoopCount(false);
            }
            break;
        case 7:
            groupRoopIndex_[groupIndex_] = dss::loop<int>(groupRoopIndex_[groupIndex_], 0, 5);
            patternIndex_ = groupRoopIndex_[groupIndex_];
            groupRoopIndex_[groupIndex_]++;
            break;
        }
        if (callStart == StartTurn) {
            int action = getActionIndexForPattern();
            if (action == 0x49) {
                setLoopCount(true);
                continue;
            }
            if (action == 0x4a) {
                setLoopCount(true);
                continue;
            }
        }
        if (getRestNum() == 0) {
            patternIndex_ = 7;
            return;
        }
        if (!checkGroupControl()) {
            setLoopCount(false);
            continue;
        }
        if (isActionAllDisable()) {
            patternIndex_ = 7;
            return;
        }
        if (isActionAllDisable2nd()) {
            patternIndex_ = 7;
            return;
        }
        if (!isActionDisable() && !isActionDisable2nd()) {
            return;
        }
        setRestOne();
        if (!isRestOneAction2nd()) {
            continue;
        }
        if (!checkGroupControl()) {
            continue;
        }
        if (isActionAllDisable()) {
            patternIndex_ = 7;
            return;
        }
        if (isActionAllDisable2nd()) {
            patternIndex_ = 7;
            return;
        }
        if (isActionDisable()) {
            continue;
        }
        if (isActionDisable2nd()) {
            continue;
        }
        return;
    }
}

template <> THUMB int dss::loop<int>(int x, int a, int b)
{
    if (x > b) {
        return a;
    }
    if (x < a) {
        return b;
    }
    return x;
}

THUMB void status::HaveBattleStatus::setActionIndexForMonster()
{
    getRecord(index_);
    switch (patternIndex_) {
    case 0:
        actionIndex_ = monsterData2_->getAction1();
        break;
    case 1:
        actionIndex_ = monsterData2_->getAction2();
        break;
    case 2:
        actionIndex_ = monsterData2_->getAction3();
        break;
    case 3:
        actionIndex_ = monsterData2_->getAction4();
        break;
    case 4:
        actionIndex_ = monsterData2_->getAction5();
        break;
    case 5:
        actionIndex_ = monsterData2_->getAction6();
        break;
    case 7:
        actionIndex_ = 0x1e2;
        break;
    }
}

THUMB int status::HaveBattleStatus::getActionIndexForPattern()
{
    getRecord(index_);
    switch (patternIndex_) {
    case 0:
        return monsterData2_->getAction1();
    case 1:
        return monsterData2_->getAction2();
    case 2:
        return monsterData2_->getAction3();
    case 3:
        return monsterData2_->getAction4();
    case 4:
        return monsterData2_->getAction5();
    case 5:
        return monsterData2_->getAction6();
    }
    return 0;
}

THUMB int status::HaveBattleStatus::getActionIndex(int index)
{
    getRecord(index_);
    switch (index) {
    case 0:
        return monsterData2_->getAction1();
    case 1:
        return monsterData2_->getAction2();
    case 2:
        return monsterData2_->getAction3();
    case 3:
        return monsterData2_->getAction4();
    case 4:
        return monsterData2_->getAction5();
    case 5:
        return monsterData2_->getAction6();
    }
    return 0;
}

THUMB int status::HaveBattleStatus::getActionAnimation()
{
    getRecord(index_);
    switch (patternIndex_) {
    case 0:
        return monsterData2_->getAnim1();
    case 1:
        return monsterData2_->getAnim2();
    case 2:
        return monsterData2_->getAnim3();
    case 3:
        return monsterData2_->getAnim4();
    case 4:
        return monsterData2_->getAnim5();
    case 5:
        return monsterData2_->getAnim6();
    }
    return monsterData2_->getAnimAll();
}

THUMB void status::HaveBattleStatus::setActionFailed(int actionIndex)
{
    int backup = patternIndex_;
    for (int i = 0; i < 6; i++) {
        patternIndex_ = i;
        setActionIndexForMonster();
        patternFailedFlag_.set(1 << i);
    }
    patternIndex_ = backup;
}

THUMB bool status::HaveBattleStatus::isActionFailed()
{
    return patternFailedFlag_.flag_ != 0;
}

THUMB void status::HaveBattleStatus::setActionDisable(bool flag)
{
    if (flag) {
        disablePattern_.set(1 << patternIndex_);
    } else {
        disablePattern_.remove(1 << patternIndex_);
    }
}

THUMB bool status::HaveBattleStatus::isActionDisable()
{
    return disablePattern_.check(1 << patternIndex_);
}

THUMB bool status::HaveBattleStatus::isActionAllDisable()
{
    return (disablePattern_.flag_ & 0x3f) == 0x3f;
}

THUMB void status::HaveBattleStatus::setActionDisable2nd()
{
    disablePattern2nd_.set(1 << patternIndex_);
}

THUMB bool status::HaveBattleStatus::isActionDisable2nd()
{
    return disablePattern2nd_.check(1 << patternIndex_);
}

THUMB bool status::HaveBattleStatus::isActionDisable2nd(int pattern)
{
    return disablePattern2nd_.check(1 << pattern);
}

THUMB bool status::HaveBattleStatus::isActionAllDisable2nd()
{
    return (disablePattern2nd_.flag_ & 0x3f) == 0x3f;
}

THUMB void status::HaveBattleStatus::clearActionDisable2nd()
{
    disablePattern2nd_.clear();
}

THUMB bool status::HaveBattleStatus::isRestOneAction2nd()
{
    int count = 0;
    int index = -1;
    for (int i = 0; i < 6; i++) {
        if (disablePattern2nd_.check(1 << i)) {
            count++;
        } else {
            index = i;
        }
    }
    if (count == 5) {
        patternIndex_ = index;
        return true;
    }
    return false;
}

THUMB void status::HaveBattleStatus::setRestOne()
{
    int flag[6] = { true, true, true, true, true, true };
    for (int i = 0; i < 6; i++) {
        if (disablePattern_.check(1 << i)) {
            flag[i] = false;
        }
        if (disablePattern2nd_.check(1 << i)) {
            flag[i] = false;
        }
        if (groupControl_[groupIndex_].check(1 << i)) {
            flag[i] = false;
        }
    }
    int count = 0;
    int index = 0;
    for (int i = 0; i < 6; i++) {
        if (flag[i]) {
            count++;
            index = i;
        }
    }
    if (count == 1) {
        patternIndex_ = index;
    }
}

THUMB int status::HaveBattleStatus::getRestNum()
{
    int flag[6] = { true, true, true, true, true, true };
    for (int i = 0; i < 6; i++) {
        if (disablePattern_.check(1 << i)) {
            flag[i] = false;
        }
        if (disablePattern2nd_.check(1 << i)) {
            flag[i] = false;
        }
        if (groupControl_[groupIndex_].check(1 << i)) {
            flag[i] = false;
        }
    }
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (flag[i]) {
            count++;
        }
    }
    return count;
}

THUMB bool status::HaveBattleStatus::isUseMp()
{
    if (haveStatusInfo_ == NULL) {
        return true;
    }
    int useMp = UseAction::getUseMp(actionIndex_);
    if (useMp == 0xff && haveStatusInfo_->getMp() != 0) {
        return true;
    }
    if (haveStatusInfo_->getMp() >= useMp) {
        return true;
    }
    return false;
}

THUMB int status::HaveBattleStatus::isMahoton()
{
    if (haveStatusInfo_ == NULL) {
        return false;
    }
    if (UseAction::isMahoton(actionIndex_)) {
        return haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_MAHOTON);
    }
    return false;
}

THUMB int status::HaveBattleStatus::isFizzleZone()
{
    if (haveStatusInfo_ == NULL) {
        return false;
    }
    if (UseAction::isMahoton(actionIndex_)) {
        return haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_FIZZLEZONE);
    }
    return false;
}

THUMB bool status::HaveBattleStatus::checkRestMP_Mahoton()
{
    if (!isUseMp() || isMahoton() || isFizzleZone()) {
        setActionDisable(true);
        return false;
    }
    setActionDisable(false);
    return true;
}

THUMB void status::HaveBattleStatus::setLoopCount(bool secondCheck)
{
    getRecord(index_);
    int pattern = monsterData2_->getPattern();
    switch (pattern) {
    case 4:
        actionCount_++;
        break;
    case 5:
        if (!secondCheck) {
            actionCount_++;
        }
        break;
    case 6:
        if (!secondCheck) {
            actionCount_++;
        }
        break;
    }
}

THUMB void status::HaveBattleStatus::clearGroupControl()
{
    for (int i = 0; i < 4; i++) {
        groupControl_[i].clear();
    }
}

THUMB void status::HaveBattleStatus::setGroupControl()
{
    if (patternIndex_ <= 6 && group_[patternIndex_] != 0) {
        groupControl_[groupIndex_].set(1 << patternIndex_);
    }
}

THUMB bool status::HaveBattleStatus::checkGroupControl()
{
    if (group_[patternIndex_] != 0 && groupControl_[groupIndex_].check(1 << patternIndex_)) {
        return false;
    }
    return true;
}

THUMB void status::HaveBattleStatus::setSelectCommand(SelectCommand command, int index)
{
    selectCommand_ = command;
    selectIndex_ = index;
}

THUMB status::HaveBattleStatus::SelectCommand status::HaveBattleStatus::getSelectCommand()
{
    return selectCommand_;
}

THUMB void status::HaveBattleStatus::clearSelectCommand()
{
    selectCommand_ = NoSelect;
    selectedTarget_ = -1;
    selectedGroup_ = -1;
}

THUMB void status::HaveBattleStatus::startBattle()
{
    selectCommand_ = NoSelect;
    multiCount_ = 0;
    multiCount2_ = 0;
    multiGlobalCount_ = -1;
    for (int i = 0; i < 4; i++) {
        groupRoopIndex_[i] = 0;
    }
}

THUMB void status::HaveBattleStatus::execStartOfRound()
{
    multiTurnCount_ = 0;
    clearActionDisable2nd();
    multiExecCount_ = 0;
}

THUMB void status::HaveBattleStatus::setMultiAction()
{
    multiCount2_++;
}

THUMB bool status::HaveBattleStatus::isMultiAction()
{
    bool ret = false;
    switch (multi_) {
    case 0:
        multiCount_ = 0;
        break;
    case 1:
        if (multiTurnCount_ == 0 && UnkDssRand::rand(2) != 0) {
            ret = true;
        }
        break;
    case 2:
        if (multiCount_ == 0) {
            ret = true;
        }
        multiCount_++;
        if (multiCount_ > 1) {
            multiCount_ = 0;
        }
        break;
    case 3:
        if (multiCount_ < 2) {
            ret = true;
        }
        break;
    case 4:
        switch (multiCount2_ % 3) {
        case 0:
            ret = true;
            break;
        case 1:
            break;
        case 2:
            ret = true;
            break;
        }
        break;
    case 5:
        break;
    case 6:
        switch (multiCount2_ % 3) {
        case 0:
            break;
        case 1:
            ret = true;
            break;
        case 2:
            break;
        }
        break;
    }
    multiTurnCount_++;
    return ret;
}

THUMB int status::HaveBattleStatus::getParupunteAction(int event)
{
    if (event) {
        int parupunte[10] = { 0x1be, 0x1bf, 0x1c6, 0x1c9, 0x1cc, 0x1d0, 0x1d1, 0x1d2, 0x1d4, 0x1d6 };
        return parupunte[UnkDssRand::rand(10)];
    }
    int parupunte[25] = { 0x1b9, 0x1ba, 0x1bc, 0x1bd, 0x1be, 0x1bf, 0x1c1, 0x1c2, 0x1c4, 0x1c5, 0x1c6, 0x1c7, 0x1c9, 0x1ca, 0x1cb, 0x1cc, 0x1cd, 0x1ce, 0x1cf, 0x1d0, 0x1d1, 0x1d2, 0x1d3, 0x1d4, 0x1d6 };
    return parupunte[UnkDssRand::rand(25)];
}

THUMB int status::HaveBattleStatus::getParupunteActionForMonster(int event)
{
    if (event) {
        int parupunte[8] = { 0x1be, 0x1bf, 0x1c6, 0x1c9, 0x1cc, 0x1d0, 0x1d4, 0x1d6 };
        return parupunte[UnkDssRand::rand(8)];
    }
    int parupunte[18] = { 0x1b9, 0x1ba, 0x1bc, 0x1bd, 0x1be, 0x1bf, 0x1c4, 0x1c6, 0x1c7, 0x1c9, 0x1cb, 0x1cc, 0x1cd, 0x1cf, 0x1d0, 0x1d3, 0x1d4, 0x1d6 };
    return parupunte[UnkDssRand::rand(18)];
}

THUMB void status::HaveBattleStatus::setupParupunteAction()
{
    if (haveStatusInfo_ == NULL || haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_FIZZLEZONE) || actionIndex_ != 0x42) {
        return;
    }
    actionIndex_ = getParupunteAction(eventFlag_);
    if (btl::Encount::getSingleton()->getLandType() != 0) {
        while (true) {
            if (actionIndex_ != 0x1c5) {
                break;
            }
            actionIndex_ = getParupunteAction(false);
        }
    }
    if (btl::Encount::getSingleton()->getLandType() != 8) {
        while (true) {
            if (actionIndex_ != 0x1c4) {
                break;
            }
            actionIndex_ = getParupunteAction(false);
        }
    }
    if (!g_Party.isCarriage() || !g_StageAttribute.isCarriageEnable() || !g_StageAttribute.isCarriageEnter()) {
        while (true) {
            if (actionIndex_ != 0x1ca) {
                break;
            }
            actionIndex_ = getParupunteAction(false);
        }
    }
    if (type_ == MONSTER) {
        actionIndex_ = getParupunteActionForMonster(eventFlag_);
        if (btl::Encount::getSingleton()->getLandType() != 8) {
            while (true) {
                if (actionIndex_ != 0x1c4) {
                    break;
                }
                actionIndex_ = getParupunteActionForMonster(eventFlag_);
            }
        }
    }
    if (parupunteDebugIndex_ != 0) {
        actionIndex_ = parupunteDebugIndex_;
        parupunteDebugIndex_ = 0;
    }
    selectCommand_ = UseAction;
    selectedTarget_ = -1;
    selectedGroup_ = -1;
}

THUMB int status::HaveBattleStatus::getPlayerConfuseAction()
{
    int confusion[18] = { 0x191, 0x193, 0x194, 0x195, 0x196, 0x197, 0x198, 0x199, 0x19a, 0x19b, 0x19c, 0x19e, 0x19f, 0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a5 };
    return confusion[UnkDssRand::rand(18)];
}

THUMB int status::HaveBattleStatus::getMonsterConfuseAction()
{
    int confusion[8] = { 0x1a6, 0x1a7, 0x1a8, 0x1a9, 0x1aa, 0x1ab, 0x1ac, 0x1ad };
    return confusion[UnkDssRand::rand(8)];
}

THUMB int status::HaveBattleStatus::getMonsterConfuseActionOnEvent()
{
    int confusion[5] = { 0x1a7, 0x1a8, 0x1a9, 0x1ab, 0x1ac };
    return confusion[UnkDssRand::rand(5)];
}

THUMB int status::HaveBattleStatus::getMonsterConfuseActionOnStadium()
{
    if (!g_StadiumData.isStadiumBattle()) {
        return 0;
    }
    int confusion[5] = { 0x1a7, 0x1a8, 0x1a9, 0x1ab, 0x1ac };
    return confusion[UnkDssRand::rand(5)];
}

THUMB void status::HaveBattleStatus::setupConfuseAction()
{
    if (haveStatusInfo_ == NULL || !haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_KONRAN)) {
        return;
    }
    haveStatusInfo_->setConfuseMissAttack(false);
    if (haveStatusInfo_->getCharacterType() == PLAYER || monsterIndexForNpc_ != 0) {
        actionIndex_ = getPlayerConfuseAction();
        if (haveStatusInfo_->getHaveStatus().getSex() == 1 && actionIndex_ == 0x19a) {
            actionIndex_ = 0x191;
        }
        if (actionIndex_ == 0x1a3) {
            if (g_Party.isCarriage() && g_StageAttribute.isCarriageEnable() && g_StageAttribute.isCarriageEnter()) {
                if (PartyStatusUtility::getAlivePlayerCountOutsideCarriage() == 1) {
                    actionIndex_ = 0x191;
                }
                if (StatusChange::statusCloseDoor_.isEnable()) {
                    actionIndex_ = 0x191;
                }
            } else {
                actionIndex_ = 0x191;
            }
        }
        if (actionIndex_ == 0x19f) {
            if (PartyStatusUtility::getAlivePlayerCountOutsideCarriage() == 1) {
                actionIndex_ = 0x191;
            }
            g_Party.setBattleMode();
            g_Party.getCount();
        }
        if (actionIndex_ == 0x196 && PartyStatusUtility::getAlivePlayerCountOutsideCarriage() == 1) {
            actionIndex_ = 0x191;
        }
        if (actionIndex_ == 0x19e && !haveStatusInfo_->getHaveEquipment().getEquipment(ITEM_ARMOR, 0)) {
            actionIndex_ = 0x191;
        }
        if (haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_DORAGORAM)) {
            actionIndex_ = 0x1a5;
        }
    } else if (type_ == MONSTER) {
        int count = g_Monster.getAliveCount();
        if (UnkDssRand::rand(4) < 3 && count != 1) {
            actionIndex_ = 0x192;
        } else {
            actionIndex_ = getMonsterConfuseAction();
            if (eventFlag_) {
                actionIndex_ = getMonsterConfuseActionOnEvent();
            }
            int temp = getMonsterConfuseActionOnStadium();
            if (temp) {
                actionIndex_ = temp;
            }
        }
    }
    if (confusionDebugIndex_ != 0) {
        actionIndex_ = confusionDebugIndex_;
        confusionDebugIndex_ = 0;
    }
    selectCommand_ = UseAction;
    selectedTarget_ = -1;
    selectedGroup_ = -1;
}

THUMB void status::HaveBattleStatus::setupSpecialAction(int actionIndex)
{
    actionIndex_ = actionIndex;
    selectCommand_ = UseAction;
    selectedTarget_ = -1;
    selectedGroup_ = -1;
}

THUMB void status::HaveBattleStatus::setupSleepAction()
{
    setupRollOver();
}

THUMB void status::HaveBattleStatus::setupRollOver()
{
    if (haveStatusInfo_ != NULL && type_ != MONSTER && haveStatusInfo_->getStatusChange().isEnable(ActionParam::ACTIONTYPE_NEMURI)) {
        if (haveStatusInfo_->getHaveEquipment().isEquipment(0x61)) {
            actionIndex_ = 0x6b;
        }
    }
}

THUMB void status::HaveBattleStatus::setupTurnBeforeAction()
{
    setupSleepAction();
}

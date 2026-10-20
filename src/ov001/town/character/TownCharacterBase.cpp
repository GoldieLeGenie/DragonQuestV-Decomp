#pragma ipa file
#include "ov001/town/character/TownCharacterBase.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/stage/TownExtraCollManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/CharaData.hpp"

#pragma thumb on

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::CharaData::getVoice()
{
    return byte_1 & 3;
}

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline int twn::TownStageManager::characoterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 rad, dss::Fix32Vector3* retVec, int flag)
{
    return coll_.characterColl(oldPos, newPos, rad, retVec, flag);
}

inline int twn::TownStageManager::getCrossPolyNo(dss::Fix32Vector3& pos0, dss::Fix32Vector3& pos1, dss::Fix32* length, bool flag)
{
    return stage_.collCrossCheckPoly(pos0, pos1, length, flag);
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

inline dss::Fix32Vector3& twn::TownCharacterBase::getPosition()
{
    return data_.position;
}

inline void TownCharacterManager::setSyncroPos(int index)
{
    character_[index]->setSyncroPos();
}

inline void twn::TownCharacterBase::setAllEventLock(bool flag)
{
    allEventLock_ = flag;
}

inline bool twn::TownCharacterBase::getMonsterSpeakAll()
{
    return monsterTalk_;
}

const dss::Fix32 twn::fixLen((fx32)0x333);

int twn::TownCharacterBase::areaCheck_;
int twn::TownCharacterBase::allEventLock_;
int twn::TownCharacterBase::monsterTalk_;

twn::TownCharacterBase::TownCharacterBase() : collFlag_(true)
{
}

twn::TownCharacterBase::~TownCharacterBase()
{
}

void twn::TownCharacterBase::setup(TOWN_CHARACTER& chara)
{
    data_.enable = true;
    data_.charaIndex = chara.charaIndex;
    data_.dir = chara.dir;
    data_.position = chara.position;
    data_.flag.clear();
    simpleMove_.setup();
    moveType_ = MOVE_TYPE_NONE;
    stageColl_ = 0;
    animCounter_ = 0;
    rgbFrame_ = -1;
    mapNo_ = -1;
    alphaMax_ = 0x1f;
    switch (dq5::level::CharaData::getRecord(charaParamIndex_)->getVoice()) {
    case 0:
        voice_ = 0x30;
        break;
    case 1:
        voice_ = 0x31;
        break;
    case 2:
        voice_ = 0x32;
        break;
    case 3:
        voice_ = 0x33;
        break;
    }
    if (TownSystem::getSingleton().getScriptSystem().isEventLock() == true) {
        setPersonalEventLock(true);
    }
}

void twn::TownCharacterBase::setDir(int dir)
{
    data_.dir = dir;
}

int twn::TownCharacterBase::getDir()
{
    return 0;
}

void twn::TownCharacterBase::setRotation(dss::Vector3<short>& rot)
{
}

void twn::TownCharacterBase::setRotation(unsigned short rot)
{
}

void twn::TownCharacterBase::setShadow(int flag)
{
}

void twn::TownCharacterBase::setAnimation(int flag)
{
}

void twn::TownCharacterBase::setNearCharacter(int flag)
{
}

void twn::TownCharacterBase::setDisplay(int flag)
{
}

int twn::TownCharacterBase::isDisplay()
{
    return false;
}

void twn::TownCharacterBase::setSleepCharacter(int flag)
{
}

void twn::TownCharacterBase::setWriggleCharacter(int flag)
{
}

void twn::TownCharacterBase::setAlpha(unsigned char alpha)
{
}

void twn::TownCharacterBase::changePose(int pose)
{
}

void twn::TownCharacterBase::restorePose()
{
}

void twn::TownCharacterBase::requestReload()
{
}

void twn::TownCharacterBase::setHueChange(int type, int frame)
{
}

bool twn::TownCharacterBase::isHueChange()
{
    return false;
}

void twn::TownCharacterBase::setShadowOnly(int flag)
{
}

void twn::TownCharacterBase::setScale(dss::Fix32 scale)
{
}

void twn::TownCharacterBase::setScriptData(TOWN_SCRIPT_DATA& data)
{
    script_ = data;
    script_.isEnd = false;
}

int twn::TownCharacterBase::isScriptEnd()
{
    return script_.isEnd;
}

void twn::TownCharacterBase::execWait()
{
    int& counter = script_.counter;
    int& frame = script_.frame;
    int& isEnd = script_.isEnd;
    if (data_.flag.check(0x80) == true) {
        return;
    }
    counter++;
    if (counter >= frame) {
        isEnd = true;
    }
}

void twn::TownCharacterBase::execMove()
{
    if (getTalked() == true) {
        return;
    }
    dss::Fix32Vector3 prevPos = getPosition();
    dss::Fix32Vector3 nextPos = prevPos;
    simpleMove_.execMove(nextPos);
    if (TownPlayerManager::getSingleton().charaColl_ == true && collFlag_ == true) {
        if ((areaCheck_ == true && data_.flag.check(1) == true) || areaCheck_ == false) {
            dss::Fix32Vector3 vec = nextPos - prevPos;
            dss::Fix32Vector3 player = TownPlayerManager::getSingleton().getPosition();
            player.vy = nextPos.vy;
            dss::Fix32Vector3 diff = player - nextPos;
            if (diff.lengthsq().value < (TownPlayerAction::collR * TownPlayerAction::collR * 4).value + 0x12c) {
                vec.normalize();
                diff.normalize();
                dss::Fix32 dot = diff * vec;
                if (dot.value > 0x165) {
                    if (data_.flag.check(0x4000)) {
                        TownCharacterManager::getSingleton()->setSyncroPos(syncroNo_);
                    }
                    return;
                }
            }
        }
    }
    if (stageColl_ & 1 || stageColl_ & 2) {
        TownStageManager::getSingleton()->characoterColl(prevPos, nextPos, TownPlayerAction::collR, &nextPos, stageColl_);
    }
    if (data_.flag.check(8) == false) {
        setDir(moveIdx_);
    }
    setPosition(nextPos);
    if (stageColl_ & 4) {
        if (TownCharacterManager::getSingleton()->charaToCharaColl(this, 0, 0) == true) {
            setPosition(prevPos);
            return;
        }
    }
    syncroType_ = SYNCHRONOUS_MOVE;
    if (simpleMove_.moveUpdate() == true) {
        if (moveType_ == MOVE_TYPE_TO_PARTY) {
            setNextMoveToParty();
            setSimpleMove();
            return;
        }
        moveType_ = MOVE_TYPE_NONE;
        script_.isEnd = true;
    }
}

void twn::TownCharacterBase::setPosition(dss::Fix32Vector3& pos)
{
    data_.position = pos;
}

void twn::TownCharacterBase::execRiseup()
{
    int& icon = script_.num[0];
    int& index = script_.num[1];
    int& counter = script_.counter;
    int& isEnd = script_.isEnd;
    if (counter == 0) {
        index = TownRiseupManager::getSingleton().setup(icon, getPosition());
    }
    if (TownRiseupManager::getSingleton().isFinish(index)) {
        isEnd = true;
    }
    counter++;
}

void twn::TownCharacterBase::setColor(unsigned char r, unsigned char g, unsigned char b)
{
}

void twn::TownCharacterBase::execTremble()
{
    static const int defaultRoop = 0x10;
    dss::Fix32Vector3& start = script_.node[0];
    int& direction = script_.num[0];
    int& counter = script_.counter;
    int& frame = script_.frame;
    int& mode = script_.num[1];
    int& roop = script_.num[2];
    int n;
    if (roop == 0) {
        roop = defaultRoop;
    }
    switch (mode) {
    case 0:
        n = 1;
        break;
    case 1:
        n = 2;
        break;
    case 2:
        n = 4;
        break;
    case 3:
        n = 8;
        break;
    }
    if (counter == 0) {
        start = data_.position;
    }
    dss::Fix32Vector3 pos = start;
    int val;
    switch (direction) {
    case 0:
        val = pos.vy.value;
        break;
    case 1:
        val = pos.vx.value;
        break;
    case 2:
        val = pos.vz.value;
        break;
    }
    int current = counter % roop;
    if (current < roop / 2) {
        if (current < roop / 4) {
            val += 0x100 / n;
        } else {
            val -= 0x100 / n;
        }
    } else {
        if (current < roop * 3 / 4) {
            val -= 0x100 / n;
        } else {
            val += 0x100 / n;
        }
    }
    switch (direction) {
    case 0:
        pos.vy.value = val;
        break;
    case 1:
        pos.vx.value = val;
        break;
    case 2:
        pos.vz.value = val;
        break;
    }
    setPosition(pos);
    if (++counter >= frame) {
        setPosition(start);
        script_.isEnd = true;
    }
}

void twn::TownCharacterBase::setCollFlag(int flag)
{
    collFlag_ = flag;
}

int twn::TownCharacterBase::getCollFlag()
{
    return collFlag_;
}

void twn::TownCharacterBase::execute()
{
    if (data_.flag.check(0x80) == true) {
        return;
    }
    if (TownSystem::getSingleton().getScriptSystem().isEventLock() == true) {
        switch (moveType_) {
        case MOVE_TYPE_AREA:
        case MOVE_TYPE_PURSUE:
        case MOVE_TYPE_PASSIVE:
        case MOVE_TYPE_RANDOM:
        case MOVE_TYPE_REVESE:
            return;
        }
    } else if (data_.flag.check(0x20) == true && data_.flag.check(0x40) == true) {
        data_.flag.remove(0x40);
        setDir(swingIdx_);
    }
    switch (moveType_) {
    case MOVE_TYPE_AREA:
        execAreaMove();
        break;
    case MOVE_TYPE_ROOT:
        execRootMove();
        break;
    case MOVE_TYPE_PURSUE:
        execPursueMove();
        break;
    case MOVE_TYPE_TO_PARTY:
    case MOVE_TYPE_SIMPLE_MOVE:
        if (data_.flag.check(0x4000)) {
            syncroPos_ = data_.position;
            if (syncroType_ == SYNCHRONOUS_STOP) {
                break;
            }
        }
        execMove();
        break;
    case MOVE_TYPE_JUMP:
        jumpMove();
        break;
    case MOVE_TYPE_PASSIVE:
        execMovePassive();
        break;
    case MOVE_TYPE_RANDOM:
        execMoveRandom();
        break;
    case MOVE_TYPE_REVESE:
        execMoveReverse();
        break;
    case MOVE_TYPE_WAIT:
        execMoveWait();
        break;
    case MOVE_TYPE_MAP_OBJ:
        mapObjMove();
        break;
    }
    if (data_.flag.check(0x10) == true) {
        dss::Vector3<short> rot;
        rot.vy = getDir();
        simpleMove_.execRot(rot);
        setDir(rot.vy);
        if (simpleMove_.rotUpdate() == true) {
            data_.flag.remove(0x10);
        }
    }
    if (changeAlphaType_ != 0) {
        changeAlpha();
    }
    if (rgbFrame_ != -1) {
        changeRGB();
    }
}

void twn::TownCharacterBase::changeRGB()
{
    if (rgbFrame_ >= 0) {
        switch (rgbChangeType_) {
        case 0:
            setRGB += addRGB;
            setPaletteRate(setRGB.vx, setRGB.vy, setRGB.vz);
            break;
        case 1: {
            unsigned char r = setRGB.vx.value / 0x1000;
            unsigned char g = setRGB.vy.value / 0x1000;
            unsigned char b = setRGB.vz.value / 0x1000;
            dss::Fix32 rate;
            rate.value = (rgbFrameMax_ - rgbFrame_) << 12;
            rate /= rgbFrameMax_;
            setPaletteRate(r, g, b, rate);
            break;
        }
        }
    }
    rgbFrame_--;
}

void twn::TownCharacterBase::setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
}

void twn::TownCharacterBase::changeAlpha()
{
    static int fadeData[10] = {10, 9, 9, 8, 8, 7, 6, 4, 2, 0};
    static int blinkFrame[6] = {7, 6, 6, 5, 4, 3};
    switch (changeAlphaType_) {
    case 2:
    case 4: {
        int index = dss::clamp<int>(0, alphaCounter_ * 10 / alphaFrame_, 9);
        unsigned char fadeOut = (changeAlphaType_ == 2) ? 1 : 0;
        unsigned char alpha;
        if (fadeOut) {
            alpha = fadeData[9 - index] * alphaMax_ / 10;
        } else {
            alpha = fadeData[index] * alphaMax_ / 10;
        }
        remoteAlpha_ = alpha;
        remoteAlpha_ = dss::clamp<unsigned int>(0, remoteAlpha_, (unsigned char)alphaMax_);
        setAlpha(remoteAlpha_);
        break;
    }
    case 3:
    case 5: {
        int prevIndex = (alphaCounter_ - 1) * 6 / alphaFrame_;
        int index = dss::clamp<int>(0, alphaCounter_ * 6 / alphaFrame_, 5);
        unsigned char setA = changeAlphaType_ == 3 ? alphaMax_ : 0;
        unsigned char resetA = changeAlphaType_ == 3 ? 0 : alphaMax_;
        if (blinkCounter_ == blinkFrame[index] || prevIndex != index) {
            blinkCounter_ = 0;
            setAlpha(setA);
        }
        if (blinkCounter_ == 0) {
            setAlpha(setA);
        } else if (blinkCounter_ == 3) {
            setAlpha(resetA);
        }
        blinkCounter_++;
        break;
    }
    case 1:
        remoteAlpha_ += alphaAdd_;
        remoteAlpha_ = dss::clamp<unsigned int>(0, remoteAlpha_, (unsigned char)alphaMax_);
        setAlpha(remoteAlpha_);
        if (remoteAlpha_ == 0 || remoteAlpha_ == alphaMax_) {
            script_.isEnd = true;
            alphaAdd_ = 0;
        }
        break;
    }
    if (alphaCounter_ >= alphaFrame_) {
        switch (changeAlphaType_) {
        case 4:
        case 5:
            setDisplay(false);
            break;
        }
        changeAlphaType_ = 0;
    }
    alphaCounter_++;
}

void twn::TownCharacterBase::execPursueMove()
{
    if (moveData_.counter >= 0x3c) {
        moveData_.counter = 0;
    }
    if (moveData_.counter >= 0x1e) {
        moveData_.counter++;
        return;
    }
    static dss::Fix32 length2((fx32)0xb33);
    dss::Fix32Vector3 oldPos = getPosition();
    int drawCharaCount = TownPlayerManager::getSingleton().getPartyDrawCount();
    dss::Fix32Vector3 vec = TownPlayerManager::getSingleton().party_.getMemberPos(drawCharaCount) - oldPos;
    if (vec.lengthsq() < fixLen * fixLen) {
        return;
    }
    dss::Fix32Vector3 vec2 = TownPlayerManager::getSingleton().getPosition() - oldPos;
    if (collFlag_ == true) {
        if (vec2.lengthsq() < length2 * length2) {
            return;
        }
    }
    short idx = getDir();
    if (moveData_.counter % 0x3c < 0x1e && (getDisplayFrame() & 1)) {
        vec.normalize();
        dss::Fix32Vector3 newPos = oldPos + vec * moveData_.speed;
        TownStageManager::getSingleton()->characoterColl(oldPos, newPos, TownPlayerAction::collR, &newPos, 3);
        setPosition(newPos);
        vec = newPos - oldPos;
        TownActionCalculate::getIdxByVec(idx, vec);
        setDir(idx);
    }
    moveData_.counter++;
}

void twn::TownCharacterBase::checkMoveColl(dss::Fix32Vector3& pos1, dss::Fix32Vector3& pos2, dss::Fix32& ret, dss::Fix32& min)
{
    dss::Fix32 temp = ret;
    if (TownStageManager::getSingleton()->getCrossPolyNo(pos1, pos2, &temp, true) != -1 && temp < min) {
        min = temp;
        ret = temp;
        if (ret <= TownPlayerAction::townCharaPreR) {
            moveData_.vector[3].vz.value = 0;
            moveData_.vector[3].vy.value = 0;
        } else {
            moveData_.vector[3].vy = (ret - TownPlayerAction::townCharaPreR) / moveData_.speed;
            moveData_.vector[3].vz.value = moveData_.vector[3].vy.value / 0x1000;
        }
    }
}

void twn::TownCharacterBase::execAreaMove()
{
    if (moveData_.counter == 0x50) {
        moveData_.counter = 0;
    }
    static const dss::Fix32 Len((fx32)0x2800);
    if (moveData_.counter == 0) {
        unsigned char param = UnkDssRand::rand(4);
        short dir = TownActionCalculate::getIdxByParam(param);
        setDir(dir);
        moveData_.vector[3].vx.value = dir;
        moveData_.vector[2] = TownActionCalculate::getParamVec(param);
        data_.flag.remove(0x200);
        if (stageColl_ & 1) {
            data_.flag.set(0x200);
            moveData_.vector[3].vz.value = 0x23;
            dss::Fix32Vector3 add;
            int rParam = param - 1;
            if (rParam < 0) {
                rParam = 3;
            }
            add = TownActionCalculate::getParamVec(rParam);
            dss::Fix32Vector3 pos1 = getPosition() + add * TownPlayerAction::collR;
            dss::Fix32Vector3 pos2 = pos1 + moveData_.vector[2] * (moveData_.speed * 0x28 + TownPlayerAction::townCharaPreR);
            pos1.vy += TownPlayerAction::collR;
            pos2.vy += TownPlayerAction::collR;
            dss::Fix32 retLen = Len;
            dss::Fix32 tempLen = Len;
            checkMoveColl(pos1, pos2, retLen, tempLen);
            rParam = param + 1;
            if (rParam > 3) {
                rParam = 0;
            }
            add = TownActionCalculate::getParamVec(rParam);
            pos1 = getPosition() + add * TownPlayerAction::collR;
            pos2 = pos1 + moveData_.vector[2] * (moveData_.speed * 0x28 + TownPlayerAction::townCharaPreR);
            pos1.vy += TownPlayerAction::collR;
            pos2.vy += pos1.vy;
            checkMoveColl(pos1, pos2, retLen, tempLen);
            pos1 = getPosition();
            pos2 = pos1 + moveData_.vector[2] * (moveData_.speed * 0x28 + TownPlayerAction::townCharaPreR);
            pos1.vy += TownPlayerAction::collR;
            pos2.vy = pos1.vy;
            checkMoveColl(pos1, pos2, retLen, tempLen);
        }
        moveData_.vector[2] *= moveData_.speed;
    }
    if (moveData_.counter < 0x23) {
        dss::Fix32Vector3 oldPos = getPosition();
        dss::Fix32Vector3 newPos = oldPos + moveData_.vector[2];
        if (moveData_.vector[0].vx > newPos.vx || moveData_.vector[0].vz > newPos.vz || moveData_.vector[1].vx < newPos.vx || moveData_.vector[1].vz < newPos.vz) {
            moveData_.counter++;
            return;
        }
        if (data_.flag.check(0x200) && moveData_.counter >= moveData_.vector[3].vz.value) {
            moveData_.counter++;
            return;
        }
        if ((areaCheck_ == true && data_.flag.check(1) == true) || areaCheck_ == false) {
            dss::Fix32Vector3 vec1 = TownPlayerManager::getSingleton().getPosition() - newPos;
            if (vec1.lengthsq().value < (TownPlayerAction::townCharaR * TownPlayerAction::townCharaR * 4).value + 0x190) {
                dss::Fix32Vector3 vec2 = moveData_.vector[2];
                dss::Fix32 dot = vec1 * vec2;
                if (dot > dss::Fix32(0L)) {
                    moveData_.counter++;
                    return;
                }
            }
        }
        if (stageColl_ & 2) {
            TownStageManager::getSingleton()->characoterColl(oldPos, newPos, TownPlayerAction::collR, &newPos, 2);
        }
        setPosition(newPos);
        if (stageColl_ & 4) {
            if (TownCharacterManager::getSingleton()->charaToCharaColl(this, 0, 0) == true) {
                setPosition(oldPos);
                moveData_.counter++;
                return;
            }
        }
        if (!data_.flag.check(8)) {
            setDir(moveData_.vector[3].vx.value);
        }
    }
    moveData_.counter++;
}

void twn::TownCharacterBase::execRootMove()
{
}

void twn::TownCharacterBase::setMoveToParty()
{
    moveType_ = MOVE_TYPE_TO_PARTY;
    dss::Fix32Vector3 unused;
    switch (script_.num[0]) {
    case 0:
        moveType_ = MOVE_TYPE_NONE;
        return;
    case 1:
        script_.node[2] = script_.node[1];
        script_.node[1].vz = script_.node[0].vz;
        break;
    case 2:
        script_.node[2] = script_.node[1];
        script_.node[1].vx = script_.node[0].vx;
        break;
    default:
        moveType_ = MOVE_TYPE_NONE;
        return;
    }
    dss::Fix32 len1 = (script_.node[1] - script_.node[0]).length();
    dss::Fix32 len2 = (script_.node[2] - script_.node[1]).length();
    int frame = script_.frame;
    script_.num[1] = ((len2 / (len1 + len2)).value * frame) / 0x1000;
    script_.frame = ((len1 / (len1 + len2)).value * frame) / 0x1000;
}

void twn::TownCharacterBase::setNextMoveToParty()
{
    script_.node[1] = script_.node[2];
    script_.node[0] = data_.position;
    script_.frame = script_.num[1];
    script_.counter = 0;
    moveType_ = MOVE_TYPE_NONE;
}

void twn::TownCharacterBase::setSimpleMove()
{
    if (moveType_ != MOVE_TYPE_TO_PARTY) {
        moveType_ = MOVE_TYPE_SIMPLE_MOVE;
    }
    simpleMove_.setActionMove(script_.node[0], script_.node[1]);
    simpleMove_.setMoveFrame(script_.frame);
    short idx = getDir();
    dss::Fix32Vector3 dirVec = script_.node[1] - script_.node[0];
    TownActionCalculate::getIdxByVec(idx, dirVec);
    moveIdx_ = idx;
}

void twn::TownCharacterBase::setSimpleRot(short idx, int frame, int mode)
{
    data_.flag.set(0x10);
    dss::Vector3<short> start;
    dss::Vector3<short> end;
    start.set(0, 0, 0);
    end.set(0, 0, 0);
    start.vy = getDir();
    end.vy = idx;
    simpleMove_.setActionRot(start, end);
    simpleMove_.setRotFrame(frame, mode);
}

void twn::TownCharacterBase::setJumpMove(dss::Fix32Vector3 target, int frame)
{
    moveType_ = MOVE_TYPE_JUMP;
    dss::Fix32Vector3 pos = getPosition();
    simpleMove_.setJumpMove(pos, target, frame);
    script_.isEnd = false;
}

void twn::TownCharacterBase::jumpMove()
{
    dss::Fix32Vector3 pos = getPosition();
    simpleMove_.execMove(pos);
    if (simpleMove_.moveUpdate() == true) {
        moveType_ = MOVE_TYPE_NONE;
        script_.isEnd = true;
    }
    setPosition(pos);
}

void twn::TownCharacterBase::setLockRot(int flag)
{
    if (flag == true) {
        data_.flag.set(8);
    } else {
        data_.flag.remove(8);
    }
}

void twn::TownCharacterBase::setPosing(int pose)
{
    if (pose == data_.charaIndex) {
        restorePose();
    } else {
        changePose(pose);
    }
}

void twn::TownCharacterBase::setMotion(int motion, bool flag)
{
}

bool twn::TownCharacterBase::isMotion()
{
    return false;
}

void twn::TownCharacterBase::setMovePassive()
{
    static const dss::Fix32 passiveSpeed((fx32)0x19a);
    moveType_ = MOVE_TYPE_PASSIVE;
    moveData_.frame = 0;
    moveData_.counter = 0;
    moveData_.speed = passiveSpeed;
}

void twn::TownCharacterBase::setPassiveRetPos(dss::Fix32Vector3& retPos, dss::Fix32Vector3& playerPos, dss::Fix32Vector3& vec)
{
    int polyNo = -1;
    dss::Fix32 len;
    dss::Fix32Vector3 target;
    if (vec * (retPos - playerPos) >= dss::Fix32(0L)) {
        len = moveData_.speed;
        target = retPos + vec * (TownPlayerAction::collR + len);
        if (TownStageManager::getSingleton()->getCrossPolygonOtherSurface(retPos, target, 0, 0, polyNo, 0, false) <= 0) {
            retPos += vec * len;
            return;
        }
        vec *= -1;
        target = retPos + vec * (TownPlayerAction::collR + len);
        if (TownStageManager::getSingleton()->getCrossPolygonOtherSurface(retPos, target, 0, 0, polyNo, 0, false) <= 0) {
            retPos += vec * len;
        }
    } else {
        vec *= -1;
        len = moveData_.speed;
        target = retPos + vec * (TownPlayerAction::collR + len);
        if (TownStageManager::getSingleton()->getCrossPolygonOtherSurface(retPos, target, 0, 0, polyNo, 0, false) <= 0) {
            retPos += vec * len;
            return;
        }
        vec *= -1;
        target = retPos + vec * (TownPlayerAction::collR + len);
        if (TownStageManager::getSingleton()->getCrossPolygonOtherSurface(retPos, target, 0, 0, polyNo, 0, false) <= 0) {
            retPos += vec * len;
        }
    }
}

void twn::TownCharacterBase::execMovePassive()
{
    if (areaCheck_ == true && data_.flag.check(1) == true) {
        dss::Fix32Vector3 nowPos = getPosition();
        dss::Fix32Vector3 playerPos = cmn::g_cmnPartyInfo.position_;
        dss::Fix32Vector3 vec = nowPos - playerPos;
        vec.vy = 0L;
        if (dss::abs<long>(vec.vy.value) > TownPlayerAction::townCharaR.value) {
            return;
        }
        if (vec.lengthsq() <= TownPlayerAction::townCharaR * TownPlayerAction::townCharaR * 4 || type_ == 1 || type_ == 3) {
            moveData_.counter++;
            int counter = moveData_.counter;
            if (counter % 0x28 > 0x14) {
                return;
            }
            if (counter % 2 != 0) {
                return;
            }
            if (TownPlayerManager::getSingleton().player_.townActionWalk_.moveFlag_ == 0) {
                return;
            }
            dss::Fix32Vector3 prevPlayerPos = cmn::g_cmnPartyInfo.prev_position_;
            short idx = getDir();
            TownActionCalculate::getIdxByVec(idx, vec);
            unsigned char dir = TownActionCalculate::getParamDir4ByIdx(idx);
            vec = TownActionCalculate::getParamVec(dir);
            if (type_ == 0) {
                setDir(idx);
            }
            dss::Fix32Vector3 nextPos = nowPos + vec * moveData_.speed;
            dss::Fix32Vector3 retPos;
            dss::Fix32 r = TownPlayerAction::collR;
            if (type_ == 1) {
                r = TownPlayerAction::collR * 3 / 2;
            }
            int ret = TownStageManager::getSingleton()->characoterColl(nowPos, nextPos, r, &retPos, 3);
            bool wall = false;
            if (retPos.vx != nextPos.vx || retPos.vz != nextPos.vz) {
                wall = true;
                COLL_POLY coll;
                if (TownStageManager::getSingleton()->getCollPolyByPolyNo(ret, &coll)) {
                    vec = FldStage::getFx32Vector3(coll.bbox[0]) - FldStage::getFx32Vector3(coll.bbox[1]);
                    vec.vy = 0L;
                    vec.normalize();
                    setPassiveRetPos(retPos, playerPos, vec);
                    vec = retPos - playerPos;
                    vec.vy = 0L;
                    if (vec.lengthsq() <= TownPlayerAction::collR * TownPlayerAction::collR * 4) {
                        return;
                    }
                }
            }
            setPosition(retPos);
            dss::Fix32 llen1;
            dss::Fix32 llen2;
            int no1 = -1;
            int no2 = -1;
            if (TownCharacterManager::getSingleton()->charaToCharaColl(this, &llen1, &no1) == true) {
                if (wall == false) {
                    short tdir = dir - 1;
                    if (tdir < 0) {
                        tdir = 3;
                    }
                    vec = TownActionCalculate::getParamVec(tdir);
                    setPassiveRetPos(retPos, playerPos, vec);
                    vec = retPos - playerPos;
                    vec.vy = 0L;
                    if (vec.lengthsq() <= TownPlayerAction::collR * TownPlayerAction::collR * 4) {
                        setPosition(nowPos);
                        return;
                    }
                    setPosition(retPos);
                    if (TownCharacterManager::getSingleton()->charaToCharaColl(this, &llen2, &no2) == true) {
                        if (!(llen1 < llen2) || no1 != no2) {
                            setPosition(nowPos);
                            return;
                        }
                    }
                } else {
                    setPosition(nowPos);
                    return;
                }
            }
            if (TownExtraCollManager::getSingleton().checkInArea(retPos) == true) {
                setPosition(nowPos);
                return;
            }
            if (type_ == 1) {
                TownExtraCollManager::getSingleton().addMoveColl(data_.ctrlNo, type_, nowPos, retPos);
            }
        }
    }
}

void twn::TownCharacterBase::setMoveReverse()
{
    moveType_ = MOVE_TYPE_REVESE;
    moveData_.speed = TownPlayerAction::walkSpeed / 4;
}

void twn::TownCharacterBase::execMoveReverse()
{
    dss::Fix32Vector3 playerPos = cmn::g_cmnPartyInfo.position_;
    dss::Fix32Vector3 prevPlayerPos = cmn::g_cmnPartyInfo.prev_position_;
    if (playerPos == prevPlayerPos) {
        return;
    }
    dss::Fix32Vector3 vec = playerPos - prevPlayerPos;
    vec.normalize();
    int dir = TownActionCalculate::getParamDir4ByIdx(getDir());
    switch (dir) {
    case 0:
    case 2:
        vec.vz *= -1;
        break;
    case 1:
    case 3:
        vec.vx *= -1;
        break;
    }
    dss::Fix32Vector3 nowPos = getPosition();
    dss::Fix32Vector3 nextPos = nowPos + vec * moveData_.speed;
    dss::Fix32Vector3 retPos;
    moveData_.counter++;
    if (checkPlayerColl(nextPos) == true) {
        return;
    }
    TownStageManager::getSingleton()->characoterColl(nowPos, nextPos, TownPlayerAction::collR, &retPos, 3);
    if (TownCharacterManager::getSingleton()->charaToCharaColl(this, 0, 0) == true || retPos.vx != nextPos.vx || retPos.vz != nextPos.vz) {
        setPosition(nowPos);
        return;
    }
    setPosition(retPos);
}

void twn::TownCharacterBase::setMoveRandom()
{
    moveType_ = MOVE_TYPE_RANDOM;
    moveData_.frame = 0;
    moveData_.counter = 0;
    moveData_.speed = TownPlayerAction::walkSpeed / 4;
}

void twn::TownCharacterBase::execMoveRandom()
{
    switch (moveData_.counter) {
    case -1: {
        dss::Fix32Vector3 playerPos = cmn::g_cmnPartyInfo.position_;
        dss::Fix32Vector3 prevPlayerPos = cmn::g_cmnPartyInfo.prev_position_;
        if (playerPos != prevPlayerPos) {
            moveData_.counter++;
        }
        return;
    }
    case 0x1e:
        moveData_.counter = -1;
        return;
    }
    if (moveData_.counter == 0) {
        short dir = UnkDssRand::rand(4) << 14;
        if (data_.flag.check(8) == false) {
            setDir(dir);
        }
        moveData_.vector[3].vx.value = dir;
        TownActionCalculate::getDirByIdx(dir, moveData_.vector[2]);
        moveData_.vector[2].normalize();
        moveData_.vector[2] *= moveData_.speed;
    }
    dss::Fix32Vector3 nowPos = getPosition();
    dss::Fix32Vector3 nextPos = nowPos + moveData_.vector[2];
    dss::Fix32Vector3 retPos;
    moveData_.counter++;
    if (checkPlayerColl(nextPos) == true) {
        return;
    }
    TownStageManager::getSingleton()->characoterColl(nowPos, nextPos, TownPlayerAction::collR, &retPos, 3);
    if (TownCharacterManager::getSingleton()->charaToCharaColl(this, 0, 0) == true || retPos.vx != nextPos.vx || retPos.vz != nextPos.vz) {
        setPosition(nowPos);
        return;
    }
    setPosition(retPos);
}

bool twn::TownCharacterBase::checkPlayerColl(dss::Fix32Vector3& newPos)
{
    dss::Fix32Vector3 vec1 = TownPlayerManager::getSingleton().getPosition() - newPos;
    if (vec1.lengthsq() < TownPlayerAction::townCharaR * TownPlayerAction::townCharaR * 4) {
        dss::Fix32Vector3 vec2 = moveData_.vector[2];
        vec2.normalize();
        vec1.normalize();
        dss::Fix32 dot = vec1 * vec2;
        if (dot > dss::Fix32(0L)) {
            return true;
        }
    }
    return false;
}

void twn::TownCharacterBase::setSwingRoundIdx()
{
    if (data_.flag.check(0x40) == false) {
        swingIdx_ = getDir();
    }
    data_.flag.set(0x40);
}

void twn::TownCharacterBase::setFadeType(int type, int frame)
{
    alphaCounter_ = 0;
    alphaFrame_ = frame;
    changeAlphaType_ = type;
    blinkCounter_ = 0;
    alphaMax_ = 0x1f;
    switch (changeAlphaType_) {
    case 2:
    case 3:
        setDisplay(true);
        setAlpha(0);
        break;
    default:
        alphaMax_ = getAlpha();
        break;
    }
}

bool twn::TownCharacterBase::isEndFade()
{
    return changeAlphaType_ == 0;
}

void twn::TownCharacterBase::setChangePaletteRate(dss::Fix32Vector3& rate, int frame)
{
    rgbChangeType_ = 0;
    addRGB = (rate - setRGB) / frame;
    rgbFrame_ = frame;
}

void twn::TownCharacterBase::setChangePaletteRate(unsigned char r, unsigned char g, unsigned char b, int frame)
{
    rgbChangeType_ = 1;
    setRGB.vx.value = r << 12;
    setRGB.vy.value = g << 12;
    setRGB.vz.value = b << 12;
    rgbFrame_ = frame;
    rgbFrameMax_ = rgbFrame_;
}

bool twn::TownCharacterBase::isEndPalletRate()
{
    return rgbFrame_ == -1;
}

void twn::TownCharacterBase::setPersonalEventLock(bool flag)
{
    if (flag == true) {
        data_.flag.set(0x80);
    } else {
        data_.flag.remove(0x80);
    }
}

void twn::TownCharacterBase::setMonsterSpeak(int flag)
{
    if (flag == true) {
        data_.flag.set(0x100);
    } else {
        data_.flag.remove(0x100);
    }
}

void twn::TownCharacterBase::setMoveBigRock()
{
}

void twn::TownCharacterBase::execMoveBigRock()
{
}

void twn::TownCharacterBase::setMapUid(int uid)
{
}

void twn::TownCharacterBase::resetTalk()
{
    data_.flag.remove(2);
    data_.flag.remove(1);
    data_.flag.remove(4);
    if (data_.flag.check(0x4000)) {
        syncroType_ = SYNCHRONOUS_NONE;
    }
}

bool twn::TownCharacterBase::getSpeak()
{
    return data_.flag.check(1);
}

void twn::TownCharacterBase::setSpeak(bool flag)
{
    if (flag == true) {
        data_.flag.set(1);
    } else {
        data_.flag.remove(1);
    }
}

bool twn::TownCharacterBase::getTalked()
{
    return data_.flag.check(2);
}

void twn::TownCharacterBase::setTalked(bool flag)
{
    if (flag == true) {
        data_.flag.set(2);
    } else {
        data_.flag.remove(2);
    }
}

void twn::TownCharacterBase::setCounterTalk(bool flag)
{
    if (flag == true) {
        data_.flag.set(4);
    } else {
        data_.flag.remove(4);
    }
}

bool twn::TownCharacterBase::getCounterTalk()
{
    return data_.flag.check(4);
}

bool twn::TownCharacterBase::isRotEnd()
{
    return !data_.flag.check(0x10);
}

void twn::TownCharacterBase::setSwingRound(int flag)
{
    if (flag == true) {
        data_.flag.set(0x20);
    } else {
        data_.flag.remove(0x20);
    }
}

void twn::TownCharacterBase::execMoveWait()
{
    waitCounter_--;
}

void twn::TownCharacterBase::setRotFrame(int frame, short idx, int flag, int typeA)
{
    data_.flag.set(0x10);
    dss::Vector3<short> start(0, getDir(), 0);
    if (flag == 0) {
        idx = -idx;
    }
    dss::Vector3<short> rot(0, idx, 0);
    simpleMove_.setSimpleRot(start, rot, frame);
    if (typeA == true) {
        data_.flag.set(0x400);
    }
}

bool twn::TownCharacterBase::isRotFrameEnd()
{
    if (data_.flag.check(0x400) == true) {
        data_.flag.remove(0x400);
        return true;
    }
    return isRotEnd();
}

void twn::TownCharacterBase::setVoice(int voice)
{
    if (voice == 0x39) {
        data_.flag.remove(0x800);
    } else {
        data_.flag.set(0x800);
        voice_ = voice;
    }
}

bool twn::TownCharacterBase::checkVoice()
{
    return data_.flag.check(0x800);
}

int twn::TownCharacterBase::getVoice()
{
    return voice_;
}

void twn::TownCharacterBase::setPaletteRate(unsigned char r, unsigned char g, unsigned char b, dss::Fix32 rate)
{
}

void twn::TownCharacterBase::setPalletRate(dss::Fix32 rate)
{
}

void twn::TownCharacterBase::setObjectMove(int uid, dss::Fix32Vector3& offset, int type)
{
    script_.num[3] = uid;
    script_.node[3] = offset;
    moveType_ = MOVE_TYPE_MAP_OBJ;
    switch (type) {
    case 0:
        data_.flag.set(0x1000);
        break;
    case 1:
        data_.flag.set(0x2000);
        break;
    case 2:
        data_.flag.remove(0x1000);
        data_.flag.remove(0x2000);
        break;
    }
}

void twn::TownCharacterBase::mapObjMove()
{
    dss::Fix32Vector3 oldPos = getPosition();
    dss::Fix32Vector3 pos = TownStageManager::getSingleton()->getMapUidPos(script_.num[3]);
    pos += script_.node[3];
    setPosition(pos);
    if (data_.flag.check(0x1000)) {
        short idx = getDir();
        dss::Fix32Vector3 vec = pos - oldPos;
        TownActionCalculate::getIdxByVec(idx, vec);
        setDir(idx);
    }
    if (data_.flag.check(0x2000)) {
        dss::Fix32Vector3 rot = TownStageManager::getSingleton()->getMapUidRot(script_.num[3]);
        setDir(rot.vy.value);
    }
}

void twn::TownCharacterBase::setSynchronous(int flag, int no)
{
    if (flag == true) {
        syncroNo_ = no;
        data_.flag.set(0x4000);
    } else {
        data_.flag.remove(0x4000);
    }
}

void twn::TownCharacterBase::setSyncroPos()
{
    if (syncroType_ == SYNCHRONOUS_MOVE) {
        setPosition(syncroPos_);
        simpleMove_.moveCounter_--;
        simpleMove_.actionFlag_.set(1);
    } else {
        syncroType_ = SYNCHRONOUS_STOP;
    }
}

void twn::TownCharacterBase::setMotionLock(int flag)
{
    if (flag == true) {
        data_.flag.set(0x8000);
    } else {
        data_.flag.remove(0x8000);
    }
}

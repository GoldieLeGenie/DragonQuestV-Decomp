#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownExtraCollManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/status/StageInfo.hpp"
#include <nitro/fx/fx_atan.h>

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::CharaData::getType()
{
    return (byte_1 & 0x1c) >> 2;
}

inline char dq5::level::CharaData::getAnim()
{
    return (byte_1 & 0xe0) >> 5;
}

inline void dq5::level::CharaData::setType(char type)
{
    byte_1 &= ~0x1c;
    byte_1 += type << 2;
}

inline int twn::TownCharacterBase::getCharaType()
{
    return type_;
}

inline int twn::TownCharacterBase::getCharaIndex()
{
    return data_.charaIndex;
}

inline dss::Fix32Vector3& twn::TownCharacterBase::getPosition()
{
    return data_.position;
}

inline bool twn::TownStageManager::checkObectIn(int objectId, dss::Fix32Vector3& pos)
{
    return stage_.getObjectIn(objectId, pos);
}

const dss::Fix32 TownCharacterManager::defaultSpeed(0x66);

THUMB TownCharacterManager::TownCharacterManager()
{
}

THUMB TownCharacterManager* TownCharacterManager::getSingleton()
{
    static TownCharacterManager m_singleton;
    return &m_singleton;
}

THUMB TownCharacterManager::~TownCharacterManager()
{
}

THUMB void TownCharacterManager::initialize()
{
    characterStorage.initialize();
    twn::TownCharacterBase::areaCheck_ = 0;
}

THUMB void TownCharacterManager::terminate()
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            cleanup(i);
        }
    }
    characterStorage.terminate();
}

THUMB void TownCharacterManager::execute()
{
    getDisplayFrame();
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->execute();
        }
    }
    twn::TownCharacterBase::areaCheck_ = 0;
    resetCharaTalk();
}

THUMB int TownCharacterManager::setup(TOWN_CHARACTER& chara)
{
    int result = -1;
    int charaparam = dq5::level::g_LevelDataUtility.getCharaParamIndex(chara.charaIndex);
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] == 0) {
            if (dq5::level::CharaData::getRecord(charaparam)->getType() == 3 && dq5::level::CharaData::getRecord(charaparam)->getAnim() == 1) {
                dq5::level::CharaData::getRecord(charaparam)->setType(4);
            }
            character_[i] = characterStorage.getContainer(dq5::level::CharaData::getRecord(charaparam)->getType());
            character_[i]->charaParamIndex_ = charaparam;
            character_[i]->render_ = &twn::TownSystem::getSingleton().townSystemRender_;
            character_[i]->cmr_ = &TownCamera::getSingleton()->camera_.unk_004;
            character_[i]->setup(chara);
            character_[i]->type_ = dq5::level::CharaData::getRecord(charaparam)->getType() == 1 ? 0 : dq5::level::CharaData::getRecord(charaparam)->getType();
            character_[i]->data_.ctrlNo = i;
            character_[i]->setMonsterSpeak(twn::TownCharacterBase::monsterTalk_);
            if (status::g_StageInfo.sepiaFlag_ && dq5::level::CharaData::getRecord(charaparam)->getType() == 1) {
                character_[i]->setHueChange(1, 1);
            }
            result = i;
            break;
        }
    }
    townCharacterCount_++;
    int drawType = character_[result]->getCharaType();
    if (drawType == 2 || drawType == 3 || drawType == 4) {
        twn::TownExtraCollManager::getSingleton().addCharacterColl(result, drawType);
    }
    return result;
}

THUMB void TownCharacterManager::draw()
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->draw();
        }
    }
}

THUMB void TownCharacterManager::requestCharacterReload()
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->requestReload();
        }
    }
}

THUMB void TownCharacterManager::setPosing(int index, int pose)
{
    character_[index]->setPosing(pose);
}

THUMB bool TownCharacterManager::isCharacterEnable(int index)
{
    if (character_[index]) {
        return true;
    }
    return false;
}

THUMB void TownCharacterManager::cleanup(int index)
{
    townCharacterCount_--;
    if (character_[index]->getCharaType() == 0) {
        characterStorage.restoreContainer(1);
    } else {
        characterStorage.restoreContainer(character_[index]->getCharaType());
    }
    character_[index]->cleanup();
    character_[index]->data_.enable = 0;
    character_[index] = 0;
}

THUMB void TownCharacterManager::setPlayerDirection(int index)
{
    dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().getPosition());
    dss::Fix32Vector3 target(getPosition(index));
    dss::Fix32Vector3 dir = pos - target;
    dir.normalize();
    character_[index]->setSwingRoundIdx();
    setRotate(index, FX_Atan2Idx(dir.vx.value, dir.vz.value));
}

THUMB dss::Fix32Vector3& TownCharacterManager::getPosition(int index)
{
    return character_[index]->getPosition();
}

THUMB void TownCharacterManager::setRotate(int index, int dir)
{
    character_[index]->setDir(dir);
}

THUMB void TownCharacterManager::setRotate(int index, dss::Vector3<short>& rot)
{
    character_[index]->setRotation(rot);
}

THUMB void TownCharacterManager::setTalkedArea(int index, bool flag)
{
    character_[index]->setSpeak(flag);
}

THUMB void TownCharacterManager::setTalked(int index, bool flag)
{
    character_[index]->setTalked(flag);
}

THUMB bool TownCharacterManager::isTalked(int index)
{
    return character_[index]->getTalked();
}

THUMB void TownCharacterManager::setShadow(int index, int flag)
{
    character_[index]->setShadow(flag);
}

THUMB void TownCharacterManager::setAnimation(int index, int flag)
{
    character_[index]->setAnimation(flag);
}

THUMB void TownCharacterManager::setWriggleCharacter(int index, int flag)
{
    character_[index]->setWriggleCharacter(flag);
}

THUMB void TownCharacterManager::setNearCharacter(int index, int flag)
{
    character_[index]->setNearCharacter(flag);
}

THUMB void TownCharacterManager::setDisplay(int index, int flag)
{
    character_[index]->setDisplay(flag);
    character_[index]->setCollFlag(flag);
    int type = character_[index]->getCharaType();
    switch (type) {
    case 2:
    case 3:
        if (flag == 1) {
            twn::TownExtraCollManager::getSingleton().addCharacterColl(index, type);
        } else {
            twn::TownExtraCollManager::getSingleton().resetCharaColl(index, 2);
        }
        break;
    case 1:
        if (flag == 1) {
            twn::TownExtraCollManager::getSingleton().addCharacterColl(index, 1);
        } else {
            twn::TownExtraCollManager::getSingleton().resetCharaColl(index, 0);
        }
        break;
    }
}

THUMB void TownCharacterManager::setAlpha(int index, unsigned char alpha)
{
    character_[index]->setAlpha(alpha);
}

THUMB void TownCharacterManager::setPosition(int index, dss::Fix32Vector3& pos)
{
    character_[index]->setPosition(pos);
}

THUMB void TownCharacterManager::setSleepCharacter(int index, int flag)
{
    if (flag == 1) {
        if (character_[index]->getCharaType() != 1 && character_[index]->getCollFlag() == 1 && character_[index]->isDisplay() == 1) {
            twn::TownExtraCollManager::getSingleton().addSleepChara(index);
        }
    } else {
        if (character_[index]->getCharaType() == 1 && character_[index]->getCollFlag() == 1) {
            twn::TownExtraCollManager::getSingleton().resetCharaColl(index, 0);
        }
    }
    character_[index]->setMonsterSpeak(flag);
    character_[index]->setSleepCharacter(flag);
}

THUMB void TownCharacterManager::setCollFlag(int index, int flag)
{
    if (flag == 1) {
        if (character_[index]->getCharaType() == 1 && character_[index]->getCollFlag() == 0) {
            twn::TownExtraCollManager::getSingleton().addSleepChara(index);
        } else {
            twn::TownCharacterBase* p = character_[index];
            if (p->getCharaType() == 2) {
                twn::TownExtraCollManager::getSingleton().addCharacterColl(index, p->getCharaIndex());
            }
        }
    } else {
        if (character_[index]->getCharaType() == 1 && character_[index]->getCollFlag() == 1) {
            twn::TownExtraCollManager::getSingleton().resetCharaColl(index, 0);
        } else if (character_[index]->getCharaType() == 2) {
            twn::TownExtraCollManager::getSingleton().resetCharaColl(index, 2);
        }
    }
    character_[index]->setCollFlag(flag);
}

THUMB int TownCharacterManager::getDirection(int index)
{
    return character_[index]->getDir();
}

THUMB void TownCharacterManager::resetCharaTalk()
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->resetTalk();
        }
    }
}

THUMB bool TownCharacterManager::checkCollision(dss::Fix32Vector3& pos, dss::Fix32 rr)
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->isDisplay()) {
            if ((character_[i]->getPosition() - pos).lengthsq() <= rr) {
                return true;
            }
        }
    }
    return false;
}

THUMB bool TownCharacterManager::charaToCharaColl(twn::TownCharacterBase* chara, dss::Fix32* llen, int* no)
{
    dss::Fix32Vector3 vec;
    dss::Fix32 RR = twn::TownPlayerAction::collR * twn::TownPlayerAction::collR * 4;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && (character_[i]->stageColl_ & 4) && character_[i] != chara && character_[i]->isDisplay() == 1) {
            vec = character_[i]->getPosition() - chara->getPosition();
            if (!(vec.vy > 1L)) {
                vec.vy = 0L;
                if (vec.lengthsq() <= RR) {
                    if (llen) {
                        *llen = vec.lengthsq();
                    }
                    if (no) {
                        *no = i;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

THUMB void TownCharacterManager::characterColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 r)
{
    dss::Fix32Vector3 vec;
    twn::TownCharacterBase::areaCheck_ = 1;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->isDisplay()) {
            dss::Fix32Vector3& target = character_[i]->getPosition();
            vec = target - nowPos;
            if (dss::abs<long>(vec.vx.value) <= 0x1000 && dss::abs<long>(vec.vz.value) <= 0x1000 && dss::abs<long>(vec.vy.value) <= 0x1000) {
                vec.vy = 0L;
                if (vec.lengthsq() <= twn::TownPlayerAction::talkRR) {
                    character_[i]->setSpeak(1);
                }
                if (character_[i]->getCollFlag() && character_[i]->getSpeak() && character_[i]->getCharaType() != 1) {
                    twn::TownActionCalculate::crossCheck(nowPos, nextPos, target, r);
                }
            }
        }
    }
}

THUMB bool TownCharacterManager::checkFarTalk(dss::Fix32Vector3& pos, dss::Fix32Vector3& vecN, dss::Fix32 ctrLen, int polyNo, bool farTalk)
{
    dss::Fix32 len(0x800);
    dss::Fix32Vector3 vec;
    bool ret = false;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->isDisplay()) {
            dss::Fix32Vector3& target = character_[i]->getPosition();
            vec = target - pos;
            if (polyNo != -1) {
                if (twn::TownStageManager::getSingleton()->isPolyFacePosition(polyNo, target, len) == 1) {
                    dss::Fix32Vector3 normal;
                    twn::TownStageManager::getSingleton()->getPolyDirection(normal, polyNo);
                    vec.normalize();
                    if ((vec * normal).value > 0xddb) {
                        character_[i]->setSpeak(1);
                        character_[i]->setCounterTalk(1);
                        ret = true;
                    }
                }
            }
            if (farTalk == 1) {
                if (vec.lengthsq() <= ctrLen * ctrLen) {
                    vec.normalize();
                    if ((vec * vecN).value > 0xddb) {
                        character_[i]->setSpeak(1);
                        character_[i]->setCounterTalk(1);
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}

THUMB bool TownCharacterManager::checkTalkingNearCharacter(dss::Fix32Vector3& pos, short dirIdx, int searchObject)
{
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 tempPos;
    dss::Fix32 tempDot;
    dss::Fix32 dot;
    twn::TownActionCalculate::getDirByIdx(dirIdx, playerDir);
    int charNo = -1;
    dot.value = 0xb50;
    dss::Fix32 tempLen2;
    tempLen2.value = 0x7fffffff;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->getSpeak()) {
            target = character_[i]->getPosition();
            vec = target - pos;
            vec.vy = 0L;
            if (vec.lengthsq() < tempLen2) {
                dss::Fix32Vector3 tvec(vec);
                tvec.normalize();
                tempDot = tvec * playerDir;
                if (dot < tempDot) {
                    charNo = i;
                    tempLen2 = vec.lengthsq();
                    tempPos = target;
                }
            }
        }
    }
    if (charNo != -1) {
        switch (character_[charNo]->getCharaIndex()) {
        case 0x57:
        case 0x5a:
        case 0x5b:
        case 0x8c:
            return false;
        }
        dss::Fix32 retLen;
        if (character_[charNo]->getCounterTalk() == 1 || character_[charNo]->getCharaType() == 1) {
            if (twn::TownStageManager::getSingleton()->checkCrossNum(pos, tempPos, 1) == 0) {
                character_[charNo]->setCounterTalk(0);
            }
            character_[charNo]->setTalked(1);
            return true;
        } else if (twn::TownStageManager::getSingleton()->checkCrossNumCheckUnder(pos, tempPos, 1) == 0) {
            character_[charNo]->setTalked(1);
            return true;
        }
    }
    return false;
}

THUMB void TownCharacterManager::setCharaAnim(int index, short count)
{
    character_[index]->setAnimation(1);
    character_[index]->animCounter_ = count;
}

THUMB void TownCharacterManager::eventLockAllChraraAnim()
{
    BillboardCharacter::setAllCharaAnim(false);
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->setAnimation(2);
        }
    }
}

THUMB int TownCharacterManager::getCharaIndex(int index)
{
    if (character_[index]) {
        return character_[index]->getCharaIndex();
    }
    return -1;
}

THUMB void TownCharacterManager::restoreCharacterAnim()
{
    BillboardCharacter::setAllCharaAnim(true);
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->setAnimation(1);
        }
    }
}

THUMB void TownCharacterManager::setAllEventLock(bool flag)
{
    twn::TownCharacterBase::allEventLock_ = flag;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i]) {
            character_[i]->setPersonalEventLock(flag);
        }
    }
}

THUMB void TownCharacterManager::setSpecCharaAlpha(int charIndex, unsigned char alpha)
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->getCharaIndex() == charIndex) {
            character_[i]->setAlpha(alpha);
        }
    }
}

THUMB void TownCharacterManager::setSpecCleanup(int charIndex)
{
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->getCharaIndex() == charIndex) {
            cleanup(i);
        }
    }
}

THUMB void TownCharacterManager::setCopyPlayerChara(int index, dss::Fix32Vector3& pos, short idx, int charNo)
{
    if (character_[index]) {
        character_[index]->setPosition(pos);
        character_[index]->setDir(idx);
        character_[index]->changePose(charNo);
        character_[index]->setDisplay(1);
    }
}

THUMB bool TownCharacterManager::checkIkadaTalk(dss::Fix32Vector3& target, dss::Fix32Vector3& playerDir)
{
    int charNo = -1;
    dss::Fix32Vector3 vec;
    dss::Fix32 farTargetsq = twn::TownPlayerAction::collR * twn::TownPlayerAction::collR * 3;
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->isDisplay()) {
            vec = target - character_[i]->getPosition();
            vec.vy = 0L;
            dss::Fix32Vector3 tvec(vec);
            tvec.normalize();
            if (vec.lengthsq() < farTargetsq) {
                farTargetsq = vec.lengthsq();
                charNo = i;
            }
        }
    }
    if (charNo != -1) {
        character_[charNo]->setSpeak(1);
        character_[charNo]->setCounterTalk(1);
        character_[charNo]->setTalked(1);
        return true;
    }
    return false;
}

THUMB void TownCharacterManager::checkObjectInTalk(int objectId)
{
    dss::Fix32 one(0x2400);
    for (int i = 0; i < TOWN_CHARACTER_MAX; i++) {
        if (character_[i] && character_[i]->isDisplay()) {
            if (twn::TownStageManager::getSingleton()->checkObectIn(objectId, character_[i]->getPosition()) == 1) {
                if ((character_[i]->getPosition() - twn::TownPlayerManager::getSingleton().getPosition()).lengthsq() < one) {
                    character_[i]->setSpeak(1);
                    character_[i]->setCounterTalk(1);
                }
            }
        }
    }
}

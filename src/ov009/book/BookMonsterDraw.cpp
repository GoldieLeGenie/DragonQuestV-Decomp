#pragma ipa file
#include "ov009/book/BookMonsterDraw.hpp"
#include "ov009/book/BookCamera.hpp"
#include "ov009/book/BookSystem.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "main/sound/SoundManager.hpp"
#include "nitro/pad.h"

namespace book {
    static void setCamera(dss::Camera* camera);
}

#pragma thumb on

inline UnkPaletteAnimationObject::UnkPaletteAnimationObject() : texture_(0) {}
inline UnkPaletteAnimation::~UnkPaletteAnimation() {}
inline unsigned int ExcelBinaryData::getRecordCount() { return record_; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::MonsterData::getIndex() { return index; }
inline unsigned short dq5::level::MonsterData::getAction1() { return action1; }
inline unsigned short dq5::level::MonsterData::getAction2() { return action2; }
inline unsigned short dq5::level::MonsterData::getAction3() { return action3; }
inline unsigned short dq5::level::MonsterData::getAction4() { return action4; }
inline unsigned short dq5::level::MonsterData::getAction5() { return action5; }
inline unsigned short dq5::level::MonsterData::getAction6() { return action6; }
inline unsigned short dq5::level::MonsterData::getAnimIndex() { return animIndex; }
inline unsigned char dq5::level::MonsterData::getAnim1() { return anim1; }
inline unsigned char dq5::level::MonsterData::getAnim2() { return anim2; }
inline unsigned char dq5::level::MonsterData::getAnim3() { return anim3; }
inline unsigned char dq5::level::MonsterData::getAnim4() { return anim4; }
inline unsigned char dq5::level::MonsterData::getAnim5() { return anim5; }
inline unsigned char dq5::level::MonsterData::getAnim6() { return anim6; }
inline dq5::level::MonsterAnim* dq5::level::MonsterAnim::getRecord(int index) { return (MonsterAnim*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::MonsterAnim::getArraySize() { return binary_.getRecordCount(); }
inline unsigned short dq5::level::MonsterAnim::getIndex() { return index; }
inline unsigned short dq5::level::MonsterAnim::getAction() { return action; }
inline unsigned short dq5::level::MonsterAnim::getSound() { return sound; }
inline unsigned short dq5::level::MonsterAnim::getEffect() { return effect; }
inline unsigned char dq5::level::MonsterAnim::getAnim() { return anim; }
inline unsigned char dq5::level::MonsterAnim::getAnimfile() { return animfile; }
inline unsigned char dq5::level::MonsterAnim::getStartframe() { return startframe; }
inline fx32 dq5::level::MonsterAnim::getScale() { return scale; }
inline char dq5::level::MonsterAnim::getDisplay() { return byte_1 & 0xF; }
inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index) { return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::EffectParam::getArraySize() { return binary_.getRecordCount(); }
inline unsigned short dq5::level::EffectParam::getIndex() { return index; }
inline unsigned short dq5::level::EffectParam::getSound() { return sound; }
inline char dq5::level::EffectParam::getWay() { return (byte_1 & 0x6) >> 1; }
inline int DSSACharacter::getAnimation() { return currentAnimationIndex_; }
inline dss::Camera& book::BookCamera::getCamera() { return getSingleton().camera_; }

book::BookMonsterDraw::BookMonsterDraw()
{
}

book::BookMonsterDraw::~BookMonsterDraw()
{
}

book::BookMonsterDraw& book::BookMonsterDraw::getSingleton()
{
    static BookMonsterDraw bookSystem;
    return bookSystem;
}

void book::BookMonsterDraw::initialize()
{
    system_ = &BookSystem::getSingleton();
}

void book::BookMonsterDraw::terminate()
{
    if (effect_.isEnable()) {
        cleanupEffect();
    }
    resource_.terminate();
    cleanup();
}

void book::BookMonsterDraw::setup(int index)
{
    if (character_.dssaCharacterData_ != NULL) {
        cleanup();
    }
    dss::Fix32Vector3 position;
    character_.setup(index);
    character_.setPosition(position);
    character_.setCameraType(DSSAObjectWithCamera::Normal);
    setCamera(&BookCamera::getSingleton().getCamera());
    monster_ = dq5::level::MonsterData::getRecord(index);
    unsigned short tempAction[6];
    unsigned short tempAnim[6];
    tempAction[0] = monster_->getAction1();
    tempAction[1] = monster_->getAction2();
    tempAction[2] = monster_->getAction3();
    tempAction[3] = monster_->getAction4();
    tempAction[4] = monster_->getAction5();
    tempAction[5] = monster_->getAction6();
    tempAnim[0] = monster_->getAnim1();
    tempAnim[1] = monster_->getAnim2();
    tempAnim[2] = monster_->getAnim3();
    tempAnim[3] = monster_->getAnim4();
    tempAnim[4] = monster_->getAnim5();
    tempAnim[5] = monster_->getAnim6();
    bool findAnim = false;
    int count = 0;
    for (int i = 0; i < 6; i++) {
        anim_[i] = 0xffff;
        action_[i] = 0xffff;
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (tempAnim[i] == anim_[j]) {
                findAnim = true;
            }
        }
        if (!findAnim) {
            anim_[count] = tempAnim[i];
            action_[count] = tempAction[i];
            count++;
        }
        findAnim = false;
    }
    animIndexCount_ = count;
    actionIndex_ = 0;
    defaultAnimation_ = character_.getAnimation();
    resource_.initialize();
    wait_ = 0;
    counter_ = 0;
}

/* file-local copy of the inline DSSACharacter::setCamera: mwld would merge a weak one with ov001's */
ARM static void book::setCamera(dss::Camera* camera)
{
    DSSAObjectWithCamera::camera_ = camera;
}

THUMB void book::BookMonsterDraw::cleanup()
{
    UnkCharacterPalette* palette = &character_.palette_;
    if (palette->enable_) {
        paletteAnim_.unkfunc_02051648();
        palette->enable_ = 0;
        dataObject_.cleanup();
    }
    if (effect_.isEnable()) {
        cleanupEffect();
    }
    character_.cleanup();
}

void book::BookMonsterDraw::execute()
{
    if (counter_ < 30) {
        counter_++;
        return;
    }
    if (!isActivate()) {
        if ((dss::g_Pad.edge() & PAD_BUTTON_A) || (dss::g_Pad.edge() & PAD_BUTTON_X)) {
            startAnimation(actionIndex_);
            actionIndex_++;
        }
    }
    if (effect_.isEnable() && effect_.isEnd()) {
        cleanupEffect();
    }
    if (actionIndex_ >= animIndexCount_) {
        actionIndex_ = 0;
    }
}

void book::BookMonsterDraw::draw()
{
    if (effect_.isEnable()) {
        if (wait_ != 0) {
            wait_--;
        }
    }
    if (unkfunc_0204ccd0() & 1) {
        if (effect_.isEnable() && wait_ == 0) {
            effect_.draw();
        }
        character_.draw();
    }
}

void book::BookMonsterDraw::startAnimation(int animIndex)
{
    int index = getMonsterAnimIndex(monster_->getIndex(), action_[animIndex], anim_[animIndex]);
    if (index < 0) {
        return;
    }
    int currentAnimation = dq5::level::MonsterAnim::getRecord(index)->getAnimfile();
    if (currentAnimation >= 14) {
        return;
    }
    character_.start(currentAnimation, false);
    SoundManager::playSe(dq5::level::MonsterAnim::getRecord(index)->getSound(), 0);
    setPaletteAnim(currentAnimation);
    setupEffect(index);
}

bool book::BookMonsterDraw::isActivate()
{
    if (effect_.isEnable()) {
        return true;
    }
    if (defaultAnimation_ != character_.getAnimation()) {
        return true;
    }
    return false;
}

void book::BookMonsterDraw::setPaletteAnim(int animNo)
{
}

void book::BookMonsterDraw::setupEffect(int index)
{
    int paramIndex;
    char path[128];
    effectID_ = dq5::level::MonsterAnim::getRecord(index)->getEffect();
    if (effectID_ == 0xd9) {
        return;
    }
    for (int i = 0; i < dq5::level::EffectParam::getArraySize(); i++) {
        if (effectID_ == dq5::level::EffectParam::getRecord(i)->getIndex()) {
            paramIndex = i;
            break;
        }
    }
    wait_ = dq5::level::MonsterAnim::getRecord(index)->getStartframe();
    dss::sprintf_s(path, sizeof(path), "data/effect/effect%03d.lz", effectID_);
    if (!dss::g_File.isExist(path, dss::File::Switching)) {
        return;
    }
    effect_.addEffect(resource_.getResource(effectID_), 1);
    if (cmn::CommonEffectData::isSecondEffect(effectID_)) {
        effect_.addEffect(resource_.getResource(effectID_ + 10000), 1);
    }
    dss::Fix32Vector3 pos;
    if (dq5::level::MonsterAnim::getRecord(index)->getDisplay() <= 3) {
        pos = *character_.getPosition() - character_.getNullPosition(1, dq5::level::MonsterAnim::getRecord(index)->getDisplay());
    } else {
        pos = *character_.getPosition() - character_.getNullPosition(dq5::level::MonsterAnim::getRecord(index)->getAnimfile(), dq5::level::MonsterAnim::getRecord(index)->getDisplay());
    }
    effect_.setPosition(pos);
    effect_.setScale(dss::Fix32(dq5::level::MonsterAnim::getRecord(index)->getScale()));
    effect_.setDisplayType(dq5::level::EffectParam::getRecord(paramIndex)->getWay(), 0);
    effect_.setDisplayType(dq5::level::EffectParam::getRecord(paramIndex)->getWay(), 1);
    effect_.start();
    SoundManager::playSe(dq5::level::EffectParam::getRecord(paramIndex)->getSound(), 0);
}

void book::BookMonsterDraw::cleanupEffect()
{
    effect_.cleanup(1);
    resource_.restoreResource(effectID_);
    if (cmn::CommonEffectData::isSecondEffect(effectID_)) {
        resource_.restoreResource(effectID_ + 10000);
    }
}

int book::BookMonsterDraw::getMonsterAnimIndex(unsigned short monsterId, unsigned short actionId, unsigned short animId)
{
    int index = dq5::level::MonsterData::getRecord(monsterId)->getAnimIndex();
    for (int i = index; i < dq5::level::MonsterAnim::getArraySize(); i++) {
        if (dq5::level::MonsterAnim::getRecord(i)->getAction() == actionId && dq5::level::MonsterAnim::getRecord(i)->getAnim() == animId) {
            return i;
        }
        if (dq5::level::MonsterAnim::getRecord(i)->getIndex() != monsterId && dq5::level::MonsterAnim::getRecord(i)->getIndex() != 0) {
            return 0;
        }
    }
    return 0;
}

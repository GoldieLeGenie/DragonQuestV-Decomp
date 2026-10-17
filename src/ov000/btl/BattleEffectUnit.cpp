#include "ov000/btl/BattleEffectUnit.hpp"
#include "ov000/btl/BattleCamera.hpp"
#include "ov000/btl/BattleEffectGroup.hpp"
#include "ov000/btl/BattleEffectStorage.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/cmn/CommonEffectResource.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "nitro/os.hpp"

inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index) { return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline char dq5::level::ActionParam::getDirect() { return byte_6 & 0x7; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::EffectParam::getIndex() { return index; }
inline unsigned short dq5::level::EffectParam::getFrame() { return frame; }
inline unsigned short dq5::level::EffectParam::getHoming() { return homing; }
inline unsigned short dq5::level::EffectParam::getSound() { return sound; }
inline unsigned short dq5::level::EffectParam::getCamera() { return camera; }
inline unsigned short dq5::level::EffectParam::getCamera2() { return camera2; }
inline unsigned char dq5::level::EffectParam::getInterval() { return interval; }
inline unsigned char dq5::level::EffectParam::getColor() { return color; }
inline unsigned char dq5::level::EffectParam::getHold() { return hold; }
inline unsigned char dq5::level::EffectParam::getWait() { return wait; }
inline char dq5::level::EffectParam::getFailed() { return byte_1 & 0x1; }
inline char dq5::level::EffectParam::getWay() { return (byte_1 & 0x6) >> 1; }
inline char dq5::level::EffectParam::getDisplay() { return (byte_1 & 0x78) >> 3; }
inline char dq5::level::EffectParam::getFlicker() { return byte_2 & 0xf; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline dss::Fix32Vector3 btl::BattleMonster::getPosition() { return *monsterDraw_.getPosition(); }
inline dss::Fix32Vector3 btl::BattleMonster::getNullPosition(int index, int no) { return monsterDraw_.getNullPosition(index, no); }
inline bool btl::BattleMonster::isAirMonster() { return flag_.check(FLAG_AIR_MONSTER); }
inline void btl::BattleCameraHoming::start() { step_ = STEP_START; }
inline void btl::BattleCamera::setRotateTime(int time) { homing_.setRotateTime(time); }
inline void btl::BattleCamera::setWaitTime(int time) { homing_.setWaitTime(time); }
inline void btl::BattleCamera::setHomingStart() { homing_.start(); }

cmn::CommonEffectResource* btl::BattleEffectUnit::resource_;
btl::BattleEffectStorage* btl::BattleEffectUnit::storage_;

THUMB btl::BattleEffectUnit::BattleEffectUnit()
{
}

THUMB btl::BattleEffectUnit::~BattleEffectUnit()
{
}

THUMB void btl::BattleEffectUnit::setControlData(BattleEffectStorage* storage, cmn::CommonEffectResource* resource)
{
    storage_ = storage;
    resource_ = resource;
}

THUMB void btl::BattleEffectUnit::initialize()
{
    effect_ = -1;
    start_ = false;
    upper_ = true;
    max_ = 0;
    process_ = 0;
    pass_ = 0;
    frame_ = 0;
    for (int i = 0; i < MAX_CONTAINER; i++) {
        group_[i] = 0;
    }
}

THUMB void btl::BattleEffectUnit::terminate()
{
    for (int i = 0; i < MAX_CONTAINER; i++) {
        if (group_[i] != 0 && group_[i]->isEnable()) {
            cleanupEffectGroup(i);
        }
    }
}

THUMB void btl::BattleEffectUnit::setTarget(status::UseActionParam& useActionParam)
{
    if (effect_ < 0) {
        return;
    }
    max_ = 0;
    bool flag = true;
    if ((unsigned int)(useActionParam.getActionIndex() - 0x53) <= 2) {
        flag = false;
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getInterval() != 0 && flag == true) {
        for (int i = 0; i < useActionParam.getTargetCount(); i++) {
            if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getDirect() == 4 &&
                useActionParam.getTargetCharacterStatus(i)->getCharacterType() == PLAYER) {
                continue;
            }
            if (result_[i]) {
                if (useActionParam.getTargetCharacterStatus(i)->getHaveStatusInfo().isMosyasExec()) {
                    upper_ = false;
                }
                setEffectPosition(max_, useActionParam.getTargetCharacterStatus(i)->getHaveStatusInfo().getDrawCtrlId(), 1);
                max_++;
            }
            else {
                dss::Fix32Vector3 position(0, -0x80000, 0);
                targetPos_[max_] = position;
                max_++;
            }
        }
    }
    else {
        max_ = 1;
        status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
        if (actor->getCharacterType() == MONSTER) {
            if (useActionParam.getTargetCharacterStatus(0)->getCharacterType() == PLAYER) {
                if (actor->getHaveStatusInfo().isMosyasExec()) {
                    upper_ = false;
                }
                setEffectPosition(0, useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId(), 1);
            }
            else {
                if (useActionParam.getTargetCharacterStatus(0)->getHaveStatusInfo().isMosyasExec()) {
                    upper_ = false;
                }
                setEffectPosition(0, useActionParam.getTargetCharacterStatus(0)->getHaveStatusInfo().getDrawCtrlId(), 1);
            }
        }
        else {
            if (useActionParam.getTargetCharacterStatus(0)->getHaveStatusInfo().isMosyasExec()) {
                upper_ = false;
            }
            setEffectPosition(0, useActionParam.getTargetCharacterStatus(0)->getHaveStatusInfo().getDrawCtrlId(), 1);
        }
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getHoming() != 0 && max_ == 1) {
        BattleCamera::getSingleton()->setRotateTime(dq5::level::EffectParam::getRecord(effect_)->getHoming());
        BattleCamera::getSingleton()->setWaitTime(dq5::level::EffectParam::getRecord(effect_)->getHold());
        BattleCamera::getSingleton()->setHomingTarget(useActionParam.getTargetCharacterStatus(0)->getHaveStatusInfo().getDrawCtrlId());
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getWay() == 2) {
        shufflePosition();
    }
    upper_ = true;
}

THUMB void btl::BattleEffectUnit::setTarget(status::CharacterStatus* actor, int anim)
{
    if (effect_ < 0) {
        return;
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getFailed()) {
        return;
    }
    max_ = 1;
    if (actor->getHaveStatusInfo().isMosyasExec()) {
        upper_ = false;
    }
    setEffectPosition(0, actor->getHaveStatusInfo().getDrawCtrlId(), anim);
    if (dq5::level::EffectParam::getRecord(effect_)->getHoming() != 0 && max_ == 1) {
        BattleCamera::getSingleton()->setRotateTime(dq5::level::EffectParam::getRecord(effect_)->getHoming());
        BattleCamera::getSingleton()->setWaitTime(dq5::level::EffectParam::getRecord(effect_)->getHold());
        BattleCamera::getSingleton()->setHomingTarget(actor->getHaveStatusInfo().getDrawCtrlId());
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getWay() == 2) {
        shufflePosition();
    }
    upper_ = true;
}

THUMB void btl::BattleEffectUnit::setSpecialTarget(int ctrlID, int anim)
{
    if (effect_ < 0) {
        return;
    }
    max_ = 1;
    setEffectPosition(0, ctrlID, anim);
}

THUMB void btl::BattleEffectUnit::setup(int effect)
{
    char filename[128];
    effect_ = effect;
    dss::sprintf_s(filename, sizeof(filename), "data/effect/effect%03d.lz", dq5::level::EffectParam::getRecord(effect_)->getIndex());
    if (!dss::g_File.isExist(filename, dss::File::Switching)) {
        effect_ = -1;
        return;
    }
    for (int i = 0; i < MAX_CONTAINER; i++) {
        result_[i] = true;
    }
    start_ = false;
    frame_ = 0;
    process_ = 0;
    pass_ = 0;
    hit_ = 0;
}

THUMB void btl::BattleEffectUnit::cleanup()
{
    effect_ = -1;
    start_ = false;
    for (int i = 0; i < MAX_CONTAINER; i++) {
        group_[i] = 0;
    }
}

THUMB void btl::BattleEffectUnit::setEffectPosition(int index, int monsterIndex, int anim)
{
    if (monsterIndex < 0) {
        monsterIndex = 0;
    }
    BattleMonster& monster = BattleMonsterDraw2::getSingleton().getMonster(monsterIndex);
    if (dq5::level::EffectParam::getRecord(effect_)->getDisplay() == 0) {
        dss::Fix32Vector3 position(0, 0, 0);
        targetPos_[index] = position;
        if (dq5::level::EffectParam::getRecord(effect_)->getWay() == 3 && monster.isAirMonster() && upper_) {
            targetPos_[index].vy.value = 0xc000;
        }
    }
    else if (dq5::level::EffectParam::getRecord(effect_)->getDisplay() <= 3) {
        targetPos_[index] = monster.getPosition() - monster.getNullPosition(1, dq5::level::EffectParam::getRecord(effect_)->getDisplay());
    }
    else {
        targetPos_[index] = monster.getPosition() - monster.getNullPosition(anim, dq5::level::EffectParam::getRecord(effect_)->getDisplay());
    }
    if (dq5::level::EffectParam::getRecord(effect_)->getFlicker() != 0) {
        int x = UnkDssRand::rand(dq5::level::EffectParam::getRecord(effect_)->getFlicker() << 8) - (dq5::level::EffectParam::getRecord(effect_)->getFlicker() << 7);
        int y = UnkDssRand::rand(dq5::level::EffectParam::getRecord(effect_)->getFlicker() << 8) - (dq5::level::EffectParam::getRecord(effect_)->getFlicker() << 7);
        targetPos_[index].vx.value += x;
        targetPos_[index].vy.value += y;
    }
    targetPos_[index].vz.value += 0x100;
}

THUMB void btl::BattleEffectUnit::shufflePosition()
{
    if (max_ > 1) {
        for (int i = 0; i < 16; i++) {
            int a = UnkDssRand::rand(max_);
            int b = UnkDssRand::rand(max_);
            dss::Fix32Vector3 position(targetPos_[a]);
            targetPos_[a] = targetPos_[b];
            targetPos_[b] = position;
        }
    }
}

THUMB void btl::BattleEffectUnit::setupEffectGroup(int index)
{
    char filename[128];
    dss::sprintf_s(filename, sizeof(filename), "data/effect/effect%03d.lz", dq5::level::EffectParam::getRecord(effect_)->getIndex());
    if (!dss::g_File.isExist(filename, dss::File::Switching)) {
        return;
    }
    cmn::CommonEffectData* data = resource_->getResource(dq5::level::EffectParam::getRecord(effect_)->getIndex());
    group_[index] = storage_->getContainer();
    BattleEffectGroup* group = group_[index];
    if (resource_->getRefCounter(dq5::level::EffectParam::getRecord(effect_)->getIndex()) == 1) {
        group->addEffect(data, true);
    }
    else {
        group->addEffect(data, false);
    }
    if (cmn::CommonEffectData::isSecondEffect(dq5::level::EffectParam::getRecord(effect_)->getIndex())) {
        cmn::CommonEffectData* second = resource_->getResource(dq5::level::EffectParam::getRecord(effect_)->getIndex() + 10000);
        if (resource_->getRefCounter(dq5::level::EffectParam::getRecord(effect_)->getIndex() + 10000) != 0) {
            group->addEffect(second, true);
        }
        else {
            group->addEffect(second, false);
        }
    }
    group->setPosition(targetPos_[index]);
    group->setDisplayType(dq5::level::EffectParam::getRecord(effect_)->getWay(), 0);
    group->setDisplayType(dq5::level::EffectParam::getRecord(effect_)->getWay(), 1);
    group->setScale(dss::Fix32(dq5::level::EffectParam::getRecord(effect_)->scale));
}

THUMB void btl::BattleEffectUnit::cleanupEffectGroup(int index)
{
    if (resource_->getRefCounter(dq5::level::EffectParam::getRecord(effect_)->getIndex()) == 1) {
        group_[index]->cleanup(true);
    }
    else {
        group_[index]->cleanup(false);
    }
    group_[index] = 0;
    pass_++;
    storage_->restoreContainer();
    resource_->restoreResource(dq5::level::EffectParam::getRecord(effect_)->getIndex());
    if (cmn::CommonEffectData::isSecondEffect(dq5::level::EffectParam::getRecord(effect_)->getIndex())) {
        resource_->restoreResource(dq5::level::EffectParam::getRecord(effect_)->getIndex() + 10000);
    }
}

THUMB void btl::BattleEffectUnit::draw()
{
    if (start_) {
        for (int i = pass_; i < max_; i++) {
            group_[i]->draw();
        }
    }
}

THUMB void btl::BattleEffectUnit::extraDraw()
{
    if (start_) {
        for (int i = pass_; i < max_; i++) {
            group_[i]->extraDraw();
        }
    }
}

THUMB void btl::BattleEffectUnit::waitStart()
{
    if (effect_ < 0 || start_) {
        return;
    }
    {
        if (frame_ == 0) {
            if (storage_->getContainerStock() >= max_ && resource_->getResourceStock() >= 2) {
                start_ = true;
                if (dq5::level::EffectParam::getRecord(effect_)->getColor() != 0) {
                    if (max_ == 0) {
                        cmn::CommonEffectLocation::getSingleton().start(dq5::level::EffectParam::getRecord(effect_)->getColor(), 0);
                    }
                    else {
                        int interval = dq5::level::EffectParam::getRecord(effect_)->getInterval();
                        cmn::CommonEffectLocation::getSingleton().start(dq5::level::EffectParam::getRecord(effect_)->getColor(), (max_ - 1) * interval);
                    }
                }
                OS_Wait();
                for (int i = 0; i < max_; i++) {
                    setupEffectGroup(i);
                }
                if (dq5::level::EffectParam::getRecord(effect_)->getCamera() != 0 || dq5::level::EffectParam::getRecord(effect_)->getCamera2() != 0) {
                    unsigned short camera = dq5::level::EffectParam::getRecord(effect_)->getCamera();
                    unsigned short camera2 = dq5::level::EffectParam::getRecord(effect_)->getCamera2();
                    BattleCamera::getSingleton()->setCameraAnimation(camera, camera2, dq5::level::EffectParam::getRecord(effect_)->getWait());
                }
                if (dq5::level::EffectParam::getRecord(effect_)->getHoming() != 0 && max_ == 1) {
                    BattleCamera::getSingleton()->setHomingStart();
                }
            }
        }
        else {
            frame_++;
        }
    }
}

THUMB void btl::BattleEffectUnit::execute()
{
    waitStart();
    if (!start_) {
        return;
    }
    if (max_ == 0) {
        cleanup();
        return;
    }
    if (frame_ % dq5::level::EffectParam::getRecord(effect_)->getInterval() == 0 && process_ < max_) {
        group_[process_]->start();
        if (result_[process_]) {
            SoundManager::playSe(dq5::level::EffectParam::getRecord(effect_)->getSound(), 0);
        }
        process_++;
    }
    int interval = dq5::level::EffectParam::getRecord(effect_)->getInterval();
    if ((frame_ - hit_ * interval) % dq5::level::EffectParam::getRecord(effect_)->getFrame() == 0 && hit_ < max_) {
        hit_++;
    }
    for (int i = pass_; i < process_; i++) {
        if (group_[i]->isEnable() && group_[i]->isEnd()) {
            cleanupEffectGroup(i);
        }
    }
    if (process_ == max_ && pass_ == max_) {
        if (frame_ >= dq5::level::EffectParam::getRecord(effect_)->getFrame() + max_ * dq5::level::EffectParam::getRecord(effect_)->getInterval()) {
            cleanup();
        }
    }
    frame_++;
}

THUMB int btl::BattleEffectUnit::getHitFrame()
{
    return dq5::level::EffectParam::getRecord(effect_)->getFrame();
}

THUMB bool btl::BattleEffectUnit::isEnable()
{
    return effect_ >= 0;
}

THUMB void btl::BattleEffectUnit::setWaitTime(int time)
{
    if (time < 0) {
        time = 0;
    }
    frame_ = -time;
}

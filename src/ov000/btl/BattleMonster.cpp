#include "ov000/btl/BattleMonster.hpp"
#include "ov000/btl/BattleCamera.hpp"
#include "ov000/btl/MonsterAnimInfo.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "main/sound/SoundManager.hpp"
#include <printf.h>

inline PaletteAnimationObject::PaletteAnimationObject() : texture_(0) {}
inline dq5::level::MonsterAnim* dq5::level::MonsterAnim::getRecord(int index) { return (MonsterAnim*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::MonsterAnim::getAnimfile() { return animfile; }
inline void DSSACharacter::setTransOfEnd() { flag_.set(0x20); }
inline void DSSACharacter::setNextAnimationIndex(int index)
{
    firstAnimationIndex_ = index;
    nextAnimationIndex_ = index;
}

THUMB btl::BattleMonster::BattleMonster() : monsterGroup_(0), monsterIndex_(-1)
{
    flag_.clear();
}

THUMB void btl::BattleMonster::setup(int monsterGroup, int monsterIndex)
{
    flag_.clear();
    monsterGroup_ = monsterGroup;
    monsterIndex_ = monsterIndex;
    monsterDraw_.setup(monsterIndex_);
    monsterDraw_.setCurrentFrame(0, UnkDssRand::rand(30));
    screenPosition_ = 0;
    screenWidth_ = 0;
    animationFlag_ = 0;
    flag_.set(FLAG_ENABLE);
    monsterDraw_.setCameraType(DSSAObjectWithCamera::Near2);
}

THUMB void btl::BattleMonster::cleanup()
{
    CharacterPalette* palette = &monsterDraw_.palette_;
    if (palette->enable_) {
        paletteAnimation_.unkfunc_02051648();
        palette->enable_ = 0;
        dataObject_.cleanup();
    }
    monsterIndex_ = -1;
    monsterDraw_.cleanup();
    screenPosition_ = 0;
    screenWidth_ = 0;
    flag_.clear();
}

THUMB void btl::BattleMonster::setPosition(const dss::Fix32Vector3& position)
{
    monsterDraw_.setPosition(position);
}

THUMB void btl::BattleMonster::draw()
{
    CharacterPalette* palette = &monsterDraw_.palette_;
    if (palette->enable_ && !paletteAnimation_.unkfunc_02051628()) {
        paletteAnimation_.unkfunc_02051580(palette->address_, palette->size_);
    }
    if (monsterDraw_.currentAnimationIndex_ != 0) {
        dss::Fix32Vector3 pos = *monsterDraw_.getPosition();
        pos.vz.value += 0x100;
        monsterDraw_.setPosition(pos);
        monsterDraw_.draw();
        pos.vz.value -= 0x100;
        monsterDraw_.setPosition(pos);
    } else {
        monsterDraw_.draw();
    }
}

THUMB void btl::BattleMonster::startAnimation(int actionIndex, int animIndex)
{
    if (actionIndex == 0x1e2) {
        actionIndex = 0x47;
    }
    if (actionIndex == 0x49 || actionIndex == 0x4a) {
        monsterDraw_.start(0xe, 0);
        monsterDraw_.setNextAnimationIndex(0xf);
        return;
    }
    if (actionIndex == 0x3f) {
        monsterDraw_.setTransOfEnd();
    }
    if (actionIndex == 0x52) {
        monsterDraw_.setTransOfEnd();
    }
    if (animIndex == 0x22) {
        monsterDraw_.start(0x22, 0);
    } else if (animIndex == 0x23) {
        monsterDraw_.start(0x23, 0);
    } else if (animIndex == 0x20) {
        monsterDraw_.start(0x20, 0);
    } else if (animIndex == 0x1f) {
        if (actionIndex == 0x48) {
            monsterDraw_.start(0x1f, 0);
        }
        if (actionIndex == 0) {
            monsterDraw_.start(0x1f, 0);
        }
    } else {
        int anim = getMonsterAnimIndex(monsterIndex_, actionIndex, animIndex);
        int animNo;
        SoundManager::playSe(dq5::level::MonsterAnim::getRecord(anim)->sound, 0);
        if (anim < 0) {
            animNo = 0x1e;
        } else {
            setCameraAnimation(anim);
            animNo = dq5::level::MonsterAnim::getRecord(anim)->getAnimfile();
        }
        monsterDraw_.start(animNo, 0);
        setPaletteAnim(animNo);
    }
}

THUMB void btl::BattleMonster::startMosyasAnimation(int monsterId, int actionId)
{
    int anim = getMonsterAnimIndex(monsterId, actionId);
    int animNo;
    SoundManager::playSe(dq5::level::MonsterAnim::getRecord(anim)->sound, 0);
    if (anim < 0) {
        animNo = 0x1e;
    } else {
        setCameraAnimation(anim);
        animNo = dq5::level::MonsterAnim::getRecord(anim)->getAnimfile();
    }
    monsterDraw_.start(animNo, 0);
    setPaletteAnim(animNo);
}

THUMB bool btl::BattleMonster::isLastFrame()
{
    if (monsterDraw_.getCurrentFrame() == monsterDraw_.getMaxFrame() - 1) {
        return true;
    }
    return false;
}

THUMB void btl::BattleMonster::setCameraAnimation(int index)
{
    dq5::level::MonsterAnim* anim = dq5::level::MonsterAnim::getRecord(index);
    BattleCamera::getSingleton()->setCameraAnimation(anim->camera, anim->camera2, anim->wait);
}

THUMB void btl::BattleMonster::startAnimation(int animIndex)
{
    monsterDraw_.start(animIndex, 0);
}

THUMB void btl::BattleMonster::startAnimationWithLoop(int animIndex, int flag)
{
    monsterDraw_.start(animIndex, flag);
}

THUMB bool btl::BattleMonster::startGattai()
{
    if (monsterIndex_ == 0x6a && monsterDraw_.currentAnimationIndex_ != 9) {
        monsterDraw_.start(9, 0);
        dss::Fix32Vector3 pos(0, 0, 0);
        monsterDraw_.setPosition(pos);
        return true;
    }
    return false;
}

THUMB void btl::BattleMonster::disappearGattaiSlime()
{
    if (monsterIndex_ == 0x6a) {
        monsterDraw_.start(0x26, 1);
    }
}

THUMB bool btl::BattleMonster::isAppearKingSlime2()
{
    if (monsterIndex_ == 0x6a && monsterDraw_.currentAnimationIndex_ == 9 && monsterDraw_.getCurrentFrame() == monsterDraw_.getMaxFrame() - 1) {
        return true;
    }
    return false;
}

THUMB void btl::BattleMonster::setPaletteAnim(int animNo)
{
}

THUMB void btl::BattleMonster::setPaletteAstoron(int flag)
{
    CharacterPalette* palette = &monsterDraw_.palette_;
    if (palette->enable_) {
        paletteAnimation_.unkfunc_02051648();
        dataObject_.cleanup();
        palette->enable_ = 0;
    }
    char filename[128];
    if (flag) {
        sprintf(filename, "data/pam/m%03ds.pam", monsterIndex_);
    } else {
        sprintf(filename, "data/pam/m%03dl.pam", monsterIndex_);
    }
    if (dss::g_File.isExist(filename, dss::File::Switching)) {
        dataObject_.setup(filename, 1, 0);
        palette->enable_ = 1;
        paletteAnimation_.anim_.setup(dataObject_.getAddr());
        paletteAnimation_.unkfunc_0205150c(palette->address_, palette->size_);
    }
}

THUMB void btl::BattleMonster::setTransOfEnd()
{
    monsterDraw_.setTransOfEnd();
}

THUMB void btl::BattleMonster::setNextAnimationIndex(int index)
{
    monsterDraw_.setNextAnimationIndex(index);
}

#include "main/dss/DssVectorDefault.hpp"

#include "main/window/ScreenEffectManager.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/cmn/NonBattleActionManager.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/UnkMenuOverlay.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

inline bool window::UnkScreenEffect::isSetup()
{
    return (flag_ & FLAG_SETUP) ? true : false;
}

inline void fld::FieldData::pause(int flag)
{
    pause_ = flag;
}

inline void cmn::CommonParticleEmitter::pause(bool flag)
{
    stop_ = flag;
}

inline void fld::FieldStage::pause(int flag)
{
    fieldData.pause(flag);
    cmn::CommonParticleEmitter::getSingleton()->pause(flag);
}

int window::ScreenEffectManager::travelFlag_;
window::ScreenEffectManager window::gScreenEffect;

THUMB void window::ScreenEffectManager::initialize()
{
    effectMode_ = PLAY_BACK_NONE;
    effect_ = NULL;
    soundCounter_ = 0;
    if (travelFlag_) {
        dss::g_DISPLAYPLUGIN_DOUBLE3D.ReqBlurMode(1);
        dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(0, 16);
        g_Global.setRanarutaFlag(true);
        cmn::NonBattleActionManager::getSingleton()->setAction(cmn::NonBattleActionManager::ACTION_TRAVELDOOR);
    }
    setupFlag_ = 0;
}

THUMB void window::ScreenEffectManager::execute()
{
    if (effect_ == NULL) {
        return;
    }
    if (soundCounter_ == 15) {
        switch (effectMode_) {
            case PLAY_BACK_TABI:
                SoundManager::playSe(0x451, 0);
                break;
            case PLAY_BACK_RANARUTA:
                SoundManager::playSe(0x23d, 0);
                break;
        }
        soundCounter_++;
    }
    soundCounter_++;
    if (effectMode_ == PLAY_BACK_TABI && tabiEffect_.travelBack_) {
        if (!effect_->isActive()) {
            g_Global.fadeOutBlack(1, true);
        } else if (!oldFlag_) {
            g_Global.fadeInBlack(60);
        }
        oldFlag_ = effect_->isActive();
    }
    effect_->execute();
}

THUMB void window::ScreenEffectManager::draw()
{
    if (effectMode_ == PLAY_BACK_CURE_FLOOR) {
        cureFloorUpdate();
        return;
    }
    if (effect_ != NULL) {
        effect_->draw();
    }
}

THUMB void window::ScreenEffectManager::terminate()
{
    if (effect_ != NULL) {
        setupFlag_ = 0;
        effect_->terminate();
        effect_ = NULL;
        soundCounter_ = 0;
    }
}

THUMB void window::ScreenEffectManager::cleanUp()
{
    if (effect_ != NULL) {
        setupFlag_ = 0;
        effect_->terminate();
        effect_ = NULL;
        if (effectMode_ == PLAY_BACK_TABI) {
            unloadWindowOverlay();
            loadWindowOverlay(1);
        }
        dss::g_DISPLAYPLUGIN_DOUBLE3D.ReqBlurMode(0);
    }
}

THUMB void window::ScreenEffectManager::effectStart(PLAY_BACK_EFFECT mode)
{
    effectMode_ = mode;
    soundCounter_ = 0;
    switch (effectMode_) {
        case PLAY_BACK_CURE_FLOOR:
            cureFloorSetup();
            break;
        case PLAY_BACK_TABI:
            effect_ = &tabiEffect_;
            effect_->setup();
            if (travelFlag_) {
                g_Global.fadeOutBlack(1, true);
                tabiEffect_.setTravelBack(true);
                travelFlag_ = false;
            }
            break;
        case PLAY_BACK_RANARUTA:
            effect_ = &ranarutaEffect_;
            effect_->setup();
            break;
        case PLAY_BACK_BATTLE:
            effect_ = &battleEffect_;
            effect_->setup();
            break;
        case PLAY_BACK_RIREMITO:
            effect_ = &riremitoEffect_;
            effect_->setup();
            break;
    }
    if (data_02101c88.isCurrentPart(4)) {
        BillboardCharacter::setAllCharaAnim(false);
    } else if (data_02101c88.isCurrentPart(6)) {
        SpriteCharacter::setAllCharaAnim(0);
    }
    setupFlag_ = 1;
}

THUMB bool window::ScreenEffectManager::isActivate()
{
    if (effect_ != NULL) {
        return effect_->isActive();
    }
    return false;
}

THUMB bool window::ScreenEffectManager::isActiveSetup()
{
    if (effect_ != NULL) {
        return effect_->isSetup();
    }
    return false;
}

THUMB bool window::ScreenEffectManager::isEnd()
{
    bool result;
    if (effect_ == NULL) {
        return true;
    }
    result = effect_->isEnd();
    if (result) {
        if (data_02101c88.isCurrentPart(4)) {
            twn::TownStageManager::getSingleton()->pause(0);
            BillboardCharacter::setAllCharaAnim(true);
        } else if (data_02101c88.isCurrentPart(6)) {
            fld::FieldStage::getSingleton()->pause(0);
            SpriteCharacter::setAllCharaAnim(1);
        }
    }
    return result;
}

THUMB void window::ScreenEffectManager::cureFloorSetup()
{
    fade_ = 0;
    data_0211b27c.state_ = FadeEffector::FADE_IN_BLACK;
    data_0211b27c.count_ = 0;
    data_0211b27c.frames_ = 30;
    data_0211b27c.sprite_[0].setColor(31, 31, 31);
    data_0211b27c.sprite_[1].setColor(31, 31, 31);
    data_02101d14.addPart(&data_0211b27c);
    twn::TownPlayerManager::getSingleton().setLock(true);
    SoundManager::playSe(0x469, 0);
}

THUMB void window::ScreenEffectManager::cureFloorUpdate()
{
    if (data_0211b27c.count_ == data_0211b27c.frames_) {
        if (!fade_) {
            switch (data_0211b27c.state_) {
                case FadeEffector::FADE_NONE:
                    data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
                    break;
                case FadeEffector::FADE_IN_BLACK:
                    data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
                    break;
                default:
                    data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
                    break;
            }
            data_0211b27c.count_ = 0;
            data_0211b27c.frames_ = 30;
            data_02101d14.addPart(&data_0211b27c);
            fade_ = 1;
            return;
        }
        SoundManager::playSe(0x1f5, 0);
        twn::TownPlayerManager::getSingleton().setLock(false);
        effectMode_ = PLAY_BACK_NONE;
    }
}

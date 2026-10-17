#include "ov001/town/shop/TownCurseSpotLight.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/status/MenuStatus.hpp"

#pragma thumb on

inline int status::MenuStatus::getCurseEffectStart()
{
    return curseEffectStart_;
}

inline void status::MenuStatus::setCurseEffectStart(bool flag)
{
    curseEffectStart_ = flag;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void twn::TownStageEffectManager::setBlindAlpha(unsigned char alpha)
{
    spotlight_.setBlindAlpha(alpha);
}

twn::TownCurseSpotLight::TownCurseSpotLight()
{
    isEnd_ = true;
    isContraction_ = false;
    size_ = 0;
    alpha_ = 0;
}

twn::TownCurseSpotLight::~TownCurseSpotLight()
{
}

twn::TownCurseSpotLight& twn::TownCurseSpotLight::getSingleton()
{
    static TownCurseSpotLight townCurseSpotLight_;
    return townCurseSpotLight_;
}

void twn::TownCurseSpotLight::setup()
{
    size_ = 0x80;
    alpha_ = 0;
    isEnd_ = false;
    isContraction_ = true;
    TownStageEffectManager::getSingleton()->setSpotlight(&TownPlayerManager::getSingleton().getPosition());
    TownStageEffectManager::getSingleton()->setLightSize(size_);
    TownStageEffectManager::getSingleton()->setLightAlpha(1);
    TownStageEffectManager::getSingleton()->setBlindAlpha(alpha_);
}

void twn::TownCurseSpotLight::execute()
{
    if (!status::g_Menu.getCurseEffectStart()) {
        return;
    }
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    if (isContraction_ == true) {
        if (alpha_ == 0) {
            TownPlayerManager::getSingleton().setLock(true);
            TownStageManager::getSingleton()->pause(1);
            BillboardCharacter::setAllCharaAnim(false);
        }
        if (size_ < 0x40) {
            cmn::g_cmnSoundManager.setPlaySound(1, false);
            isContraction_ = false;
            return;
        }
        if (alpha_ < 0x30) {
            alpha_++;
            unsigned char setAlpha = alpha_ >> 1;
            TownStageEffectManager::getSingleton()->setBlindAlpha(setAlpha);
        }
        size_--;
        TownStageEffectManager::getSingleton()->setLightSize(size_);
    } else if (size_ < 0x80) {
        if (alpha_ != 0) {
            alpha_--;
            unsigned char setAlpha = alpha_ >> 1;
            TownStageEffectManager::getSingleton()->setBlindAlpha(setAlpha);
        }
        size_++;
        TownStageEffectManager::getSingleton()->setLightSize(size_);
    } else {
        TownStageEffectManager::getSingleton()->clearTorchlight();
        status::g_Menu.setCurseEffectStart(false);
        TownPlayerManager::getSingleton().setLock(false);
        TownStageManager::getSingleton()->pause(0);
        BillboardCharacter::setAllCharaAnim(true);
        isEnd_ = true;
    }
}

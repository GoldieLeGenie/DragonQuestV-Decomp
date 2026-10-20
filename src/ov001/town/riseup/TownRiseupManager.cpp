#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov001/town/TownCamera.hpp"

int twn::TownRiseupManager::riseupCounter_;

THUMB twn::TownRiseupManager::TownRiseupManager()
{
}

THUMB twn::TownRiseupManager::~TownRiseupManager()
{
}

THUMB twn::TownRiseupManager& twn::TownRiseupManager::getSingleton()
{
    static TownRiseupManager m_singleton;
    return m_singleton;
}

THUMB void twn::TownRiseupManager::initialize()
{
    riseupStorage_.initialize();
    riseupResourece_.initialize();
    effectResourece_.initialize();
    for (int i = 0; i < RISEUP_MAX; i++) {
        riseup_[i] = NULL;
    }
    TownRiseupBase::setCamera(&TownCamera::getSingleton()->camera_.m_camera0);
    riseupCounter_ = 0;
}

THUMB void twn::TownRiseupManager::terminate()
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] != NULL) {
            cleanup(i);
        }
    }
    riseupStorage_.terminate();
    riseupResourece_.terminate();
    effectResourece_.terminate();
}

THUMB int twn::TownRiseupManager::setup(int index, dss::Fix32Vector3 position)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_BILLBOARD_ITEM);
            riseup_[i]->setResource(riseupResourece_.getResource(index));
            riseup_[i]->setup(index);
            riseup_[i]->setPosition(position);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupMedal(dss::Fix32Vector3 position)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_SPRITE_MEDAL);
            riseup_[i]->setResource(effectResourece_.getResource(SMALL_MEDAL_EFFECT));
            riseup_[i]->setup(SMALL_MEDAL_EFFECT);
            riseup_[i]->setPosition(position);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupSprite(int index, dss::Fix32Vector3 position, int near, int startFrame)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_SPRITE_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(index));
            riseup_[i]->setStartFrame(startFrame);
            riseup_[i]->setup(index);
            riseup_[i]->setPosition(position);
            riseup_[i]->setupNear(near);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupSprite2(int index, dss::Fix32Vector3 position, int near, int startFrame)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_SPRITE_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(index));
            riseup_[i]->setStartFrame(startFrame);
            riseup_[i]->setup(index);
            riseup_[i]->setPosition(position);
            riseup_[i]->setupNear2(near);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupScript(int index, dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_BILLBOARD_SCRIPT);
            riseup_[i]->setResource(riseupResourece_.getResource(index));
            riseup_[i]->setup(index);
            riseup_[i]->setScriptData(start, end, frame, 0);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupSpriteMove(int index, dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_SPRITE_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(index));
            riseup_[i]->setup(index);
            riseup_[i]->setScriptData(start, end, frame, type);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupModel(int index, dss::Fix32Vector3 position)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_MODEL_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(index));
            riseup_[i]->setPosition(position);
            riseup_[i]->setup(index);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupSpriteFade(int index, dss::Fix32Vector3 position, int frame, int flag)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_SPRITE_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(index));
            riseup_[i]->setup(index);
            riseup_[i]->setScriptFade(position, frame, flag);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB int twn::TownRiseupManager::setupExhibitIcon(int icon, dss::Fix32Vector3 position)
{
    for (int i = 0; i < RISEUP_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = riseupStorage_.getContainer(TownRiseupBase::RISEUP_BILLBOARD_EXHIBIT);
            riseup_[i]->setResource(riseupResourece_.getResource(2000));
            riseup_[i]->setup(2000);
            riseup_[i]->setPosition(position);
            riseup_[i]->setExhibitIcon(icon);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB void twn::TownRiseupManager::setFadeIn(int index, int frame)
{
    riseup_[index]->setStartFrame(frame);
}

THUMB void twn::TownRiseupManager::setFadeOut(int index, int frame)
{
    riseup_[index]->setEndFrame(frame);
}

THUMB void twn::TownRiseupManager::setPosition(int index, dss::Fix32Vector3 position)
{
    if (riseup_[index] != NULL) {
        riseup_[index]->setPosition(position);
    }
}

THUMB void twn::TownRiseupManager::cleanup(int index)
{
    riseupStorage_.restoreContainer(riseup_[index]->getType());
    if (riseup_[index]->getResorceType() == 0) {
        riseupResourece_.restoreResource(riseup_[index]->index_);
    } else {
        effectResourece_.restoreResource(riseup_[index]->index_);
    }
    riseup_[index]->cleanup();
    riseup_[index] = NULL;
    riseupCounter_--;
}

THUMB void twn::TownRiseupManager::draw()
{
    if (riseupCounter_ != 0) {
        for (int i = 0; i < RISEUP_MAX; i++) {
            if (riseup_[i] != NULL) {
                riseup_[i]->draw();
                if (riseup_[i]->enable_ == false) {
                    cleanup(i);
                }
            }
        }
    }
}

THUMB void twn::TownRiseupManager::execute()
{
    if (riseupCounter_ != 0) {
        for (int i = 0; i < RISEUP_MAX; i++) {
            if (riseup_[i] != NULL) {
                riseup_[i]->execute();
                if (riseup_[i]->enable_ == false) {
                    cleanup(i);
                }
            }
        }
    }
}

THUMB bool twn::TownRiseupManager::isFinish(int index)
{
    if (riseup_[index] == NULL) {
        return true;
    }
    return riseup_[index]->isFinish();
}

THUMB bool twn::TownRiseupManager::isEnable(int index)
{
    if (riseup_[index] != NULL) {
        return true;
    }
    return false;
}

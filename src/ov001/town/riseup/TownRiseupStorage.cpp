#include "ov001/town/riseup/TownRiseupStorage.hpp"
#include "main/dss/UnkMemory.hpp"

THUMB twn::TownRiseupStorage::TownRiseupStorage()
{
}

THUMB twn::TownRiseupStorage::~TownRiseupStorage()
{
}

THUMB void twn::TownRiseupStorage::initialize()
{
    iconCounter_ = 0;
    spriteCounter_ = 0;
    modelCounter_ = 0;
    scriptCounter_ = 0;
    exhibitCounter_ = 0;
    for (int i = 0; i < RISEUP_ICON_MAX; i++) {
        icon_[i].enable_ = false;
    }
    for (int i = 0; i < RISEUP_SPRITE_MAX; i++) {
        sprite_[i].enable_ = false;
    }
    for (int i = 0; i < RISEUP_MODEL_MAX; i++) {
        model_[i].enable_ = false;
    }
    for (int i = 0; i < RISEUP_SCRIPT_MOVE_MAX; i++) {
        script_[i].enable_ = false;
    }
    for (int i = 0; i < RISEUP_MEDAL_MAX; i++) {
        medal_[i].enable_ = false;
    }
    TownRiseupExhibit exhibit;
    exhibit_ = (TownRiseupExhibit*)dssAlloc(&data_020fd24c, sizeof(TownRiseupExhibit) * RISEUP_EXHIBIT_MAX, 0x20);
    for (unsigned int i = 0; i < RISEUP_EXHIBIT_MAX; i++) {
        dss::memcpy(&exhibit_[i], &exhibit, sizeof(TownRiseupExhibit));
        exhibit_[i].enable_ = false;
    }
}

THUMB void twn::TownRiseupStorage::terminate()
{
    dssFree(&data_020fd24c, exhibit_);
}

THUMB twn::TownRiseupBase* twn::TownRiseupStorage::getContainer(int type)
{
    switch (type) {
    case TownRiseupBase::RISEUP_BILLBOARD_ITEM:
        iconCounter_++;
        for (unsigned int i = 0; i < RISEUP_ICON_MAX; i++) {
            if (!icon_[i].enable_) {
                return &icon_[i];
            }
        }
        break;
    case TownRiseupBase::RISEUP_SPRITE_ANIM:
        spriteCounter_++;
        for (unsigned int i = 0; i < RISEUP_SPRITE_MAX; i++) {
            if (!sprite_[i].enable_) {
                return &sprite_[i];
            }
        }
        break;
    case TownRiseupBase::RISEUP_MODEL_ANIM:
        modelCounter_++;
        for (unsigned int i = 0; i < RISEUP_MODEL_MAX; i++) {
            if (!model_[i].enable_) {
                return &model_[i];
            }
        }
        break;
    case TownRiseupBase::RISEUP_BILLBOARD_SCRIPT:
        scriptCounter_++;
        for (unsigned int i = 0; i < RISEUP_SCRIPT_MOVE_MAX; i++) {
            if (!script_[i].enable_) {
                return &script_[i];
            }
        }
        break;
    case TownRiseupBase::RISEUP_SPRITE_MEDAL:
        medalCounter_++;
        for (unsigned int i = 0; i < RISEUP_MEDAL_MAX; i++) {
            if (!medal_[i].enable_) {
                return &medal_[i];
            }
        }
        break;
    case TownRiseupBase::RISEUP_BILLBOARD_EXHIBIT:
        exhibitCounter_++;
        for (unsigned int i = 0; i < RISEUP_EXHIBIT_MAX; i++) {
            if (!exhibit_[i].enable_) {
                return &exhibit_[i];
            }
        }
        break;
    }
    return NULL;
}

THUMB void twn::TownRiseupStorage::restoreContainer(int type)
{
    switch (type) {
    case TownRiseupBase::RISEUP_BILLBOARD_ITEM:
        iconCounter_--;
        break;
    case TownRiseupBase::RISEUP_SPRITE_ANIM:
        spriteCounter_--;
        break;
    case TownRiseupBase::RISEUP_MODEL_ANIM:
        modelCounter_--;
        break;
    case TownRiseupBase::RISEUP_BILLBOARD_SCRIPT:
        scriptCounter_--;
        break;
    case TownRiseupBase::RISEUP_SPRITE_MEDAL:
        medalCounter_--;
        break;
    case TownRiseupBase::RISEUP_BILLBOARD_EXHIBIT:
        exhibitCounter_--;
        break;
    }
}

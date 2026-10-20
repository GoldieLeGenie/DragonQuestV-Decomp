#pragma ipa file
#include "main/window/MapControl.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "ov019/commonmenu/CommonMenu_Dummy.hpp"

inline int window::MapControl::getPhase()
{
    return PHASE_MAP;
}

inline window::MapControl::~MapControl()
{
}

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

window::MapControl window::gMapControl;

THUMB void window::MapControl::setup()
{
    state_ = TOWNMAP_WAIT_MOVE;
    if (data_02101c88.isCurrentPart(4)) {
        BillboardCharacter::setAllCharaAnim(false);
    } else if (data_02101c88.isCurrentPart(6)) {
        SpriteCharacter::setAllCharaAnim(false);
    }
    playerLock(true);
    count_ = 0;
}

THUMB void window::MapControl::execute()
{
    switch (state_) {
        case TOWNMAP_WAIT_MOVE:
            if (++count_ > 2) {
                openMap();
                state_ = TOWNMAP_WAIT_OPEN;
            }
            break;
        case TOWNMAP_WAIT_OPEN:
            if (imageMap_->isOpen()) {
                state_ = TOWNMAP_VIEWING;
            }
            break;
        case TOWNMAP_VIEWING:
            break;
        case TOWMMAP_WAIT_CLOSE:
            if (imageMap_->isClose()) {
                if (data_02101c88.isCurrentPart(4)) {
                    BillboardCharacter::setAllCharaAnim(true);
                } else {
                    SpriteCharacter::setAllCharaAnim(true);
                }
                state_ = TOWNMAP_END;
                playerLock(false);
            }
            break;
        case TOWNMAP_MESSAGE:
            if (gTownMenu_MESSAGE.isOpen()) {
                int stat = gTownMenu_MESSAGE.getStat();
                if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
                    gTownMenu_MESSAGE.close();
                    closeMapMessage();
                    state_ = TOWNMAP_VIEWING;
                }
            }
            break;
        case TOWNMAP_END:
            break;
    }
}

THUMB void window::MapControl::registImageMap(ImageMap* imageMap)
{
    imageMap_ = imageMap;
}

THUMB void window::MapControl::openMap()
{
    imageMap_->open();
    gTownMenu_MapInfo.setMapInfo(1);
}

THUMB void window::MapControl::closeMap()
{
    imageMap_->close();
    gTownMenu_MapInfo.setMapInfo(0);
    setupIcon();
    state_ = TOWMMAP_WAIT_CLOSE;
}

THUMB void window::MapControl::closeMapMessage()
{
    gTownMenu_MapInfo.setMapInfo(1);
}

THUMB bool window::MapControl::isEnd()
{
    return state_ == TOWNMAP_END;
}

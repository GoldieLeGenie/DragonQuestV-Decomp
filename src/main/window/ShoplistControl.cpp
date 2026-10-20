#pragma ipa file
#include "main/window/ShoplistControl.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/TownShopMenu.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "ov019/commonmenu/CommonMenu_Dummy.hpp"

inline int window::ShoplistControl::getPhase()
{
    return PHASE_SHOPLIST;
}

inline window::ShoplistControl::~ShoplistControl()
{
}

inline void window::ShoplistControl::setOpen(bool flag)
{
    open_ = flag;
}

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

window::ShoplistControl window::gShoplistControl;

THUMB window::ShoplistControl::ShoplistControl()
{
    open_ = 0;
}

THUMB void window::ShoplistControl::setup()
{
    state_ = TOWNMAP_WAIT_OPEN;
    if (data_02101c88.isCurrentPart(4)) {
        BillboardCharacter::setAllCharaAnim(false);
    } else if (data_02101c88.isCurrentPart(6)) {
        SpriteCharacter::setAllCharaAnim(false);
    }
    openList();
    playerLock(true);
}

THUMB void window::ShoplistControl::execute()
{
    switch (state_) {
        case TOWNMAP_WAIT_OPEN:
            if (imageMap_->isOpen()) {
                state_ = TOWNMAP_VIEWING;
            }
            break;
        case TOWNMAP_VIEWING:
            if (dss::g_Pad.edge() & 0x800) {
                if (nextList() == false) {
                    closeList();
                    state_ = TOWMMAP_WAIT_CLOSE;
                    setOpen(false);
                } else {
                    state_ = RELEASE_WAIT;
                }
            } else if (dss::g_Pad.edge() & 1 || dss::g_Pad.edge() & 2) {
                closeList();
                state_ = TOWMMAP_WAIT_CLOSE;
            } else if (dss::g_Pad.edge() & 0x400) {
            }
            break;
        case TOWMMAP_WAIT_CLOSE:
            if (imageMap_->isClose()) {
                gTownMenu_MapInfo.setMapInfo(0);
                state_ = TOWMMAP_CLOSE;
            }
            break;
        case TOWMMAP_CLOSE:
            if (data_02101c88.isCurrentPart(4)) {
                BillboardCharacter::setAllCharaAnim(true);
            } else if (data_02101c88.isCurrentPart(6)) {
                SpriteCharacter::setAllCharaAnim(true);
            }
            playerLock(false);
            state_ = TOWNMAP_END;
            break;
        case TOWNMAP_MESSAGE:
            if (gTownMenu_MESSAGE.isOpen()) {
                int stat = gTownMenu_MESSAGE.getStat();
                if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
                    gTownMenu_MESSAGE.close();
                    closeListMessage();
                    state_ = TOWNMAP_VIEWING;
                }
            }
            break;
        case RELEASE_WAIT:
            state_ = TOWNMAP_VIEWING;
            break;
    }
}

THUMB void window::ShoplistControl::openList()
{
    gTownMenu_MapInfo.setMapInfo(2);
    for (int i = 0; i < 8; i++) {
        if (data_ov019_02182f2c.setPage(i)) {
            if (prev_ == PHASE_MAP) {
                imageMap_->openBlack();
            } else {
                imageMap_->open();
            }
            data_ov019_02182f2c.open();
            return;
        }
    }
}

THUMB void window::ShoplistControl::closeList()
{
    imageMap_->close();
    data_ov019_02182f2c.close();
    setupIcon();
    state_ = TOWMMAP_WAIT_CLOSE;
    setOpen(false);
}

THUMB bool window::ShoplistControl::nextList()
{
    return data_ov019_02182f2c.nextPage();
}

THUMB void window::ShoplistControl::closeListMessage()
{
}

THUMB void window::ShoplistControl::registShopList(ImageMap* imageMap)
{
    imageMap_ = imageMap;
}

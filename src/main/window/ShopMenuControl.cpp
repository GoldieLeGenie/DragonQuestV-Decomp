#pragma ipa file
#include "main/window/ShopMenuControl.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"

inline int window::ShopMenuControl::getPhase()
{
    return PHASE_SHOPMENU;
}

inline window::ShopMenuControl::~ShopMenuControl()
{
}

inline int MaterielMenu_WINDOW_MANAGER::getCloseMaterielMenu()
{
    return endWindow_;
}

window::ShopMenuControl window::gShopMenuControl;

THUMB void window::ShopMenuControl::setup()
{
    if (data_02101c88.unkfunc_02051818(4)) {
        BillboardCharacter::setAllCharaAnim(false);
        twn::TownStageManager::getSingleton()->pause(1);
    } else if (data_02101c88.unkfunc_02051818(6)) {
        fld::FieldStage::getSingleton()->fieldData.pause_ = 1;
        cmn::CommonParticleEmitter::getSingleton()->stop_ = 1;
        SpriteCharacter::setAllCharaAnim(false);
    }
    playerLock(true);
    state_ = OPEN_SETUP;
}

THUMB void window::ShopMenuControl::execute()
{
    switch (state_) {
        case OPEN_SETUP:
            MenuAPI::clearMenuAll();
            state_ = OPEN_SETUP1;
            break;
        case OPEN_SETUP1:
            state_ = OPEN_SETUP2;
            break;
        case OPEN_SETUP2:
            state_ = OPEN_WAIT;
            MenuAPI::changeMenuModeExtra();
            break;
        case OPEN_WAIT:
            if (MenuAPI::isMenuModeExtra()) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->openMaterielWindow(menuType_);
                state_ = OPEN;
            }
            break;
        case OPEN:
            if (MaterielMenu_WINDOW_MANAGER::getSingleton()->getCloseMaterielMenu()) {
                MenuAPI::changeMenuModeNormal();
                state_ = CLOSE_WAIT;
            }
            break;
        case CLOSE_WAIT:
            if (MenuAPI::isMenuModeNormal()) {
                setupIcon();
                state_ = RELEASE_WAIT;
            }
            break;
        case RELEASE_WAIT:
            if (data_02101c88.unkfunc_02051818(4)) {
                twn::TownStageManager::getSingleton()->pause(0);
                BillboardCharacter::setAllCharaAnim(true);
            } else {
                fld::FieldStage::getSingleton()->fieldData.pause_ = 0;
                cmn::CommonParticleEmitter::getSingleton()->stop_ = 0;
                SpriteCharacter::setAllCharaAnim(true);
            }
            playerLock(false);
            state_ = MENU_END;
            break;
    }
}

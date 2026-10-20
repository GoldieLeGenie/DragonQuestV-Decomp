#include "main/window/MenuControl.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_ROOT.hpp"
#include "ov019/townmenu/TownMenu_PARTY_TALK.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"

inline int window::MenuControl::getPhase()
{
    return PHASE_MENU;
}

int window::MenuControl::menu_;
window::MenuControl window::gMenuControl;

THUMB window::MenuControl::MenuControl()
{
}

THUMB window::MenuControl::~MenuControl()
{
}

THUMB void window::MenuControl::openSetup()
{
    setup();
}

THUMB void window::MenuControl::setup()
{
    if (data_02101c88.isCurrentPart(4)) {
        twn::TownStageManager::getSingleton()->pause(1);
        BillboardCharacter::setAllCharaAnim(false);
    } else if (data_02101c88.isCurrentPart(6)) {
        fld::FieldStage::getSingleton()->fieldData.pause_ = 1;
        cmn::CommonParticleEmitter::getSingleton()->stop_ = 1;
        SpriteCharacter::setAllCharaAnim(false);
    }
    playerLock(true);
    state_ = OPEN_SETUP;
    regist_ = PHASE_NORMAL;
}

THUMB void window::MenuControl::execute()
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
                openMenu();
                state_ = OPEN;
            }
            break;
        case OPEN:
            if (MenuAPI::isFinishMenu()) {
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
            if (data_02101c88.isCurrentPart(4)) {
                twn::TownStageManager::getSingleton()->pause(0);
                BillboardCharacter::setAllCharaAnim(true);
            } else {
                fld::FieldStage::getSingleton()->fieldData.pause_ = 0;
                cmn::CommonParticleEmitter::getSingleton()->stop_ = 0;
                SpriteCharacter::setAllCharaAnim(true);
            }
            playerLock(false);
            if (regist_ == PHASE_MENU) {
                setup();
            }
            state_ = MENU_END;
            break;
    }
}

THUMB void window::MenuControl::openMenu()
{
    int open = 0;
    MenuAPI::openTownMenu();
    switch (menu_) {
        case 1:
            gTownMenu_ROOT.close();
            gTownMenu_MAGIC_ROOT.open();
            open = 1;
            break;
        case 2:
            gTownMenu_ROOT.close();
            gTownMenuItemSelectChara.meisanhinFlag_ = 0;
            gTownMenuItemSelectChara.open();
            open = 1;
            break;
        case 3:
            gTownMenu_ROOT.close();
            data_ov019_02183524.fromMateriel_ = 0;
            data_ov019_02183524.open();
            open = 1;
            break;
        case 4:
            gTownMenu_ROOT.close();
            gTownMenu_PARTY_TALK.open();
            open = 1;
            break;
        default:
            if (data_02101c88.isCurrentPart(4) || data_02101c88.isCurrentPart(6)) {
                SoundManager::playSe(0x12c, 0);
            }
            break;
    }
    if (data_02101c88.isCurrentPart(6) && open == 1) {
        SoundManager::fieldPlay(fld::FieldSystem::getFloorBgmIndex());
    }
    menu_ = 0;
}


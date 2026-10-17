#pragma ipa file
#include "main/window/MessageControl.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/SpriteCharacter.hpp"

inline int window::MessageControl::getPhase()
{
    return PHASE_MESSAGE;
}

inline window::MessageControl::~MessageControl()
{
}

window::MessageControl window::gMessageControl;

THUMB window::MessageControl::MessageControl()
{
    state_ = END_MESSAGE;
}

THUMB void window::MessageControl::startMessage()
{
    setup();
}

THUMB void window::MessageControl::setup()
{
    if (data_02101c88.unkfunc_02051818(4)) {
        BillboardCharacter::allAnimLock = 1;
    } else if (data_02101c88.unkfunc_02051818(6)) {
        back_ = SpriteCharacter::getAllCharaAnim();
        SpriteCharacter::setAllCharaAnim(false);
    }
    state_ = MESSAGE;
}

THUMB void window::MessageControl::execute()
{
    switch (state_) {
        case MESSAGE:
            if (MenuAPI::isFinishMenu()) {
                MenuAPI::changeMenuModeNormal();
                state_ = CLOSE_WAIT;
            }
            break;
        case CLOSE_WAIT:
            if (MenuAPI::isMenuModeNormal()) {
                setupIcon();
                if (data_02101c88.unkfunc_02051818(4)) {
                    BillboardCharacter::allAnimLock = 0;
                } else {
                    SpriteCharacter::setAllCharaAnim(back_);
                }
                state_ = END_MESSAGE;
            }
            break;
        case END_MESSAGE:
            break;
    }
}

THUMB void window::MessageControl::MESSAGEWINDOW(int message, int count)
{
    MenuAPI::openMessage(message, count);
}

THUMB void window::MessageControl::MESSAGECOMMONWINDOW()
{
    MenuAPI::openCommonMessage();
}

THUMB void window::MessageControl::ADDCOMMONWINDOW(int message)
{
    MenuAPI::addCommonMessage(message);
}

THUMB void window::MessageControl::WAITCOMMONWINDOW()
{
    MenuAPI::waitCommonMessage();
}

THUMB void window::MessageControl::CLEARCOMMONWINDOW()
{
    MenuAPI::clearCommonMessage();
}

THUMB void window::MessageControl::SERIALCOMMONWINDOW(int message)
{
    MenuAPI::addMessageSerial(message);
}

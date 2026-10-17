#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/global/Global.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/window/ShopMenuControl.hpp"

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

THUMB fld::FieldCommandBookingMenu::FieldCommandBookingMenu()
{
    fadeCount_ = 0;
}

THUMB int fld::FieldCommandBookingMenu::isExec()
{
    int bookingFlag = status::g_Menu.bookingFlag_;
    if (bookingFlag == 0) {
        return false;
    }
    switch (bookingFlag) {
        case 3:
            window::gShopMenuControl.startMenu(0x1d);
            break;
        case 2:
            if (fadeCount_ == 0) {
                cmn::GameManager::getSingleton().getPlayerManager()->setLock(true);
                cmn::GameManager::getSingleton().getPlayerManager()->charaColl_ = 0;
                BillboardCharacter::setAllCharaAnim(false);
                fadeCount_++;
            } else if (fadeCount_ > 0x1e) {
                window::gShopMenuControl.startMenu(0);
            } else {
                fadeCount_++;
            }
            break;
        case 5:
            window::gShopMenuControl.startMenu(0x1a);
            break;
        case 13:
            if (fadeCount_ == 0) {
                cmn::GameManager::getSingleton().getPlayerManager()->setLock(true);
                cmn::GameManager::getSingleton().getPlayerManager()->charaColl_ = 0;
                BillboardCharacter::setAllCharaAnim(false);
                fadeCount_++;
            }
            if (data_0211b27c.count_ == data_0211b27c.frames_) {
                window::gShopMenuControl.startMenu(1);
            }
            break;
    }
    return true;
}

THUMB void fld::FieldCommandBookingMenu::exec()
{
    CommandObjectDefineFieldSystem::setReturnMaterielMenu();
}

THUMB int fld::FieldCommandBookingMenu::isEnd()
{
    return window::gShopMenuControl.state_ == 8;
}

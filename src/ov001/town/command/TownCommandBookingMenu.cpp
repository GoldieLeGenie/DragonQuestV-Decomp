#include "ov001/town/command/TownCommandBookingMenu.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/global/Global.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

inline int status::MenuStatus::getBooking()
{
    return bookingFlag_;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

inline void window::ShopMenuControl::startMenu(int menuType)
{
    menuType_ = menuType;
    state_ = 7;
}

inline bool window::ShopMenuControl::isMenuEnd()
{
    return state_ == 8;
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline void cmn::PlayerManager::setTownCharaColl(bool charaColl)
{
    charaColl_ = charaColl;
}

twn::TownCommandBookingMenu::TownCommandBookingMenu()
{
    fadeCount_ = 0;
    fadeEnd_ = true;
    meisanInnFlag_ = false;
}

int twn::TownCommandBookingMenu::isExec()
{
    if (status::g_Menu.getBooking() == menu::BOOKING_NONE) {
        return false;
    }
    switch (status::g_Menu.getBooking()) {
    case menu::BOOKING_CHURCH:
        window::gShopMenuControl.startMenu(0x1d);
        break;
    case menu::BOOKING_INN:
        fadeEnd_ = false;
        if (fadeCount_ > 30) {
            fadeEnd_ = true;
            meisanInnFlag_ = false;
            window::gShopMenuControl.startMenu(0);
            fadeCount_ = 0;
            break;
        }
        if (fadeCount_ == 0) {
            meisanInnFlag_ = true;
        }
        fadeCount_++;
        return true;
    case menu::BOOKING_STADIUM:
        window::gShopMenuControl.startMenu(0x1a);
        break;
    case menu::BOOKING_SLIMERACE:
        fadeEnd_ = false;
        if (fadeCount_ > 30) {
            fadeEnd_ = true;
            window::gShopMenuControl.startMenu(0x26);
            break;
        }
        fadeCount_++;
        return true;
    case menu::BOOKING_SLIMETOUCH:
        fadeEnd_ = false;
        if (fadeCount_ > 30) {
            fadeEnd_ = true;
            window::gShopMenuControl.startMenu(0x28);
            break;
        }
        fadeCount_++;
        return true;
    case menu::BOOKING_FUKUBIKI:
        window::gShopMenuControl.startMenu(0x17);
        break;
    case menu::BOOKING_JISAN:
        window::gShopMenuControl.startMenu(0x15);
        break;
    case menu::BOOKING_LUIDA:
        window::gShopMenuControl.startMenu(0x16);
        break;
    case menu::BOOKING_SURECHIGAI_ROOT:
        window::gShopMenuControl.startMenu(0x13);
        break;
    case menu::BOOKING_SURECHIGAI:
        window::gShopMenuControl.startMenu(0x11);
        break;
    case menu::BOOKING_GAMESET:
        if (fadeCount_ == 0) {
            cmn::GameManager::getSingleton().getPlayerManager()->setLock(true);
            cmn::GameManager::getSingleton().getPlayerManager()->setTownCharaColl(false);
            BillboardCharacter::setAllCharaAnim(false);
            fadeCount_++;
            fadeEnd_ = false;
            return true;
        }
        if (data_0211b27c.count_ == data_0211b27c.frames_) {
            fadeEnd_ = true;
            window::gShopMenuControl.startMenu(1);
            break;
        }
        return true;
    }
    status::g_Menu.setBooking(menu::BOOKING_RETURN);
    window::gShopMenuControl.setup();
    return true;
}

void twn::TownCommandBookingMenu::exec()
{
    CommandObjectDefineTownSystem::setReturnMaterielMenu();
    if (!fadeEnd_) {
        args::GameSystemManager::getSingleton().setExclusion(TownSystem::MaterielMenuPriority, false);
    }
    if (meisanInnFlag_ == true) {
        args::GameSystemManager::getSingleton().setExclusion(TownSystem::RiseupPriority, true);
    } else {
        args::GameSystemManager::getSingleton().setExclusion(TownSystem::RiseupPriority, false);
    }
}

int twn::TownCommandBookingMenu::isEnd()
{
    if (fadeEnd_ == false) {
        return true;
    } else {
        return window::gShopMenuControl.isMenuEnd();
    }
}

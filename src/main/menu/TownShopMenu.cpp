#include "main/menu/TownShopMenu.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/global/Global.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"

THUMB menu::TownShopMenu::TownShopMenu()
{
}

THUMB menu::TownShopMenu::~TownShopMenu()
{
}

THUMB void menu::TownShopMenu::menuSetup()
{
    setPage(0);
}

THUMB void menu::TownShopMenu::menuExecute()
{
}

THUMB void menu::TownShopMenu::menuDraw()
{
    if (type_ != -1) {
        drawTownShopScreen(type_);
    }
}

THUMB void menu::TownShopMenu::menuUpdate()
{
}

THUMB int menu::TownShopMenu::setPage(int page)
{
    switch (page) {
        case 0:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_WEAPON)) {
                if (g_Global.areaNo_ == 10 && status::g_Story.chapter_ == dq5::CHAPTER_YOUNENKI && g_AreaFlag.check(0x53) && !g_AreaFlag.check(0x65)) {
                } else if (g_Global.areaNo_ == 17 && status::g_Story.chapter_ == dq5::CHAPTER_SEINENKI && !g_AreaFlag.check(0xd4)) {
                } else {
                    type_ = 0;
                    redraw_ = 1;
                    return true;
                }
            }
        case 1:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_PROTECTOR)) {
                type_ = 1;
                redraw_ = 1;
                return true;
            }
        case 2:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_ITEM)) {
                if (g_Global.areaNo_ == 10 && status::g_Story.chapter_ == dq5::CHAPTER_YOUNENKI && !g_AreaFlag.check(0x53)) {
                } else if (g_Global.areaNo_ == 10 && status::g_Story.chapter_ == dq5::CHAPTER_YOUNENKI && g_AreaFlag.check(0x65)) {
                } else if (g_Global.areaNo_ == 3 && status::g_Story.chapter_ == dq5::CHAPTER_SEINENKI && !g_GlobalFlag.check(7)) {
                } else if (g_Global.areaNo_ == 17 && status::g_Story.chapter_ == dq5::CHAPTER_SEINENKI && !g_AreaFlag.check(0xd4)) {
                } else {
                    type_ = 2;
                    redraw_ = 1;
                    return true;
                }
            }
        case 3:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_YOROZU)) {
                type_ = 3;
                redraw_ = 1;
                return true;
            }
        case 4:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_WEAPON_SECOND)) {
                type_ = 4;
                redraw_ = 1;
                return true;
            }
        case 5:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_PROTECTOR_SECOND)) {
                type_ = 5;
                redraw_ = 1;
                return true;
            }
        case 6:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_ITEM_SECOND)) {
                type_ = 6;
                redraw_ = 1;
                return true;
            }
        case 7:
            if (status::g_Shop.getShopCount(status::ShopList::SHOP_YOROZU_SECOND)) {
                type_ = 7;
                redraw_ = 1;
                return true;
            }
    }
    type_ = -1;
    return false;
}

THUMB bool menu::TownShopMenu::nextPage()
{
    if (setPage(type_ + 1)) {
        return true;
    }
    return false;
}

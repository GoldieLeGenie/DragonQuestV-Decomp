#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownImageShoplist.hpp"
#include "main/window/ShoplistControl.hpp"

namespace twn {
    TownImageShoplist shoplist;
}

#pragma thumb on

twn::TownSystemDrawShopList::TownSystemDrawShopList()
{
}

twn::TownSystemDrawShopList::~TownSystemDrawShopList()
{
}

void twn::TownSystemDrawShopList::initialize()
{
    window::gShoplistControl.registShopList(&shoplist);
}

void twn::TownSystemDrawShopList::terminate()
{
    shoplist.cleanup();
}

void twn::TownSystemDrawShopList::execute()
{
    window::gShoplistControl.execute();
    shoplist.execute();
}

void twn::TownSystemDrawShopList::draw()
{
    shoplist.draw();
}

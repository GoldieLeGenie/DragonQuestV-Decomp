#include "ov001/town/TownSystem.hpp"
#include "main/window/ShopMenuControl.hpp"

#pragma thumb on

twn::TownSystemMaterielMenu::TownSystemMaterielMenu()
{
}

twn::TownSystemMaterielMenu::~TownSystemMaterielMenu()
{
}

void twn::TownSystemMaterielMenu::initialize()
{
}

void twn::TownSystemMaterielMenu::terminate()
{
}

void twn::TownSystemMaterielMenu::execute()
{
    window::gShopMenuControl.execute();
}

void twn::TownSystemMaterielMenu::draw()
{
}

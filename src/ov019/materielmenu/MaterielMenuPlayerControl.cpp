#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"

THUMB menu::MaterielMenuPlayerControl* menu::MaterielMenuPlayerControl::getSingleton()
{
    static MaterielMenuPlayerControl playerControl;
    return &playerControl;
}

THUMB void menu::MaterielMenuPlayerControl::initialize()
{
    setup();
    activeItemPage_ = 0;
    churchCommandNum_ = 0;
}

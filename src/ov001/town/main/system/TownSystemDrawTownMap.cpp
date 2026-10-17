#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownImageMap.hpp"
#include "main/window/MapControl.hpp"

twn::TownImageMap twn::imageMap;

THUMB twn::TownSystemDrawTownMap::TownSystemDrawTownMap()
{
}

THUMB twn::TownSystemDrawTownMap::~TownSystemDrawTownMap()
{
}

THUMB void twn::TownSystemDrawTownMap::initialize()
{
    window::gMapControl.registImageMap(&imageMap);
    imageMap.setOverview();
    imageMap.calcTargetPos();
}

THUMB void twn::TownSystemDrawTownMap::terminate()
{
    imageMap.exitFloor();
    imageMap.cleanup();
}

THUMB void twn::TownSystemDrawTownMap::execute()
{
    imageMap.execute();
    window::gMapControl.execute();
}

THUMB void twn::TownSystemDrawTownMap::draw()
{
    imageMap.draw();
}

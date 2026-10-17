#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownExtraMapObjManager.hpp"
#include "main/cmn/ExtraMapLink.hpp"

#pragma thumb on

twn::TownSystemStage::TownSystemStage()
{
}

twn::TownSystemStage::~TownSystemStage()
{
}

void twn::TownSystemStage::initialize()
{
    TownCamera::getSingleton()->initialize();
    TownStageManager::getSingleton()->initialize();
    cmn::g_extraMapLink.setup();
    TownExtraMapObjManager::getSingleton().setup();
}

void twn::TownSystemStage::terminate()
{
    TownStageManager::getSingleton()->terminate();
}

void twn::TownSystemStage::execute()
{
    TownStageManager::getSingleton()->execute();
}

void twn::TownSystemStage::draw()
{
    TownStageManager::getSingleton()->draw();
}

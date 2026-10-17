#include "ov005/fld/FieldSystem.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSymbolManager.hpp"

THUMB fld::FieldSystemStage::FieldSystemStage()
{
}

THUMB fld::FieldSystemStage::~FieldSystemStage()
{
}

THUMB void fld::FieldSystemStage::initialize()
{
    FieldStage::getSingleton()->initialize();
    cmn::g_extraMapLink.setup();
    FieldStage::getSingleton()->ChangeTime(1);
    FieldSymbolManager::getSingleton().initialize();
}

THUMB void fld::FieldSystemStage::terminate()
{
    FieldSymbolManager::getSingleton().terminate();
    FieldStage::getSingleton()->terminate();
}

THUMB void fld::FieldSystemStage::execute()
{
    FieldStage::getSingleton()->execute();
}

THUMB void fld::FieldSystemStage::draw()
{
    FieldStage::getSingleton()->draw();
    FieldStage::getSingleton()->drawPlayer();
}

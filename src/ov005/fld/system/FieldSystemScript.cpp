#pragma ipa file
#include "ov005/fld/FieldSystem.hpp"
#include "main/global/Global.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/status/StoryStatus.hpp"

THUMB fld::FieldSystemScript::FieldSystemScript()
{
}

THUMB fld::FieldSystemScript::~FieldSystemScript()
{
}

THUMB void fld::FieldSystemScript::initialize()
{
    eventLock_ = 0;
    search_ = 0;
    switch (g_Global.getFieldType()) {
        case 0:
            ScriptSystem::getSingleton()->initialize(status::g_Story.chapter_, "field");
            break;
        case 1:
            ScriptSystem::getSingleton()->initialize(status::g_Story.chapter_, "fieldyw");
            break;
        case 2:
            ScriptSystem::getSingleton()->initialize(status::g_Story.chapter_, "fieldys");
            break;
        case 3:
            ScriptSystem::getSingleton()->initialize(status::g_Story.chapter_, "fielddark");
            break;
    }
}

THUMB void fld::FieldSystemScript::terminate()
{
    ScriptSystem::getSingleton()->terminate();
}

THUMB void fld::FieldSystemScript::execute()
{
    ScriptSystem::getSingleton()->execute();
    search_ = 0;
}

THUMB void fld::FieldSystemScript::draw()
{
}

THUMB bool fld::FieldSystemScript::isEventLock()
{
    return eventLock_ > 0;
}

THUMB void fld::FieldSystemScript::setEventLock(bool flag)
{
    if (flag == true) {
        eventLock_++;
    } else {
        eventLock_--;
    }
}

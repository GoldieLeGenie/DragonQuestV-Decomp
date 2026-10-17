#include "main/script/ScriptSystem.hpp"
#include "main/script/ScriptBaseCommand.hpp"
#include "main/script/ScriptCommand.hpp"
#include "main/script/sys/PlacementParameter.hpp"
#include "main/script/sys/ScriptParam.hpp"
#include "main/script/sys/ScriptObject.hpp"
#include "main/script/sys/ScriptGroup.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/data/FileLoader.hpp"

inline bool ScriptSystem::isEnable()
{
    return enable_;
}

THUMB ScriptSystem::ScriptSystem()
{
    enable_ = true;
}

THUMB ScriptSystem::~ScriptSystem()
{
}

THUMB ScriptSystem* ScriptSystem::getSingleton()
{
    static ScriptSystem scriptSystem;
    return &scriptSystem;
}

THUMB void ScriptSystem::setup(char* fname)
{
    dataObject_.setup(fname, 1, 0);
    setup();
}

THUMB void ScriptSystem::setup()
{
    PlacementParameter::setStartFunction(StartFunction);
    ScriptParam::setExecuteCommandFunction(CommandFunction);
    ScriptObject::setSetCtrlIdFunction(setPlacementCtrlId);
    initializeScriptObjectEnble();
    ScriptGroup::setScriptObjectEnableFunction((bool (*)(int))isScriptObjectEnble);
    initializeScriptObjectCtrl();
    ScriptGroup::setScriptObjectCtrlFunction(setScriptObjectCtrl);
    scriptEngine_.setup(dataObject_.getAddr(), chapter_);
    executeEnable_ = true;
}

THUMB void ScriptSystem::cleanup()
{
    scriptEngine_.cleanup();
    dataObject_.cleanup();
}

THUMB void ScriptSystem::initialize(int chapter, const char* filename)
{
    char ss[128];
    if (!isEnable()) {
        flag_ = false;
        return;
    }
    chapter_ = chapter;
    if (filename == NULL) {
        dss::sprintf_s(ss, sizeof(ss), "data/script/%s.bin", status::g_StageAttribute.getMapName());
    } else {
        dss::sprintf_s(ss, sizeof(ss), "data/script/%s.bin", filename);
    }
    if (dss::g_File.isExist(ss, dss::File::Switching)) {
        setup(ss);
        flag_ = true;
    } else {
        flag_ = false;
        return;
    }
    scriptEngine_.initialize();
}

THUMB void ScriptSystem::terminate()
{
    if (!flag_) {
        return;
    }
    scriptEngine_.terminate();
    cleanup();
}

THUMB void ScriptSystem::execute()
{
    if (!flag_ || !executeEnable_) {
        return;
    }
    scriptEngine_.execute();
}
